from django.shortcuts import render
from rest_framework import viewsets
from raisins.jobs.models import Job
from .models import CandidateJobStep, Candidate
from .serializers import CandidateJobStepSerializer, CandidateSerializer


class CandidateJobStepViewSet(viewsets.ModelViewSet):
    queryset = CandidateJobStep.objects.all()
    serializer_class = CandidateJobStepSerializer


class CandidateViewSet(viewsets.ModelViewSet):
    queryset = Candidate.objects.all()
    serializer_class = CandidateSerializer

    def create(self, request, *args, **kwargs):
        response = super(CandidateViewSet, self).create(request, *args, **kwargs)
        if 'job' in request.data:
            Candidate.objects.get(pk=response.data['id']).jobs.add(request.data['job'])
            CandidateJobStep.objects.create(
                job=Job.objects.get(pk=request.data['job']),
                step=request.data['stage'],
                candidate=Candidate.objects.get(pk=response.data['id'])
            )
        response.data = {'id': response.data['id']}
        return response
