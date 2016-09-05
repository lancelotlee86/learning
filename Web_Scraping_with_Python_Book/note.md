从http://httpstat.us/???测试各种状态码，后三位是状态码

urllib在python3中分为以下几个模块
    urllib.request for opening and reading URLs
    urllib.error containing the exceptions raised by urllib.request
    urllib.parse for parsing URLs
    urllib.robotparser for parsing robots.txt files
    

Python3.x和2.x都可以用Pysocks做socket代理

python3的urllib.request.urlopen().read()返回的是bytes类型的，还要decode('utf8')
python2的urllib2.urlopen().read()返回的好像是str，不确定。