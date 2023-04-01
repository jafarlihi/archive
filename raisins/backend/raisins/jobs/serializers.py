from rest_framework import serializers
from django_countries.serializers import CountryFieldMixin
from .models import Job


class JobSerializer(CountryFieldMixin, serializers.ModelSerializer):
    class Meta:
        model = Job
        fields = '__all__'
