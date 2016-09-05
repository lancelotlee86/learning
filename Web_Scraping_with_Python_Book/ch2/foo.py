import urllib.request
import re
import socks
import socket


socks.set_default_proxy(socks.SOCKS5, '127.0.0.1', 1080)
socket.socket = socks.socksocket


def download(url, headers, num_retries=2):
    print('Downloading:', url)
    request = urllib.request.Request(url, headers=headers)
    try:
        html = urllib.request.urlopen(request).read()
    except urllib.error.HTTPError as e:
        print('Download error: ', e.reason)
        html = None
        if num_retries > 0:
            if hasattr(e, 'code') and 500 <= e.code < 600:
                # retry 5xx HTTP errors
                return download(url, user_agent, num_retries - 1)
    return html


def crawl_sitemap(url):
    # download the sitemap file
    sitemap = download(url)
    # extract the sitemap links
    links = re.findall('<loc>(.*?)</loc>', sitemap.decode('utf8'))
    # download each link
    for link in links:
        print(link)
        #html = download(link)


#print(download('http://www.google.com'))
#print(download('http://httpstat.us/503'))
#crawl_sitemap('http://example.webscraping.com/sitemap.xml')