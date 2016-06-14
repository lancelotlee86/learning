#!usr/bin/env python3


import socket


def find_service_name():
    protocolname = 'tcp'
    for port in [80, 25]:
        print("Port: %s  =>  service name: %s" % (port, socket.getservbyport(port, protocolname)))
        # 在socket.getservbyport()中，如果提供的端口无法找到服务名，则会报错，真正在用这个函数是要注意捕捉错误
    print("Port: %s  =>  service name: %s" % (53, socket.getservbyport(53, 'udp')))


if __name__ == '__main__':
    find_service_name()
