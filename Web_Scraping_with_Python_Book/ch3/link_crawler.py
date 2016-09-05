import urllib.parse
import urllib.robotparser
import re
from downloader import Downloader
import datetime
import time

print('abc')
def link_crawler(seed_url, link_regex=None, delay=0, headers=None, user_agent='wswp', proxies=None, num_retries=1, max_depth=2, max_urls=-1, scrape_callback=None, cache=None):
    ''' '''
    crawl_queue = [seed_url]
    # 将看过的URL存储起来
    seen = {seed_url: 0}
    num_urls = 0
    if user_agent:
        headers = {}
        headers['User-agent'] = user_agent

    rp = urllib.robotparser.RobotFileParser()
    rp.set_url('http://example.webscraping.com/robots.txt')
    rp.read()

    D = Downloader(delay=delay, user_agent=user_agent, proxies=proxies, num_retries=num_retries, cache=cache)

    while crawl_queue:
        url = crawl_queue.pop()
        # 检查robot.txt是否允许
        if rp.can_fetch(user_agent, url):
            html = D(url)
            links = []

            if scrape_callback:
                links.extend(scrape_callback(url, html) or [])

            depth = seen[url]
            if depth != max_depth:
                if link_regex:
                    links.extend(link for link in get_links(html) if re.match(link_regex, link))
                # 过滤符合我的的正则表达式的链接
                for link in links:
                    link = normalize(seed_url, link)
                    if link not in seen:
                        seen[link] = depth + 1
                        if same_domain(seed_url, link):
                            crawl_queue.append(link)

            num_urls += 1
            if num_urls == max_urls:
                break
        else:
            print('Blocked by robots.txt: ', url)



def get_links(html):
    '''从给定的html代码中返回一组链接的列表'''
    # 从网页中用正则表达式提取所有的链接
    webpage_regex = re.compile('<a[^>]+href=["\'](.*?)["\']', re.IGNORECASE)
    return webpage_regex.findall(html.decode('utf8'))


def normalize(seed_url, link):
    ''' 标准化URL,通过出去＃并且加上域名'''
    link, _ = urllib.parse.urldefrag(link)
    return urllib.parse.urljoin(seed_url, link)


def same_domain(url1, url2):
    return urllib.parse.urlparse(url1).netloc == urllib.parse.urlparse(url2).netloc



if __name__ == '__main__':
    import socks
    import socket

    socks.set_default_proxy(socks.SOCKS5, '127.0.0.1', 1080)
    socket.socket = socks.socksocket

    #link_crawler('http://example.webscraping.com', '/(index|view)', delay=0, num_retries=1, user_agent='BadCrawler')
    link_crawler('http://example.webscraping.com', '/(index|view)', delay=0, num_retries=1, max_depth=1, user_agent='GoodCrawler')
