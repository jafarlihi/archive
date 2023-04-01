import uuid
import os.path
from django.core.files.storage import default_storage
from django.core.files.base import ContentFile
from rest_framework.parsers import FileUploadParser, MultiPartParser
from rest_framework.views import APIView
from rest_framework.response import Response

class AvatarFileUploadView(APIView):
    parser_classes = (MultiPartParser,FileUploadParser,)

    def put(self, request, filename, format=None):
        file_obj = request.data['file']
        extension = os.path.splitext(filename)[1]
        file_uuid = uuid.uuid4();
        path = default_storage.save('media/' + str(file_uuid) + extension, ContentFile(file_obj.read()))
        return Response({ 'filename': str(file_uuid) + extension })
