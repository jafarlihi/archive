import pytest
import os
from pymongo import MongoClient
from main import create_app

mongo = MongoClient(os.environ['MONGO_URL'])


@pytest.fixture()
def app():
    app = create_app(test = True)
    app.config.update({
        'TESTING': True,
    })
    mongo.drop_database('speechwave-test')
    yield app


@pytest.fixture()
def client(app):
    return app.test_client()


@pytest.fixture()
def runner(app):
    return app.test_cli_runner()


def test_register_and_login(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'


def test_register_short_password(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'not'
    })
    assert response.status == '400 BAD REQUEST'


def test_get_credits(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    response = client.get('/v1/credits', headers={
        'Authorization': 'Bearer ' + response.json['access']
    })
    assert response.status == '200 OK'
    assert response.json['credits'] == 0


def test_get_credits_with_api_key(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    response = client.post('/v1/key', headers={
        'Authorization': 'Bearer ' + response.json['access']
    })
    assert response.status == '201 CREATED'
    assert len(response.json['key']) == 43

    response = client.get('/v1/credits', headers={
        'Authorization': 'Key ' + response.json['key']
    })
    assert response.status == '200 OK'
    assert response.json['credits'] == 0


def test_get_credits_with_deleted_api_key(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    jwt = response.json['access']

    response = client.post('/v1/key', headers={
        'Authorization': 'Bearer ' + jwt
    })
    assert response.status == '201 CREATED'
    assert len(response.json['key']) == 43

    key = response.json['key']

    response = client.get('/v1/credits', headers={
        'Authorization': 'Key ' + key
    })
    assert response.status == '200 OK'
    assert response.json['credits'] == 0

    response = client.delete('/v1/key?key=' + key, headers={
        'Authorization': 'Bearer ' + jwt,
    })
    assert response.status == '204 NO CONTENT'

    response = client.get('/v1/credits', headers={
        'Authorization': 'Key ' + key
    })
    assert response.status == '401 UNAUTHORIZED'


def test_upload_file_and_get(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    jwt = response.json['access']

    data = open('./tests/sample.mp3', 'rb')
    data = {'file': (data, 'sample.mp3')}
    response = client.post('/v1/upload', headers={
        'Authorization': 'Bearer ' + jwt
    }, data = data, buffered=True, content_type='multipart/form-data')
    assert response.status == '200 OK'
    assert len(response.json['filename']) > 10

    response = client.get('/v1/upload', headers={
        'Authorization': 'Bearer ' + jwt
    })
    assert len(response.json['uploads']) > 0
    assert response.json['uploads'][0]['original_name'] == 'sample.mp3'


def test_upload_file_and_transcribe_without_credits(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    jwt = response.json['access']

    data = open('./tests/sample.mp3', 'rb')
    data = {'file': (data, 'sample.mp3')}
    response = client.post('/v1/upload', headers={
        'Authorization': 'Bearer ' + jwt
    }, data = data, buffered=True, content_type='multipart/form-data')
    assert response.status == '200 OK'
    assert len(response.json['filename']) > 10

    response = client.get('/v1/transcription?filename=' + response.json['filename'], headers={
        'Authorization': 'Bearer ' + jwt
    })
    assert response.status == '400 BAD REQUEST'
    assert response.json['message'] == 'Not enough credits'


def test_upload_file_and_transcribe_and_credit_check(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    mongo['speechwave-test']['users'].update_one({'email': 'a@a.com'}, {'$inc': { 'credits': 100 }})

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    jwt = response.json['access']

    data = open('./tests/sample.mp3', 'rb')
    data = {'file': (data, 'sample.mp3')}
    response = client.post('/v1/upload', headers={
        'Authorization': 'Bearer ' + jwt
    }, data = data, buffered=True, content_type='multipart/form-data')
    assert response.status == '200 OK'
    assert len(response.json['filename']) > 10

    response = client.get('/v1/transcription?filename=' + response.json['filename'], headers={
        'Authorization': 'Bearer ' + jwt
    })
    assert response.status == '200 OK'
    assert response.json['message'] == 'Transcription is in progress. Make the same request again later to fetch the results.'

    response = client.get('/v1/credits?detailed=true', headers={
        'Authorization': 'Bearer ' + jwt
    })
    assert response.status == '200 OK'
    assert response.json['credits'] < 100
    assert response.json['history'][0]['type'] == 'deduct'
    assert response.json['history'][0]['amount'] > 0
    assert response.json['history'][0]['filename'] == 'sample.mp3'


def test_upload_file_and_transcribe_and_credit_check_with_api_key(client):
    response = client.post('/v1/register', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '201 CREATED'

    mongo['speechwave-test']['users'].update_one({'email': 'a@a.com'}, {'$inc': { 'credits': 100 }})

    response = client.post('/v1/login', json={
        'email': 'a@a.com',
        'password': 'atleast6chars'
    })
    assert response.status == '200 OK'

    response = client.post('/v1/key', headers={
        'Authorization': 'Bearer ' + response.json['access']
    })
    assert response.status == '201 CREATED'
    assert len(response.json['key']) == 43

    key = response.json['key']

    data = open('./tests/sample.mp3', 'rb')
    data = {'file': (data, 'sample.mp3')}
    response = client.post('/v1/upload', headers={
        'Authorization': 'Key ' + key
    }, data = data, buffered=True, content_type='multipart/form-data')
    assert response.status == '200 OK'
    assert len(response.json['filename']) > 10

    response = client.get('/v1/transcription?filename=' + response.json['filename'], headers={
        'Authorization': 'Key ' + key
    })
    assert response.status == '200 OK'
    assert response.json['message'] == 'Transcription is in progress. Make the same request again later to fetch the results.'

    response = client.get('/v1/credits?detailed=true', headers={
        'Authorization': 'Key ' + key
    })
    assert response.status == '200 OK'
    assert response.json['credits'] < 100
    assert response.json['history'][0]['type'] == 'deduct'
    assert response.json['history'][0]['amount'] > 0
    assert response.json['history'][0]['filename'] == 'sample.mp3'

