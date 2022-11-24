import os
from flask import render_template, flash, redirect, url_for
from werkzeug.utils import secure_filename

from booklib import app, db
from booklib.forms import AddBookForm
from booklib.models import Book


@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html', new_books=Book.new_books(10))


@app.route('/add', methods=['GET', 'POST'])
def add_book():
    form = AddBookForm()
    if form.validate_on_submit():
        name, author, release_date = form.name.data, form.author.data, form.release_date.data
        image, pdf = form.image.data, form.pdf.data

        pdff = os.path.join('static/pdf',
                            secure_filename(name.replace(' ', '_') + '-' + author.replace(' ', '_') + '.pdf'))
        pdf.save('booklib/' + pdff)

        imagef = os.path.join('booklib/static/img', '/no-image.jpg')

        if image:
            _, imageExt = os.path.splitext(image.filename)
            imagef = os.path.join('static/img',
                                  secure_filename(name.replace(' ', '_') + '-' + author.replace(' ', '_') + imageExt))
            image.save('booklib/' + imagef)

        b = Book(name=name, author=author, release_date=release_date, image_filename=imagef, pdf_filename=pdff)
        db.session.add(b)
        db.session.commit()

        flash("Added book '{}' successfully!".format(name))
        app.logger.debug('stored book: ' + name)

        return redirect(url_for('index'))
    return render_template('addBook.html', form=form)


@app.errorhandler(404)
def not_found_404(e):
    return render_template('error-pages/404.html'), 404


@app.errorhandler(500)
def error_500(e):
    return render_template('error-pages/500.html'), 500
