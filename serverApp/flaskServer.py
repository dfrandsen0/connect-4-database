from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def receive_json():
    data = request.get_json()
    print("Received JSON:", data)
    return jsonify({'status': 'ok'})

if __name__ == '__main__':
    app.run(port=8000)