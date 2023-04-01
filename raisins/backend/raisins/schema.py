import graphene
from graphene_django import DjangoObjectType

from raisins.jobs.models import Department, Tag, Job
from raisins.candidates.models import Candidate, CandidateJobStep

class DepartmentType(DjangoObjectType):
    class Meta:
        model = Department
        fields = ('id', 'name')

class TagType(DjangoObjectType):
    class Meta:
        model = Tag
        fields = ('id', 'name')

class JobType(DjangoObjectType):
    class Meta:
        model = Job
        fields = ('id', 'title', 'department', 'recruiter', 'hiring_manager', 'tags', 'description', 'requirements', 'location', 'address', 'resume', 'cover_letter', 'phone', 'pipeline', 'updated_at', 'created_at', 'candidate_set')

class CandidateJobStepType(DjangoObjectType):
    class Meta:
        model = CandidateJobStep
        field = ('candidate', 'job', 'step')


class CandidateType(DjangoObjectType):
    class Meta:
        model = Candidate
        fields = ('id', 'fullname', 'email', 'phone', 'jobs', 'address', 'salary_expectation', 'timezone', 'steps', 'resume_filename', 'cover_letter', 'created_at', 'updated_at')


class Query(graphene.ObjectType):
    all_jobs = graphene.List(JobType)
    all_candidates = graphene.List(CandidateType)
    job_by_id = graphene.Field(JobType, id=graphene.ID(required=True))
    candidate_by_id = graphene.Field(CandidateType, id=graphene.ID(required=True))

    def resolve_all_jobs(root, info):
        return Job.objects.all()

    def resolve_all_candidates(root, info):
        return Candidate.objects.all()

    def resolve_job_by_id(root, info, id):
        try:
            return Job.objects.get(id=id)
        except Job.DoesNotExist:
            return None

    def resolve_candidate_by_id(root, info, id):
        try:
            return Candidate.objects.get(id=id)
        except Candidate.DoesNotExist:
            return None


schema = graphene.Schema(query=Query)
