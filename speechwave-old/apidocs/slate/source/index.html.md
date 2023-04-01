---
title: API Reference

language_tabs: # must be one of https://git.io/vQNgJ
  - shell

toc_footers:
  - <a href='https://speechwave.ai'>Speechwave</a>

includes:
  - errors

search: true

code_clipboard: true

meta:
  - name: description
    content: Documentation for the Speechwave API
---

# Introduction

Welcome to the Speechwave API! With this API you can upload video and audio files and queue them for transcription, then later fetch the results.

# Authentication

> To authorize, use this code:

```shell
curl "api_endpoint_here" \
  --header "Authorization: Key <API Key>"
```

> Make sure to replace `<API Key>` with your API key.

You can generate an API key by clicking on the button at the top right of your dashboard.

Speechwave expects the API key to be included in all API requests to the server in a header that looks like the following:

`Authorization: Key <API Key>`

<aside class="notice">
You must replace <code>&lt;API Key&gt;</code> with your personal API key.
</aside>

# Endpoints

## Get Credits

```shell
curl --request GET \
  --header "Authorization: Key <API Key>" \
  https://speechwave.ai/api/v1/credits
```

> The above command returns JSON structured like this:

```json
{
  "credits": 100
}
```

This endpoint returns the number of credits you have available.

### HTTP Request

`GET https://speechwave.ai/api/v1/credits`

### Query Parameters

Parameter | Description
--------- | -----------
detailed | If 'true' then credit history is returned as well

## Get Uploads

```shell
curl --request GET \
  --header "Authorization: Key <API Key>" \
  https://speechwave.ai/api/v1/upload
```

> The above command returns JSON structured like this:

```json
{
    "uploads": [
        {
            "_id": {
                "$oid": "634bd765d0c92f787073f690"
            },
            "cost": 1,
            "email": "your@email.com",
            "filename": "39b7a3e0-c4d4-4a26-848d-f8535a2df8fc.mp3",
            "original_name": "sample-1.mp3",
            "status": "In progress",
            "uploaded_at": {
                "$date": "2022-10-16T14:05:25.530Z"
            }
        },
        {
            "_id": {
                "$oid": "634bd77ec18f11cf0bf4d84d"
            },
            "cost": 100,
            "email": "your@email.com",
            "filename": "130bac22-f53f-4f21-85aa-5fef3b121108.mp3.translate",
            "original_name": "sample-2.mp4",
            "status": "Done",
            "srt": "https://speechwave.ai/download/sample-2.mp4.srt",
            "txt": "https://speechwave.ai/download/sample-2.mp4.txt",
            "vtt": "https://speechwave.ai/download/sample-2.mp4.vtt",
            "uploaded_at": {
                "$date": "2022-10-16T14:05:50.008Z"
            }
        },
    ],
}
```

This endpoint returns a list of uploads that you have made.

### HTTP Request

`GET https://speechwave.ai/api/v1/upload`

## Upload

```shell
curl --request POST \
  --form "file=@/path/to/your/file/sample.mp4" \
  --header "Authorization: Key <API Key>" \
  https://speechwave.ai/api/v1/upload
```

> The above command uploads a new video or audio file to Speechwave.

```json
{
  "message": "Upload was successful",
  "filename": "123e4567-e89b-12d3-a456-426614174000.mp4"
}
```

This endpoint uploads a new video or audio file to Speechwave. It returns a unique filename associated to the upload, which you can later use with `transcription` endpoint. Accepted formats are '3gp', 'aiff', 'avi', 'flac', 'flv', 'm4a', 'mkv', 'mov', 'mp3', 'mp4', 'ogg', 'wav', 'webm', 'wma', 'wmv'.

### HTTP Request

`POST https://speechwave.ai/api/v1/upload`

### Form Data Parameters

Name | Description
--------- | -----------
file | The video or audio file you want to upload
translate | If 'true' then the transcription will be translated to English
language | If there's no speech within the first 30 seconds of the uploaded file then the language has to be specified manually. One of these: 'Afrikaans', 'Albanian', 'Amharic', 'Arabic', 'Armenian', 'Assamese', 'Azerbaijani', 'Bashkir', 'Basque', 'Belarusian', 'Bengali', 'Bosnian', 'Breton', 'Bulgarian', 'Burmese', 'Castilian', 'Catalan', 'Chinese', 'Croatian', 'Czech', 'Danish', 'Dutch', 'English', 'Estonian', 'Faroese', 'Finnish', 'Flemish', 'French', 'Galician', 'Georgian', 'German', 'Greek', 'Gujarati', 'Haitian', 'Haitian Creole', 'Hausa', 'Hawaiian', 'Hebrew', 'Hindi', 'Hungarian', 'Icelandic', 'Indonesian', 'Italian', 'Japanese', 'Javanese', 'Kannada', 'Kazakh', 'Khmer', 'Korean', 'Lao', 'Latin', 'Latvian', 'Letzeburgesch', 'Lingala', 'Lithuanian', 'Luxembourgish', 'Macedonian', 'Malagasy', 'Malay', 'Malayalam', 'Maltese', 'Maori', 'Marathi', 'Moldavian', 'Moldovan', 'Mongolian', 'Myanmar', 'Nepali', 'Norwegian', 'Nynorsk', 'Occitan', 'Panjabi', 'Pashto', 'Persian', 'Polish', 'Portuguese', 'Punjabi', 'Pushto', 'Romanian', 'Russian', 'Sanskrit', 'Serbian', 'Shona', 'Sindhi', 'Sinhala', 'Sinhalese', 'Slovak', 'Slovenian', 'Somali', 'Spanish', 'Sundanese', 'Swahili', 'Swedish', 'Tagalog', 'Tajik', 'Tamil', 'Tatar', 'Telugu', 'Thai', 'Tibetan', 'Turkish', 'Turkmen', 'Ukrainian', 'Urdu', 'Uzbek', 'Valencian', 'Vietnamese', 'Welsh', 'Yiddish', 'Yoruba'.

## Transcription

```shell
curl --request GET \
  --header "Authorization: Key <API Key>" \
  --get \
  --data-urlencode "filename=123e4567-e89b-12d3-a456-426614174000.mp4" \
  https://speechwave.ai/api/v1/transcription
```

> The above command starts the transcription process if called the first time. When called later second time it either returns a message indicating that transcription process is still in progress or download links to the results.

```json
{
  "message": "Transcription is in progress. Make the same request again later to fetch the results."
}
OR
{
  "txt": "https://speechwave.ai/download/filename.mp4.txt",
  "srt": "https://speechwave.ai/download/filename.mp4.srt",
  "vtt": "https://speechwave.ai/download/filename.mp4.vtt"
}
```

This endpoint kickstarts the transcription process first time it's called, subsequent calls either return a message indicating that the process is still in progress or the download links for the transcription result.

### HTTP Request

`GET https://speechwave.ai/api/v1/transcription`

### Query Parameters

Parameter | Description
--------- | -----------
filename | Filename returned by the `upload` call

