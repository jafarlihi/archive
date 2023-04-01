from django.db import models
from django.contrib import admin
from django.conf import settings


class Tag(models.Model):
    name = models.CharField(max_length=255)


admin.site.register(Tag)


class Department(models.Model):
    name = models.CharField(max_length=255)


admin.site.register(Department)


class Job(models.Model):
    class RequirementType(models.TextChoices):
        REQUIRED = 'R', 'Required'
        OPTIONAL = 'O', 'Optional'
        HIDDEN = 'H', 'Hidden'

    class Location(models.TextChoices):
        REMOTE = 'R', 'Remote'
        HYBRID = 'H', 'Hybrid'
        ONSITE = 'O', 'On-site'

    title = models.CharField(max_length=255)
    department = models.ForeignKey(Department, null=True, blank=True, on_delete=models.SET_NULL)
    recruiter = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.SET_NULL, related_name='recruiter', null=True, blank=True)
    hiring_manager = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.SET_NULL, related_name='hiring_manager', null=True, blank=True)
    tags = models.ManyToManyField(Tag, blank=True)
    description = models.CharField(max_length=20000, null=True, blank=True)
    requirements = models.CharField(max_length=20000, null=True, blank=True)
    address = models.CharField(max_length=2048, null=True, blank=True)
    location = models.CharField(max_length=1, choices=Location.choices, null=True, blank=True)
    resume = models.CharField(max_length=1, choices=RequirementType.choices, null=True, blank=True)
    cover_letter = models.CharField(max_length=1, choices=RequirementType.choices, null=True, blank=True)
    phone = models.CharField(max_length=1, choices=RequirementType.choices, null=True, blank=True)
    pipeline = models.JSONField(null=True, blank=True)
    created_at = models.DateTimeField(auto_now_add=True)
    updated_at = models.DateTimeField(auto_now=True)


admin.site.register(Job)
