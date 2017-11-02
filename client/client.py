import requests

if __name__ == "__main__":
    r = requests.get('http://127.0.0.1:5000/')
    print "Received " + str(r)

    r = requests.get('http://127.0.0.1:5000/test')
    print "Received " + str(r)

    r = requests.post('http://127.0.0.1:5000/test',
                      data={'Command': 'RequestStartGame', 'Args': {'Name': 'Mastermind'}})

    print "Received " + str(r.text)
