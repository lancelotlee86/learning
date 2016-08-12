# encoding=utf8

class Classifier:

    def __init__(self, bucketPrefix, testBucketNumber, dataFormat):

        self.medianAndDeviation = []

        # reading the data in  from the file

        self.format = dataFormat.strip().split('\t')
        self.data = []
        # for each of the bucket numbered 1 through 10
        for i in range(1, 11):
            # if it is not bucket we should ignore, read the data
            if i != testBucketNumber:
                filename = '%s-%02i' % (bucketPrefix, i)
                f = open(filename)
                lines = f.readlines()
                f.close()
                for line in lines:#########################################
                    fields = line.strip().split('\t')
                    ignore = []
                    vector = []
                    for i in range(len(fields)):
                        if self.format[i] == 'num':
                            vector.append(float(fields[i]))
                        elif self.format[i] == 'comment':
                            ignore.append(fields[i])
                        elif self.format[i] == 'class':
                            classification = fields[i]
                    self.data.append((classification, vector, ignore))
        self.rawData = list(self.data)
        # get lenght of instance vector
        self.vlen = len(self.data[0][1])
        # now normalize the data
        for i in range(self.vlen):
            self.normalizeColumn(i)

    ##################################################
    ###
    ###  CODE TO COMPUTE THE MODIFIED STANDARD SCORE

    def getMedian(self, alist):
        """return median of alist"""
        if alist == []:
            return []
        blist = sorted(alist)
        length = len(alist)
        if length % 2 == 1:
            # length of list is odd so return middle element
            return blist[int(((length + 1) / 2) - 1)]
        else:
            # length of list is even so compute midpoint
            v1 = blist[int(length / 2)]
            v2 = blist[(int(length / 2) - 1)]
            return (v1 + v2) / 2.0

    def getAbsoluteStandardDeviation(self, alist, median):
        """given alist and median return absolute standard deviation"""
        sum = 0
        for item in alist:
            sum += abs(item - median)
        return sum / len(alist)

    def normalizeColumn(self, columnNumber):
        """given a column number, normalize that column in self.data"""
        # first extract values to list
        col = [v[1][columnNumber] for v in self.data]
        median = self.getMedian(col)
        asd = self.getAbsoluteStandardDeviation(col, median)
        # print("Median: %f   ASD = %f" % (median, asd))
        self.medianAndDeviation.append((median, asd))
        for v in self.data:
            v[1][columnNumber] = (v[1][columnNumber] - median) / asd

    def normalizeVector(self, v):
        """We have stored the median and asd for each column.
        We now use them to normalize vector v"""
        vector = list(v)
        for i in range(len(vector)):
            (median, asd) = self.medianAndDeviation[i]
            vector[i] = (vector[i] - median) / asd
        return vector
        ###
        ### END NORMALIZATION
        ##################################################

    def testBucket(self, bucketPrefix, bucketNumer):
        """ Evaluate the classifier with data from the file bucketPrefix-bucketNumber"""

        filename = '%s-%02i' % (bucketPrefix, bucketNumer)
        f = open(filename)
        lines = f.readlines()
        totals = {}
        f.close()
        for line in lines:
            data = line.strip().split('\t')
            vector = []
            classInColumn = -1
            for i in range(len(self.format)):
                if self.format[i] == 'num':
                    vector.append(float(data[i]))
                elif self.format[i] == 'class':
                    classInColumn = i
            theRealClass = data[classInColumn]
            classifiedAs = self.classify(vector)
            totals.setdefault(theRealClass, {})
            totals[theRealClass].setdefault(classifiedAs, 0)
            totals[theRealClass][classifiedAs] += 1
        return totals


    def manhattan(self, vector1, vector2):
        """Computes the Manhattan distance."""
        return sum(map(lambda v1, v2: abs(v1 - v2), vector1, vector2))

    def nearestNeighbor(self, itemVector):
        """return nearest neighbor to itemVector"""
        return min([(self.manhattan(itemVector, item[1]), item)
                    for item in self.data])

    def classify(self, itemVector):
        """Return class we think item Vector is in"""
        return (self.nearestNeighbor(self.normalizeVector(itemVector))[1][0])


#c = Classifier('./data/mpgData/mpgData', 3, 'class	num	num	num	num	num	comment')
#t = c.testBucket('./data/mpgData/mpgData', 3)

def tenfold(bucketPrefix, dataFormat):
    results = {}
    for i in range(1, 11):
        c = Classifier(bucketPrefix, i, dataFormat)
        t = c.testBucket(bucketPrefix, i)
        for (key, value) in t.items():
            results.setdefault(key, {})
            for (ckey, cvalue) in value.items():
                results[key].setdefault(ckey, 0)
                results[key][ckey] += cvalue

    # now print results
    return results

mpg_results = tenfold('./data/mpgData/mpgData', 'class	num	num	num	num	num	comment')
pima_results = tenfold('./data/pimaSmall/pimaSmall', 'num\tnum\tnum\tnum\tnum\tnum\tnum\tnum\tclass')