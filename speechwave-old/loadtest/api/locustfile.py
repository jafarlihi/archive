from locust import HttpUser, task
from faker import Faker
from pymongo import MongoClient
import json


class SpeechwaveUser(HttpUser):
    def __init__(self, parent):
        super(SpeechwaveUser, self).__init__(parent)
        self.token = ''
        self.headers = {}

    def on_start(self):
        self.token = self.register_and_login()
        self.headers = {'Authorization': 'Bearer ' + self.token}

    def register_and_login(self):
        password = Faker().password()
        email = Faker().email()
        self.client.post('/v1/register', json={'email': email, 'password': password})
        response = self.client.post('/v1/login', json={'email': email, 'password': password})
        MongoClient('mongodb://localhost:27017')['speechwave']['users'].update_one({'email': email}, {'$set': {'credits': 100000000}})
        return json.loads(response.content)['access']

    @task
    def get_credits(self):
        self.client.get('/v1/credits', headers=self.headers)

    @task
    def get_uploads(self):
        self.client.get('/v1/upload', headers=self.headers)

    @task
    def upload_and_transcribe(self):
        file = open('sample.mp3', 'rb')
        response = self.client.post('/v1/upload', headers=self.headers, files={'file': file})
        self.client.get('/v1/transcription?filename=' + json.loads(response.content)['filename'], headers=self.headers, name='/v1/transcription')

