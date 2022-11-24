from datetime import datetime

from sqlalchemy import desc

from booklib import db


class Book(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.Text, nullable=False)
    author = db.Column(db.Text, nullable=False)
    release_date = db.Column(db.Integer, nullable=True)
    date_added = db.Column(db.DateTime, default=datetime.utcnow)
    image_filename = db.Column(db.Text, nullable=True)
    pdf_filename = db.Column(db.Text, nullable=False)

    @staticmethod
    def new_books(count):
        return Book.query.order_by(desc(Book.date_added)).limit(count)

    def __repr__(self):
        return "<Book '{}' - '{}'>".format(self.name, self.author)
