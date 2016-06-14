python3.5


    import getopt

    args = '--aa -b -cfoo --dd bar a1 a2'.split()
    optlist, args = getopt.getopt(args, 'abc:d:', ['aa', 'bb=', 'dd='])

现在
    >>> optlist
    >>> [('--aa', ''), ('-b', ''), ('-c', 'foo'), ('--dd', 'bar')]

    >>> args
    >>> ['a1', 'a2']

#### 总结
getopt.getopt()方法接收三个参数，第一个是命令行参数被分割后的列表，第二个是一个横线的单字母（有冒号代表后面有参数），第三个是--长参数的（有等号代表后面有参数）。
返回元组列表，每个元组是opt和arg的组合

具体的规范使用参见python手册
