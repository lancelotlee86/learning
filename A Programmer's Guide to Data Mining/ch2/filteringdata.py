# encoding=utf8
from math import sqrt


users = {"Angelica": {"Blues Traveler": 3.5, "Broken Bells": 2.0, "Norah Jones": 4.5, "Phoenix": 5.0,
                      "Slightly Stoopid": 1.5, "The Strokes": 2.5, "Vampire Weekend": 2.0},
         "Bill": {"Blues Traveler": 2.0, "Broken Bells": 3.5, "Deadmau5": 4.0, "Phoenix": 2.0, "Slightly Stoopid": 3.5,
                  "Vampire Weekend": 3.0},
         "Chan": {"Blues Traveler": 5.0, "Broken Bells": 1.0, "Deadmau5": 1.0, "Norah Jones": 3.0, "Phoenix": 5,
                  "Slightly Stoopid": 1.0},
         "Dan": {"Blues Traveler": 3.0, "Broken Bells": 4.0, "Deadmau5": 4.5, "Phoenix": 3.0, "Slightly Stoopid": 4.5,
                 "The Strokes": 4.0, "Vampire Weekend": 2.0},
         "Hailey": {"Broken Bells": 4.0, "Deadmau5": 1.0, "Norah Jones": 4.0, "The Strokes": 4.0,
                    "Vampire Weekend": 1.0},
         "Jordyn": {"Broken Bells": 4.5, "Deadmau5": 4.0, "Norah Jones": 5.0, "Phoenix": 5.0, "Slightly Stoopid": 4.5,
                    "The Strokes": 4.0, "Vampire Weekend": 4.0},
         "Sam": {"Blues Traveler": 5.0, "Broken Bells": 2.0, "Norah Jones": 3.0, "Phoenix": 5.0,
                 "Slightly Stoopid": 4.0, "The Strokes": 5.0},
         "Veronica": {"Blues Traveler": 3.0, "Norah Jones": 5.0, "Phoenix": 4.0, "Slightly Stoopid": 2.5,
                      "The Strokes": 3.0}
         }


def manhattan(rating1, rating2):
    """
    Computes the Manhattan distance
    :param rating1: type of dic, something like {'The Strokes': 3.0, ...}
    :param rating2: type of dic, something like {'The Strokes': 3.0, ...}
    :return: distance
    """
    distance = 0
    for key in rating1:
        if key in rating2:
            distance += abs(rating1[key] - rating2[key])
    return distance


def compute_nearest_neighbor(username, users):
    """
    creates a sorted list of users based on their distance to the given username
    :param username: str, username
    :param users:
    :return:
    """
    distances = []
    for user in users:
        if user != username:
            distance = manhattan(users[user], users[username])
            distances.append((distance, user))
    distances.sort()
    return distances


def recommend(username, users):
    """
    given list of recommendations for the given username
    :param username:
    :param users:
    :return:
    """
    # first find the nearest neighbor
    nearest = compute_nearest_neighbor(username, users)[0][1]
    recommendations = []

    neighbor_ratings = users[nearest]
    user_ratings = users[username]
    for artist in neighbor_ratings:
        if not artist in user_ratings:
            recommendations.append((artist, neighbor_ratings[artist]))

    return sorted(recommendations,
                  key=lambda artist_tuple: artist_tuple[1],
                  reverse=True)


def pearson(rating1, rating2):
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
            sum_x2 += x**2
            sum_y2 += y**2
    numerator = sum_xy - (sum_x * sum_y) / n
    denominator = sqrt(sum_x2 - (sum_x**2) / n) * sqrt(sum_y2 - (sum_y**2) / n)
    if denominator == 0:
        return 0
    else:
        return numerator / denominator
