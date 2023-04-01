from rest_framework import serializers
from .models import CandidateJobStep, Candidate


class CandidateJobStepSerializer(serializers.ModelSerializer):
    class Meta:
        model = CandidateJobStep
        fields = '__all__'


class CandidateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Candidate
        fields = '__all__'
