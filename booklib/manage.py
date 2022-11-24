#! /usr/bin/env python

from flask_script import Manager, prompt_bool
from booklib import app, db

manager = Manager(app)


@manager.command
def initdb():
    db.create_all()
    print('Database was initialized!')


@manager.command
def dropdb():
    if prompt_bool(
            "Are you sure that you want to drop the database?"):
        db.drop_all()
        print('Database was dropped.')


if __name__ == '__main__':
    manager.run()
