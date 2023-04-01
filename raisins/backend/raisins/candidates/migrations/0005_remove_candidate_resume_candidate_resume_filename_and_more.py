# Generated by Django 4.1.1 on 2022-10-09 10:45

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('candidates', '0004_alter_candidate_jobs'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='candidate',
            name='resume',
        ),
        migrations.AddField(
            model_name='candidate',
            name='resume_filename',
            field=models.CharField(blank=True, max_length=512, null=True),
        ),
        migrations.AlterField(
            model_name='candidate',
            name='cover_letter',
            field=models.CharField(blank=True, max_length=20000, null=True),
        ),
    ]
