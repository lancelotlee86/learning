#!/usr/bin/env python3

import socket

def test_socket_number():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setblocking(True)
    s.settimeout(0.5)
    s.bind(("127.0.0.1", 0))

    socket_address = s.getsockname()
    print("Trivial Server launched on socket: %s" % str(socket_address))
    while(1):
        s.listen(1)


if __name__ == '__main__':
    test_socket_number()
