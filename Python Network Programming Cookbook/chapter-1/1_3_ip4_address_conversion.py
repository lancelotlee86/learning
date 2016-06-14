#!usr/bin/env python3


import socket
from binascii import hexlify


def convert_ip4_address():
    for ip_addr in ['127.0.0.1', '192.168.0.1']:
        packed_id_addr = socket.inet_aton(ip_addr)
        unpacked_ip_addr = socket.inet_ntoa(packed_id_addr)
        print("IP address: %s =>  Packed: %s  Unpacked: %s" % (ip_addr, hexlify(packed_id_addr), unpacked_ip_addr) )


if __name__ == '__main__':
    convert_ip4_address()