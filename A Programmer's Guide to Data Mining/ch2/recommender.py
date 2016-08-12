import codecs
from math import sqrt

users = {"Angelica": {"Blues Traveler": 3.5, "Broken Bells": 2.0,
                      "Norah Jones": 4.5, "Phoenix": 5.0,
                      "Slightly Stoopid": 1.5,
                      "The Strokes": 2.5, "Vampire Weekend": 2.0},

         "Bill": {"Blues Traveler": 2.0, "Broken Bells": 3.5,
                  "Deadmau5": 4.0, "Phoenix": 2.0,
                  "Slightly Stoopid": 3.5, "Vampire Weekend": 3.0},

         "Chan": {"Blues Traveler": 5.0, "Broken Bells": 1.0,
                  "Deadmau5": 1.0, "Norah Jones": 3.0, "Phoenix": 5,
                  "Slightly Stoopid": 1.0},

         "Dan": {"Blues Traveler": 3.0, "Broken Bells": 4.0,
                 "Deadmau5": 4.5, "Phoenix": 3.0,
                 "Slightly Stoopid": 4.5, "The Strokes": 4.0,
                 "Vampire Weekend": 2.0},

         "Hailey": {"Broken Bells": 4.0, "Deadmau5": 1.0,
                    "Norah Jones": 4.0, "The Strokes": 4.0,
                    "Vampire Weekend": 1.0},

         "Jordyn": {"Broken Bells": 4.5, "Deadmau5": 4.0,
                    "Norah Jones": 5.0, "Phoenix": 5.0,
                    "Slightly Stoopid": 4.5, "The Strokes": 4.0,
                    "Vampire Weekend": 4.0},

         "Sam": {"Blues Traveler": 5.0, "Broken Bells": 2.0,
                 "Norah Jones": 3.0, "Phoenix": 5.0,
                 "Slightly Stoopid": 4.0, "The Strokes": 5.0},

         "Veronica": {"Blues Traveler": 3.0, "Norah Jones": 5.0,
                      "Phoenix": 4.0, "Slightly Stoopid": 2.5,
                      "The Strokes": 3.0}
         }


class Recommender:

    def __init__(self, data, k=1, metric='pearson', n=5):
        self.k = k
        self.n = n
        self.username2id = {}
        self.userid2name = {}
        self.productid2name = {}
        self.metric = metric

        if self.metric == 'pearson':
            self.fn = self.pearson
        # if data is dictionary, set recommender data to it
        if type(data).__name__ == 'dict':
            self.data = data

    def convert_product_ID_2_name(self,id):
        if id in self.productid2name:
            return self.productid2name[id]
        else:
            return id

    def user_ratings(self, id, n):
        """
        return n top ratings for user with id
        :param id:
        :param n:
        :return:
        """
        print("Ratings for " + self.userid2name[id])
        ratings = self.data[id]
        print(len(ratings))
        ratings = list(ratings.items())
        ratings = [(self.convert_product_ID_2_name(k), v)
                   for (k, v) in ratings]
        # finally sort and return
        ratings.sort(key=lambda artist_tuple: artist_tuple[1], reverse=True)
        ratings = ratings[:n]
        for rating in ratings:
            print("%s\t%i" % (rating[0], rating[1]))

    def load_book_DB(self, path=''):
        """
        loads the BX book dataset
        :param path:
        :return:
        """
        self.data = {}
        i = 0
        #
        # first load book ratings into self.data{}
        #
        f = codecs.open(path + "BX-Book-Ratings.csv", 'r', 'utf8')
        for line in f:
            i += 1
            # separate line into fields
            fields = line.split(';')
            user = fields[0].strip('"')
            book = fields[1].strip('"')
            rating = int(fields[2].strip().strip('"'))
            # 下面这几行的结构比较巧妙，注意一下
            if user in self.data:
                current_ratings = self.data[user]
            else:
                current_ratings = {}
            current_ratings[book] = rating
            self.data[user] = current_ratings
        f.close()
        #
        # Now load books into self.productid2name
        # Books contains isbn, title, and author among other fields
        #
        f = codecs.open(path + "BX-Books.csv", 'r', 'utf8')
        for line in f:
            i += 1
            # separate line into fields
            fields = line.split(';')
            isbn = fields[0].strip('"')
            title = fields[1].strip('"')
            author = fields[2].strip().strip('"')
            title = title + ' by ' + author
            self.productid2name[isbn] = title
        f.close()
        #
        # Now load user info into both self.userid2name and self.username2id
        #
        f = codecs.open(path + "BX-Users.csv", 'r', 'utf8')
        for line in f:
            i += 1
            # separate line into fields
            fields = line.split(';')
            userid  = fields[0].strip('"')
            location = fields[1].strip('"')
            if len(fields) > 3:
                age = fields[2].strip().strip('"')
            else:
                age = 'NULL'
            if age != 'NULL':
                value = location + '  (age: ' + age + ')'
            else:
                value = location
            self.userid2name[userid] = value
            self.username2id[location] = userid
        f.close()
        print(i)
        return i

    def pearson(self, rating1, rating2):
        sum_xy = 0
        sum_x = 0
        sum_y = 0
        sum_x2 = 0
        sum_y2 = 0
        n = 0
        for key in rating1:
            if key in rating2:
                n += 1
                x = rating1[key]
                y = rating2[key]
                sum_xy += x * y
                sum_x += x
                sum_y += y
                sum_x2 += x ** 2
                sum_y2 += y ** 2
        if n == 0:
            return 0
        numerator = sum_xy - (sum_x * sum_y) / n
        denominator = sqrt(sum_x2 - (sum_x ** 2) / n) * sqrt(sum_y2 - (sum_y ** 2) / n)
        if denominator == 0:
            return 0
        else:
            return numerator / denominator

    def compute_nearest_neighbor(self, username):
        """
        creates a sorted list of users based on their distance to the given username
        :param username: str, username
        :param users:
        :return:
        """
        distances = []
        for user in self.data:
            if user != username:
                distance = self.fn(self.data[username], self.data[user])
                distances.append((user, distance))
        distances.sort(key=lambda artistTuple: artistTuple[1], reverse=True)
        return distances

    def recommend(self, user):
        """
        give list of recommendations
        :param user:
        :return:
        """
        recommendations = {}

        # first get list of users ordered by nearness
        nearest = self.compute_nearest_neighbor(user)
        #
        # now get the ratings for the user
        #
        user_ratings = self.data[user]
        #
        #
        # 接下来计算权重
        #
        # determine the total distance
        total_distance = 0.0
        for i in range(self.k):
            total_distance += nearest[i][1]
        # now iterate through the k nearest neighbors
        # accumulating their ratings
        for i in range(self.k):
            # compute the slice of pie
            weight = nearest[i][1] / total_distance
            # get the name of the person
            name = nearest[i][0]
            # get the rating for this person
            neighbor_ratings = self.data[name]

            # now find the bands neighbor rated that user didn't
            # 很巧妙的循环与判断结构，注意一下
            for artist in neighbor_ratings:
                if not artist in user_ratings:
                    if artist not in recommendations:
                        recommendations[artist] = (neighbor_ratings[artist] * weight)
                    else:
                        recommendations[artist] = (recommendations[artist] + neighbor_ratings[artist] * weight)

        # now make list from dictionary
        recommendations = list(recommendations.items())
        recommendations = [(self.convert_product_ID_2_name(k), v) for (k, v) in recommendations]

        # finally sort and return
        recommendations.sort(key=lambda artist_tuple: artist_tuple[1], reverse=True)
        # return the first n items
        return recommendations[:self.n]

r = Recommender(data=users)
r.load_book_DB(path='C:\\Users\\lance\\Documents\\GitHub\\learning\\A Programmer\'s Guide to Data Mining\\ch2\\BX_data\\')
r.recommend('171118')