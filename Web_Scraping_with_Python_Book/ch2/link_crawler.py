import urllib.parse
import urllib.robotparser
import re
from foo import download
import datetime
import time

print('abc')
def link_crawler(seed_url, link_regex=None, delay=0, headers=None, user_agent='wswp', num_retries=1, max_depth=2, max_urls=-1, scrape_callback=None):
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

    throttle = Throttle(delay)

    while crawl_queue:
        url = crawl_queue.pop()
        # 检查robot.txt是否允许
        if rp.can_fetch(user_agent, url):
            throttle.wait(url)
            html = download(url, headers, num_retries=num_retries)
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



class Throttle:
    '''对于统一域名下的网址之间的访问增加一个访问间隔'''
    def __init__(self, delay):
        self.delay = delay
        self.domains = {}

    def wait(self, url):
        domain = urllib.parse.urlparse(url).netloc
        last_accessed = self.domains.get(domain)

        if self.delay > 0 and last_accessed is not None:
            sleep_secs = self.delay - (datetime.datetime.now() - last_accessed).seconds
            if sleep_secs > 0:
                # 该域名最近被访问过
                time.sleep(sleep_secs)
        # 更新最后一次访问时间
        self.domains[domain] = datetime.datetime.now()


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


#link_crawler('http://example.webscraping.com', '/(index|view)')