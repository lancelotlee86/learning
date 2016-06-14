#!/usr/bin/env python3

import socket


def print_machine_info():
    # gethostname()是返回主机名
    host_name = socket.gethostname()
    # gethostbyname(gethostname()) 返回主机名对应的IP地址字符串
    ip_address = socket.gethostbyname(host_name)
    print("Host name: " + host_name)
    print("IP address: " + ip_address)

if __name__ == "__main__":
    print_machine_info()