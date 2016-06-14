#!/usr/bin/env python3

import socket
import sys


def reuse_socket_addr():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # 取得 SO_REUSEADDR 操作之前的状态
    old_state = sock.getsockopt(socket.SOCK_STREAM, socket.SO_REUSEADDR, 1)
    print("Old sock state: %s" % old_state)

    # enable the SO_REUSEADDR option
    sock.setsockopt(socket.SOCK_STREAM, socket.SO_REUSEADDR, 1)
    new_state = sock.getsockopt(socket.SOCK_STREAM, socket.SO_REUSEADDR, 1)
    print("New sock state: %s" % new_state)

    local_port = 8281

    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOCK_STREAM, socket.SO_REUSEADDR, 1)
    srv.bind(('', local_port))
    print("Listening on port: %s" % local_port)

    while(True):
        try:
            """
            something wrong goes here...
            """
            connection, addr = srv.accept()
            print("Connected by %s:%s" % (addr[0], addr[1]))
        except KeyboardInterrupt:
            break
        except socket.error as msg:
            print("%s" % (msg,))


if __name__ == '__main__':
    reuse_socket_addr()