import urllib
import random
import datetime

class Downloader:
    def __init__(self, delay=5,
                 user_agent='wswp', proxies=None,
                 num_retries=1, cache=None):
        self.throttle = Throttle(delay)
        self.user_agent = user_agent
        self.proxies = proxies
        self.num_retries = num_retries
        self.cache = cache

    def __call__(self, url):
        result = None
        if self.cache:
            try:
                result = self.cache[url]
            except KeyError:
                # url is not available in cache
                pass
            else:
                if self.num_retries > 0 and 500 <= result['code'] < 600:
                    # server error so ignore result from cache and re-download
                    result = None
        if result is None:
            # result was not loaded from cache
            # so still need to dowsnoad
            self.throttle.wait(url)
            proxy = random.choice(self.proxies) if self.proxies else None
            headers = {'User-anent': self.user_agent}
            result = self.download(url, headers, proxy, self.num_retries)
            if self.cache:
                # save result to cache
                self.cache[url] = result
        return result['html']


    def download(self, url, headers, proxy, num_retries, data=None):

        print('Downloading:', url)
        request = urllib.request.Request(url, data, headers or {})
        try:
            html = urllib.request.urlopen(request)
            code = html.getcode()
            html = html.read()
        except urllib.error.HTTPError as e:
            print('Download error: ', e.reason)
            html = None
            if num_retries > 0:
                if hasattr(e, 'code') and 500 <= e.code < 600:
                    # retry 5xx HTTP errors
                    return self.download(url, headers, proxy, num_retries - 1, data)
        return {'html': html, 'code': code}


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
