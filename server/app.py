#!flask/bin/python
from flask import Flask, json, request, jsonify
from pprint import pprint

from common.types import Challenge
from challenges import mastermind

app = Flask(__name__)

tasks = [
    {
        'id': 1,
        'title': u'Buy groceries',
        'description': u'Milk, Cheese, Pizza, Fruit, Tylenol',
        'done': False
    },
    {
        'id': 2,
        'title': u'Learn Python',
        'description': u'Need to find a good Python tutorial on the web',
        'done': False
    }
]


@app.route('/')
def index():
    return "Welcome to GraderServer"


@app.route('/test', methods=['POST'])
def api_message():
    pprint(request.form)

    if request.headers['Content-Type'] == 'text/plain':
        return "Text Message: " + request.data

    elif request.headers['Content-Type'] == 'application/json':
        return "JSON Message: " + json.dumps(request.json)

    else:
        return "415 Unsupported Media Type"


@app.route('/CreateChallenge/<challenge_type>/', methods=['GET'])
def new_game(challenge_type):
    challenge_type_to_response = {Challenge.MASTERMIND.value: mastermind.request_new_game}

    try:
        response_dict = challenge_type_to_response[int(challenge_type)]()
        response = jsonify(response_dict)
    except KeyError:
        response = "Invalid Challenge type "

    print("Responding: {}".format(response))
    return response


if __name__ == '__main__':
    app.run(debug=True)
