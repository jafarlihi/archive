gcsfuse zinc-bucket-1 /hpme/user/input-bucket/

gcsfuse zinc-bucket-2 /home/user/output-bucket/

sudo systemctl start mongodb

sudo systemctl start nginx

gunicorn --bind 127.0.0.1:8080 main:app --timeout 10000 -w 10

