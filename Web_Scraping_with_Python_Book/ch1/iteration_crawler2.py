import itertools
from foo import download


# 最大连续下载错误次数
max_errors = 5
# 当前连续的下载错误次数
num_errors = 0


for page in itertools.count(251):
    url = 'http://example.webscraping.com/view/%d' % page
    html = download(url)    # 阻塞的
    if html is None:
        num_errors += 1
        if num_errors == max_errors:
            # 达到了连续最大错误次数，推出
            break
    else:
        # success, now scraping
        num_errors = 0
        pass