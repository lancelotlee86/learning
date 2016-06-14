#!/usr/bin/env python3

import socket
import sys
import argparse


host = 'localhost'
data_payload = 2048
backlog = 5

def echo_server(port):
    """
    A simple echo server
    :param port:
    :return:
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Enable reuse address/port
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # Bind the socket to the port
    server_address = (host, port)
    print("Starting up echo server on %s port %s" % (server_address[0], server_address[1]))
    sock.bind(server_address)

    sock.listen(backlog)
    while True:
        print("Waiting to receive message from client")
        client, address = sock.accept()
        data = client.recv(data_payload)
        if data:
            print("Data: %s" % data)
            client.send(data)
            print("sent %s bytes back to %s" % (len(data), address))
        client.close()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Socket Server Example')
    parser.add_argument('--port', action="store", dest="port", type=int, required=True)
    given_args = parser.parse_args()
    port = given_args.port

    echo_server(port)