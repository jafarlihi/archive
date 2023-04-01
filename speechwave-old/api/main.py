import os
import subprocess
import math
import hashlib
import datetime
import logging
import json
import secrets
import stripe
from uuid import uuid4
from flask import Flask, request, jsonify, request
from flask_cors import CORS
from flask_jwt_extended import JWTManager, create_access_token, jwt_required, get_jwt_identity
from flask_limiter import Limiter
from flask_limiter.util import get_remote_address
from pymongo import MongoClient
from bson import json_util
from bson.json_util import dumps
from dotenv import load_dotenv
from werkzeug.utils import secure_filename
from google.cloud import storage

load_dotenv()
allowed_extensions = ['3gp', 'aiff', 'avi', 'flac', 'flv', 'm4a', 'mkv', 'mov', 'mp3', 'mp4', 'ogg', 'wav', 'webm', 'wma', 'wmv']
languages = ['Afrikaans', 'Albanian', 'Amharic', 'Arabic', 'Armenian', 'Assamese', 'Azerbaijani', 'Bashkir', 'Basque', 'Belarusian', 'Bengali', 'Bosnian', 'Breton', 'Bulgarian', 'Burmese', 'Castilian', 'Catalan', 'Chinese', 'Croatian', 'Czech', 'Danish', 'Dutch', 'English', 'Estonian', 'Faroese', 'Finnish', 'Flemish', 'French', 'Galician', 'Georgian', 'German', 'Greek', 'Gujarati', 'Haitian', 'Haitian Creole', 'Hausa', 'Hawaiian', 'Hebrew', 'Hindi', 'Hungarian', 'Icelandic', 'Indonesian', 'Italian', 'Japanese', 'Javanese', 'Kannada', 'Kazakh', 'Khmer', 'Korean', 'Lao', 'Latin', 'Latvian', 'Letzeburgesch', 'Lingala', 'Lithuanian', 'Luxembourgish', 'Macedonian', 'Malagasy', 'Malay', 'Malayalam', 'Maltese', 'Maori', 'Marathi', 'Moldavian', 'Moldovan', 'Mongolian', 'Myanmar', 'Nepali', 'Norwegian', 'Nynorsk', 'Occitan', 'Panjabi', 'Pashto', 'Persian', 'Polish', 'Portuguese', 'Punjabi', 'Pushto', 'Romanian', 'Russian', 'Sanskrit', 'Serbian', 'Shona', 'Sindhi', 'Sinhala', 'Sinhalese', 'Slovak', 'Slovenian', 'Somali', 'Spanish', 'Sundanese', 'Swahili', 'Swedish', 'Tagalog', 'Tajik', 'Tamil', 'Tatar', 'Telugu', 'Thai', 'Tibetan', 'Turkish', 'Turkmen', 'Ukrainian', 'Urdu', 'Uzbek', 'Valencian', 'Vietnamese', 'Welsh', 'Yiddish', 'Yoruba']


def allowed_file(filename):
    return '.' in filename and \
            filename.rsplit('.', 1)[1].lower() in allowed_extensions


def upload_file(file, translate, language):
    filename = secure_filename(file.filename)
    uuid_filename = str(uuid4()) + '.' + filename.rsplit('.', 1)[1].lower()
    if translate == 'true':
        uuid_filename = uuid_filename + '.translate'
    if language and language in languages:
        uuid_filename = uuid_filename + '.' + language
    storage_client = storage.Client(os.environ['GCP_PROJECT_NAME'])
    bucket = storage_client.bucket(os.environ['GCP_INPUT_BUCKET_NAME'])
    blob = bucket.blob(uuid_filename)
    blob._chunk_size = 8388608  # 1024 * 1024 B * 16 = 8 MB
    blob.upload_from_file(file)
    return uuid_filename


def create_app(test = False):
    app = Flask(__name__)
    CORS(app)
    limiter = Limiter(app, key_func=get_remote_address, storage_uri=os.environ['MONGO_URL'], strategy="fixed-window")
    stripe.api_key = os.environ['STRIPE_SECRET_KEY']
    client = MongoClient(os.environ['MONGO_URL'])
    db = client['speechwave']
    users_collection = db['users']
    uploads_collection = db['uploads']
    lock_collection = db['transcription']
    keys_collection = db['keys']
    credits_collection = db['credits']
    logging.basicConfig(filename='api.log', filemode='a', format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO)

    if test:
        limiter.enabled = False
        db = client['speechwave-test']
        users_collection = db['users']
        uploads_collection = db['uploads']
        lock_collection = db['transcription']
        keys_collection = db['keys']
        credits_collection = db['credits']

    jwt = JWTManager(app)
    app.config['JWT_SECRET_KEY'] = os.environ['JWT_SECRET_KEY']
    app.config['JWT_ACCESS_TOKEN_EXPIRES'] = datetime.timedelta(days=1)
    app.config['MAX_CONTENT_LENGTH'] = 32 * 1000 * 1000 * 1000 # 32GB


    def key_auth(request):
        auth_header = request.headers.get('Authorization').split()
        key = auth_header[1] if auth_header[0] == 'Key' else None
        key_obj = keys_collection.find_one({'key': key})
        return key_obj['email'] if key_obj else None


    @app.before_request
    @jwt_required(optional=True)
    def before_request():
        current_user = None
        try:
            current_user = get_jwt_identity()
            if not current_user:
                current_user = key_auth(request)
        except:
            pass
        if current_user:
            logging.info('Before request: %s %s %s %s', current_user, request.remote_addr, request.method, request.full_path)
        else:
            logging.info('Before request: %s %s %s', request.remote_addr, request.method, request.full_path)


    @app.after_request
    @jwt_required(optional=True)
    def after_request(response):
        current_user = None
        try:
            current_user = get_jwt_identity()
            if not current_user:
                current_user = key_auth(request)
        except:
            pass
        if current_user:
            logging.info('After request: %s %s %s %s %s', current_user, request.remote_addr, request.method, request.full_path, response.status)
        else:
            logging.info('After request: %s %s %s %s', request.remote_addr, request.method, request.full_path, response.status)
        return response


    @app.route('/v1/stripe', methods=['GET'])
    @limiter.limit('20/minute')
    @jwt_required()
    def getStripePublishableKey():
        return jsonify({'key': os.environ['STRIPE_PUBLISHABLE_KEY']}), 200


    @app.route('/v1/stripe', methods=['POST'])
    @limiter.limit('20/minute')
    @jwt_required()
    def getStripeClientSecret():
        current_user = get_jwt_identity()
        data = request.get_json()
        intent = stripe.PaymentIntent.create(amount=int(data['amount']), currency='usd', automatic_payment_methods={'enabled': True}, metadata={'email': current_user})
        return jsonify({'key': intent.client_secret}), 200


    @app.route("/v1/stripe/webhook", methods=['POST'])
    @limiter.limit('100/minute')
    def webhook():
      payload = request.get_data()
      sig_header = request.headers.get('STRIPE_SIGNATURE')
      event = None

      try:
        event = stripe.Webhook.construct_event(
          payload, sig_header, os.environ['STRIPE_WEBHOOK_SECRET_KEY']
        )
      except Exception as e:
        return "Invalid payload", 400

      event_dict = event.to_dict()
      if event_dict['type'] == "payment_intent.succeeded":
        intent = event_dict['data']['object']
        logging.info('Stripe payment success, ID: ' + intent['id'])
        credits_collection.insert_one({'email': intent['metadata']['email'], 'type': 'add', 'date': datetime.datetime.now(), 'reason': 'Purchased', 'amount': intent['amount'] / 10})
        users_collection.update_one({'email': intent['metadata']['email']}, {'$inc': { 'credits': intent['amount'] / 10 }})
      elif event_dict['type'] == "payment_intent.payment_failed":
        intent = event_dict['data']['object']
        error_message = intent['last_payment_error']['message'] if intent.get('last_payment_error') else None
        logging.info('Stripe payment failure, ID: ' + intent['id'])

      return "OK", 200


    @app.route('/v1/key', methods=['POST'])
    @limiter.limit('10/minute')
    @jwt_required()
    def generateApiKey():
        current_user = get_jwt_identity()
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401
        key = secrets.token_urlsafe(32)
        keys_collection.insert_one({'email': current_user, 'key': key, 'created_at': datetime.datetime.now()})
        return jsonify({'key': key}), 201


    @app.route('/v1/key', methods=['DELETE'])
    @limiter.limit('100/minute')
    @jwt_required()
    def deleteApiKey():
        current_user = get_jwt_identity()
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401
        key = request.args.get('key')
        if not key:
            return jsonify({'message': 'Key not provided'}), 400
        current_user = get_jwt_identity()
        keys = keys_collection.find({'email': current_user})
        if key not in [k['key'] for k in keys]:
            return jsonify({'message': 'Key not found'}), 400
        keys_collection.delete_one({'key': key})
        return jsonify({'message': 'Key revoked successfully'}), 204


    @app.route('/v1/key', methods=['GET'])
    @limiter.limit('1000/minute')
    @jwt_required()
    def listApiKeys():
        current_user = get_jwt_identity()
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401
        return jsonify({'keys': json.loads(json_util.dumps(keys_collection.find({'email': current_user})))}), 200


    @app.route('/v1/upload', methods=['POST'])
    @limiter.limit('1000/minute')
    @jwt_required(optional=True)
    def upload():
        current_user = get_jwt_identity()
        if not current_user:
            current_user = key_auth(request)
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401

        translate = request.form.get('translate')
        language = request.form.get('language')

        if 'file' not in request.files:
            return jsonify({'message': 'No file in request named "file"'}), 400

        file = request.files['file']

        if file.filename == '':
            return jsonify({'message': 'Upload failed'}), 400

        if file and allowed_file(file.filename):
            uuid_filename = upload_file(file, translate, language)
            if uuid_filename:
                process = subprocess.Popen('mediainfo --Output="General;%%Duration%%" %s/%s' % (os.environ['GCP_INPUT_BUCKET_MOUNT_PATH'], uuid_filename), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                out, _ = process.communicate()
                if len(out) < 3:
                    return jsonify({'message': 'Uploaded file is invalid'}), 400
                cost = math.ceil(int(out) / 1000 / 60 if int(out) / 1000 / 60 >= 1 else 1)
                uploads_collection.insert_one({'filename': uuid_filename, 'original_name': file.filename, 'email': current_user, 'uploaded_at': datetime.datetime.now(), 'status': 'In progress', 'cost': cost})
                return jsonify({'message': 'Upload was successful', 'filename': uuid_filename}), 200
            else:
                return jsonify({'message': 'Upload failed'}), 500
        else:
            return jsonify({'message': 'File extension not supported'}), 400


    @app.route('/v1/upload', methods=['GET'])
    @limiter.limit('1000/minute')
    @jwt_required(optional=True)
    def getUploads():
        current_user = get_jwt_identity()
        if not current_user:
            current_user = key_auth(request)
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401

        uploads_cursor = uploads_collection.find({'email': current_user})
        uploads = []
        for upload in uploads_cursor:
            uploads.append(json.loads(json_util.dumps(upload)))
        return jsonify({'uploads': uploads})


    @app.route('/v1/register', methods=['POST'])
    @limiter.limit('10/minute')
    def registerEndpoint():
        new_user = request.get_json()
        if len(new_user['password']) < 6:
            return jsonify({'message': 'Password can not be shorter than 6 characters'}), 400
        new_user['password'] = hashlib.sha256(new_user['password'].encode('utf-8')).hexdigest()
        doc = users_collection.find_one({'email': new_user['email']})
        if not doc:
            users_collection.insert_one(new_user)
            return jsonify({'message': 'User created successfully'}), 201
        else:
            return jsonify({'message': 'Email is already registered'}), 409


    @app.route('/v1/login', methods=['POST'])
    @limiter.limit('20/minute')
    def loginEndpoint():
        login_details = request.get_json()
        user_from_db = users_collection.find_one({'email': login_details['email']})

        if user_from_db:
            encrpted_password = hashlib.sha256(login_details['password'].encode('utf-8')).hexdigest()
            if encrpted_password == user_from_db['password']:
                access_token = create_access_token(identity=user_from_db['email'])
                return jsonify(access=access_token), 200

        return jsonify({'message': 'The email or password is incorrect'}), 401


    @app.route('/v1/credits', methods=['GET'])
    @limiter.limit('1000/minute')
    @jwt_required(optional=True)
    def getCreditsEndpoint():
        current_user = get_jwt_identity()
        detailed = request.args.get('detailed')
        if not current_user:
            current_user = key_auth(request)
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401

        user_from_db = users_collection.find_one({'email' : current_user})
        if user_from_db:
            if not detailed == 'true':
                return jsonify({'credits': int(user_from_db['credits'] if 'credits' in user_from_db else 0)}), 200
            else:
                history = credits_collection.find({'email': current_user})
                return jsonify({'history': json.loads(json_util.dumps(history)), 'credits': int(user_from_db['credits'] if 'credits' in user_from_db else 0)}), 200
        else:
            return jsonify({'message': 'User not found'}), 404


    @app.route('/v1/transcription', methods=['GET'])
    @limiter.limit('2000/minute')
    @jwt_required(optional=True)
    def transcribe():
        current_user = get_jwt_identity()
        if not current_user:
            current_user = key_auth(request)
        if not current_user:
            return jsonify({'message': 'Unauthorized'}), 401

        filename = request.args.get('filename')
        if not filename:
            return jsonify({'message': 'Filename was not provided'}), 400

        filename = secure_filename(filename)

        user_from_db = users_collection.find_one({'email' : current_user})
        if not user_from_db:
            return jsonify({'message': 'User not found'}), 404

        file_belongs_to_user = uploads_collection.count_documents({'email': current_user, 'filename': filename})
        if not file_belongs_to_user:
            return jsonify({'message': 'Unauthorized'}), 401

        storage_client = storage.Client(os.environ['GCP_PROJECT_NAME'])
        output_bucket = storage_client.bucket(os.environ['GCP_OUTPUT_BUCKET_NAME'])
        result_exists = storage.Blob(bucket=output_bucket, name=filename + '.txt').exists(storage_client)

        if result_exists and lock_collection.count_documents({'filename': filename}):
            txt = output_bucket.blob(filename + '.txt')
            srt = output_bucket.blob(filename + '.srt')
            vtt = output_bucket.blob(filename + '.vtt')
            txt.make_public()
            srt.make_public()
            vtt.make_public()
            uploads_collection.update_one({ 'filename': filename }, {'$set': {'status': 'Done', 'txt': txt.public_url, 'srt': srt.public_url, 'vtt': vtt.public_url}})
            return jsonify({'txt': txt.public_url, 'srt': srt.public_url, 'vtt': vtt.public_url}), 200

        bucket = storage_client.bucket(os.environ['GCP_INPUT_BUCKET_NAME'])
        file_exists = storage.Blob(bucket=bucket, name=filename).exists(storage_client)
        if not file_exists and not result_exists:
            return jsonify({'message': 'File is not uploaded'}), 400

        cost = uploads_collection.find_one({'filename': filename})['cost']

        if not lock_collection.count_documents({'filename': filename}):
            if cost > int(user_from_db['credits'] if 'credits' in user_from_db else 0):
                return jsonify({'message': 'Not enough credits'}), 400

            lock_collection.insert_one({'filename': filename})
            original_name = uploads_collection.find_one({'filename': filename})['original_name']
            credits_collection.insert_one({'email': user_from_db['email'], 'type': 'deduct', 'date': datetime.datetime.now(), 'filename': original_name, 'reason': 'Transcription', 'amount': cost})
            users_collection.update_one({'email': user_from_db['email']}, {'$set': {'credits': int(user_from_db['credits']) - cost}})

        return jsonify({'message': 'Transcription is in progress. Make the same request again later to fetch the results.'}), 200


    return app

