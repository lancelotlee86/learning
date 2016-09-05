import itertools
from foo import download
from time import sleep


for page in itertools.count(251):
    url = 'http://example.webscraping.com/view/%d' % page
    html = download(url)    # 阻塞的
    if html is None:
        break
    else:
        # success, now scraping
        pass