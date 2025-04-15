from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/', methods=['POST'])
def receive_json():
    data = request.get_json()
    print("Received JSON:", data)
    return jsonify({'status': 'ok'})

@app.route('/ping', methods=['GET'])
def getPing():
    return jsonify({'status': 'ok'})

@app.route('/getTree', methods=['GET'])
def getTree():
    return jsonify({'status': 'ok'})

@app.route('/putTree', methods=['POST'])
def putTree():
    data = request.get_json()
    print("Put Tree Received Data: ", data)
    return jsonify({'status': 'ok'})

if __name__ == '__main__':
    app.run(port=8000)