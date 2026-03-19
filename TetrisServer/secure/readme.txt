Open a CMD with a folder and get bored with it:
openssl req -x509 -newkey rsa:4096 -keyout key.pem -out cert.pem -sha256 -days 365 -nodes -subj "//CN=localhost"