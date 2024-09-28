from flask import Flask, render_template, request, redirect, url_for
import requests

app = Flask(__name__)

VILLAGE_SERVER_URL = "I'll use my ngrok URL/upload"

@app.route('/', methods=['GET'])
def index():
    return render_template('dash.html')

@app.route('/upload', methods=['POST'])
def upload():
    zip_file = request.files.get('zip_file')
    csv_file = request.files.get('csv_file')
    
    if zip_file and csv_file:
        files = {
            'zip_file': (zip_file.filename, zip_file.read(), zip_file.content_type),
            'csv_file': (csv_file.filename, csv_file.read(), csv_file.content_type)
        }
        
        try:
            response = requests.post(VILLAGE_SERVER_URL, files=files)
            if response.status_code == 200:
                return 'Files uploaded successfully!'
            else:
                return f'Failed to upload files: {response.status_code} {response.text}'
        except Exception as e:
            return f'Error occurred: {str(e)}'
    else:
        return 'Please provide both a ZIP file and a CSV file.'
    
@app.route('/login', methods=['GET'])
def login():
    return render_template('login_admin.html')    

if __name__ == '__main__':
    app.run(debug=True, port=5000)
