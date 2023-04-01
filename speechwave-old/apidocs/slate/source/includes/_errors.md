# Errors

The Speechwave API uses the following error codes:


Error Code | Meaning
---------- | -------
400 | Bad Request -- Your request is invalid.
401 | Unauthorized -- Your JWT token is wrong or not provided.
404 | Not Found -- The specified endpoint could not be found.
405 | Method Not Allowed -- You tried to access an endpoint with invalid method.
409 | Conflict -- You tried to create an account for email that is already registered.
429 | Too Many Requests -- You are being rate-limited.
500 | Internal Server Error -- We had a problem with our server. Try again later.
503 | Service Unavailable -- We're temporarily offline for maintenance. Please try again later.
