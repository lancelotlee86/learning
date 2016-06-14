#!usr/bin/env python3


import sys
import socket
import argparse


def main():
    # setup argument parsing
    parser = argparse.ArgumentParser(description = 'Socket Error Examples')
    parser.add_argument('--host', action = "store", dest = "host", required = False)
    parser.add_argument('--port', action = "store", dest = "port", type = int, required = False)
    parser.add_argument('--file', action = "store", dest = "file", required = False)
    given_args = parser.parse_args()
    host = given_args.host
    port = given_args.port
    filename = given_args.file

    # 第一个try-except块 ---- 创建socket
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error as e:
        print("Error creating socket: %s" % e)
        sys.exit(1)


    # 第二个try-except块 ---- 连接到给定的 host/port
    try:
        s.connect((host, port))
    except socket.gaierror as e:
        print("Address-related error connecting to server: %s" % e)
        sys.exit(1)
    except socket.error as e:
        print("Connection error: %s" % e)
        sys.exit(1)
    except TypeError as e:
        print("莫名其妙的TypeError")
        sys.exit(1)


    # 第三个try-except块 ---- 发送 data
    try:
        data = "GET %b HTTP/1.0\r\n\r\n"
        s.sendall(("GET %s HTTP/1.0\r\n\r\n" % filename).encode('utf-8'))
    except socket.error as e:
        print("Error sending data: %s" % e)
        sys.exit(1)


    while(1):
        # 第三个try-except块 ---- 等待接收远程主机的数据
        try:
            buf = s.recv(2048)
        except socket.error as e:
            print("Error receiving data: %s" % e)
            sys.exit(1)
        if not len(buf):
            break
        # 输出接收的数据
        # 由于是 bytes，所以要用sys.stdout.buffer.write
        sys.stdout.buffer.write(buf)


if __name__ == '__main__':
    main()