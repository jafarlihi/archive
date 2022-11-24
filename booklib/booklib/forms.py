from flask_wtf import FlaskForm
from flask_wtf.file import FileField, FileAllowed, FileRequired
from wtforms.fields import StringField, IntegerField
from wtforms.validators import DataRequired, NumberRange, Optional


class AddBookForm(FlaskForm):
    name = StringField('name', validators=[DataRequired()])
    author = StringField('author', validators=[DataRequired()])
    release_date = IntegerField('release_date', validators=[Optional(), NumberRange(0, 9999)])
    image = FileField('image', validators=[Optional(), FileAllowed(['jpg', 'png'], 'Images only!')])
    pdf = FileField('pdf', validators=[FileRequired(), FileAllowed(['pdf'], 'Documents only!')])
