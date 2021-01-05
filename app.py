from flask import Flask, request, Response
from nrf import *

HOST = '0.0.0.0'
PORT = '8080'

app = Flask(__name__)
nrf = NRF()


@app.route('/color-button', methods=['POST'])
def color():
    cont = request.form.to_dict(flat=True)
    try:
        button = int(cont['button'])
        if not (button >= 1 and button <= 24):
            raise ValueError
        nrf.send(cont['button'])
        print(cont['button'])
    except Exception as e:
        print(e)
        return Response(status=500)
    return Response(status=200)


if __name__ == '__main__':
    app.run(host=HOST, port=PORT, debug=False)
