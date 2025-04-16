from flask import Flask, request, jsonify
from mongoDao import MongoDao

app = Flask(__name__)
dao = MongoDao()

@app.route('/', methods=['POST'])
def receive_json():
    return jsonify({'status': 'ok'})

@app.route('/ping', methods=['GET'])
def getPing():
    return jsonify({'status': 'ok'})

@app.route('/getTree', methods=['GET'])
def getTree():
    return jsonify(dao.getData())

@app.route('/putTree', methods=['POST'])
def putTree():
    data = request.get_json()
    dao.postData(data)

    return jsonify({'status': 'ok'})

if __name__ == '__main__':

    app.run(port=8000)