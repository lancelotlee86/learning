# encoding=utf8

import random


def buckets(filename, bucket_name, separator, class_column):

    # put the data in 10 buckets
    number_of_buckets = 10
    data = {}
    # 首先读入数据并按类别分开
    with open(filename) as f:
        lines = f.readlines()
    for line in lines:
        if separator != '\t':
            line = line.replace(separator, '\t')
        # first get the category
        category = line.split()[class_column]
        data.setdefault(category, [])
        data[category].append(line)

    # initialize the bucites
    buckets = []
    for i in range(number_of_buckets):
        buckets.append([])

    # now, for each category put the data into the buckets
    for k in data.keys():   # 每个 k 是一种类别category
        # randomize order of instances for each class
        random.shuffle(data[k])
        b_num = 0
        # divide into buckets
        for item in data[k]:
            buckets[b_num].append(item)
            b_num = (b_num + 1) % number_of_buckets

    # write to file
    for b_num in range(number_of_buckets):
        f = open("%s-%02i" % (bucket_name, b_num + 1), 'w')
        for item in buckets[b_num]:
            f.write(item)
        f.close()

buckets("../ch5/data/auto-mpg.data", 'mpg_data', '\t', 0)
