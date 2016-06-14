#!/usr/bin/env python3

import ntplib
from time import ctime


def print_time():
    ntp_client = ntplib.NTPClient()
    response = ntp_client.request('210.72.145.44')
    print(ctime(response.tx_time))

if __name__ == '__main__':
    print_time()
