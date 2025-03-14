import math

# Define the Point structure
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Function to find the distance between two points
def dist(p1, p2):
    return math.sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2)

# Brute force method to find the smallest distance
def bruteForce(points):
    min_dist = float('inf')
    n = len(points)
    for i in range(n):
        for j in range(i + 1, n):
            if dist(points[i], points[j]) < min_dist:
                min_dist = dist(points[i], points[j])
    return min_dist

# Function to find the distance between the closest points of strip
def stripClosest(strip, d):
    min_val = d
    strip.sort(key=lambda point: point.y)   # Sort the strip according to y coordinate

    for i in range(len(strip)):
        j = i + 1
        while j < len(strip) and (strip[j].y - strip[i].y) < min_val:
            min_val = min(min_val, dist(strip[i], strip[j]))
            j += 1

    return min_val

# Recursive function to find the smallest distance
def closestUtil(Px, Py):
    n = len(Px)
    if n <= 3:
        return bruteForce(Px)

    mid = n // 2
    midPoint = Px[mid]

    Pyl = Py[:mid]
    Pyr = Py[mid:]

    dl = closestUtil(Px[:mid], Pyl)
    dr = closestUtil(Px[mid:], Pyr)

    d = min(dl, dr)

    strip = []
    for p in Py:
        if abs(p.x - midPoint.x) < d:
            strip.append(p)

    return min(d, stripClosest(strip, d))

# The main function that finds the smallest distance
def closest(points):
    points.sort(key=lambda point: point.x)
    return closestUtil(points, points.copy())

# Test cases
test_points1 = [Point(2, 3), Point(12, 30), Point(40, 50), Point(5, 1), Point(12, 10), Point(3, 4)]
test_points2 = [Point(2, 3), Point(4, 5), Point(5, 7), Point(8, 9), Point(10, 12), Point(15, 18)]

# Running test cases
closest_distance1 = closest(test_points1)
closest_distance2 = closest(test_points2)

# Print the results of the closest distances
print("Question 1")
print("Closest distance in test set 1:", closest_distance1)
print("Closest distance in test set 2:", closest_distance2)

################# Question 2 #############


# A divide and conquer program to find convex
# hull of a given set of points.
from functools import cmp_to_key

# stores the centre of polygon (It is made
# global because it is used in compare function)
mid = [0, 0]

# determines the quadrant of a point
# (used in compare())
def quad(p):
	if p[0] >= 0 and p[1] >= 0:
		return 1
	if p[0] <= 0 and p[1] >= 0:
		return 2
	if p[0] <= 0 and p[1] <= 0:
		return 3
	return 4

# Checks whether the line is crossing the polygon
def orientation(a, b, c):
	res = (b[1]-a[1]) * (c[0]-b[0]) - (c[1]-b[1]) * (b[0]-a[0])
	if res == 0:
		return 0
	if res > 0:
		return 1
	return -1

# compare function for sorting
def compare(p1, q1):
	p = [p1[0]-mid[0], p1[1]-mid[1]]
	q = [q1[0]-mid[0], q1[1]-mid[1]]
	one = quad(p)
	two = quad(q)

	if one != two:
		if one < two:
			return -1
		return 1
	if p[1]*q[0] < q[1]*p[0]:
		return -1
	return 1

# Finds upper tangent of two polygons 'a' and 'b'
# represented as two vectors.
def merger(a, b):
	# n1 -> number of points in polygon a
	# n2 -> number of points in polygon b
	n1, n2 = len(a), len(b)
	ia, ib = 0, 0

	# ia -> rightmost point of a
	for i in range(1, n1):
		if a[i][0] > a[ia][0]:
			ia = i

	# ib -> leftmost point of b
	for i in range(1, n2):
		if b[i][0] < b[ib][0]:
			ib = i
	# finding the upper tangent
	inda, indb = ia, ib
	done = 0
	while not done:
		done = 1
		while orientation(b[indb], a[inda], a[(inda+1) % n1]) >= 0:
			inda = (inda + 1) % n1

		while orientation(a[inda], b[indb], b[(n2+indb-1) % n2]) <= 0:
			indb = (indb - 1) % n2
			done = 0

	uppera, upperb = inda, indb
	inda, indb = ia, ib
	done = 0
	g = 0
	while not done: # finding the lower tangent
		done = 1
		while orientation(a[inda], b[indb], b[(indb+1) % n2]) >= 0:
			indb = (indb + 1) % n2

		while orientation(b[indb], a[inda], a[(n1+inda-1) % n1]) <= 0:
			inda = (inda - 1) % n1
			done = 0

	ret = []
	lowera, lowerb = inda, indb
	# ret contains the convex hull after merging the two convex hulls
	# with the points sorted in anti-clockwise order
	ind = uppera
	ret.append(a[uppera])
	while ind != lowera:
		ind = (ind+1) % n1
		ret.append(a[ind])

	ind = lowerb
	ret.append(b[lowerb])
	while ind != upperb:
		ind = (ind+1) % n2
		ret.append(b[ind])
	return ret

# Brute force algorithm to find convex hull for a set
# of less than 6 points
def bruteHull(a):
	# Take any pair of points from the set and check
	# whether it is the edge of the convex hull or not.
	# if all the remaining points are on the same side
	# of the line then the line is the edge of convex
	# hull otherwise not
	global mid
	s = set()
	for i in range(len(a)):
		for j in range(i+1, len(a)):
			x1, x2 = a[i][0], a[j][0]
			y1, y2 = a[i][1], a[j][1]
			a1, b1, c1 = y1-y2, x2-x1, x1*y2-y1*x2
			pos, neg = 0, 0
			for k in range(len(a)):
				if (k == i) or (k == j) or (a1*a[k][0]+b1*a[k][1]+c1 <= 0):
					neg += 1
				if (k == i) or (k == j) or (a1*a[k][0]+b1*a[k][1]+c1 >= 0):
					pos += 1
			if pos == len(a) or neg == len(a):
				s.add(tuple(a[i]))
				s.add(tuple(a[j]))

	ret = []
	for x in s:
		ret.append(list(x))

	# Sorting the points in the anti-clockwise order
	mid = [0, 0]
	n = len(ret)
	for i in range(n):
		mid[0] += ret[i][0]
		mid[1] += ret[i][1]
		ret[i][0] *= n
		ret[i][1] *= n
	ret = sorted(ret, key=cmp_to_key(compare))
	for i in range(n):
		ret[i] = [ret[i][0]/n, ret[i][1]/n]
	return ret

# Returns the convex hull for the given set of points
def divide(a):
	# If the number of points is less than 6 then the
	# function uses the brute algorithm to find the
	# convex hull
	if len(a) <= 5:
		return bruteHull(a)

	# left contains the left half points
	# right contains the right half points
	left, right = [], []
	start = int(len(a)/2)
	for i in range(start):
		left.append(a[i])
	for i in range(start, len(a)):
		right.append(a[i])

	# convex hull for the left and right sets
	left_hull = divide(left)
	right_hull = divide(right)

	# merging the convex hulls
	return merger(left_hull, right_hull)

# Driver Code
if __name__ == '__main__':
	a = []
	a.append([0, 0])
	a.append([1, -4])
	a.append([-1, -5])
	a.append([-5, -3])
	a.append([-3, -1])
	a.append([-1, -3])
	a.append([-2, -2])
	a.append([-1, -1])
	a.append([-2, -1])
	a.append([-1, 1])

	n = len(a)
	# sorting the set of points according
	# to the x-coordinate
	a.sort()
	ans = divide(a)
    
	print('\nQuestion #2 \nConvex Hull:')
	for x in ans:
		print(int(x[0]), int(x[1]))


############## Question #3   #################
		
def minDis(s1, s2, n, m, dp):
 
    # If any string is empty,
    # return the remaining characters of other string
    if(n == 0):
        return m
    if(m == 0):
        return n
 
    # To check if the recursive tree
    # for given n & m has already been executed
    if(dp[n][m] != -1):
        return dp[n][m]
 
    # If characters are equal, execute
    # recursive function for n-1, m-1
    if(s1[n - 1] == s2[m - 1]):
        if(dp[n - 1][m - 1] == -1):
            dp[n][m] = minDis(s1, s2, n - 1, m - 1, dp)
            return dp[n][m]
        else:
            dp[n][m] = dp[n - 1][m - 1]
            return dp[n][m]
 
    # If characters are nt equal, we need to
    # find the minimum cost out of all 3 operations.
    else:
        if(dp[n - 1][m] != -1):
            m1 = dp[n - 1][m]
        else:
            m1 = minDis(s1, s2, n - 1, m, dp)
 
        if(dp[n][m - 1] != -1):
            m2 = dp[n][m - 1]
        else:
            m2 = minDis(s1, s2, n, m - 1, dp)
        if(dp[n - 1][m - 1] != -1):
            m3 = dp[n - 1][m - 1] 
        else:
            m3 = minDis(s1, s2, n - 1, m - 1, dp) 

        m3 = 3 * m3 # replace operation

        dp[n][m] = 1 + min(m1, min(m2, m3))
        return dp[n][m]
 

        # Driver code
	
str1 = "ACGTTCG"
str2 = "ACGATCA"
 
n = len(str1)
m = len(str2)
dp = [[-1 for i in range(m + 1)] for j in range(n + 1)]
 
print("\n Question #3\n")
print("str1:",str1)
print("str2:",str2)

print("min cost:",minDis(str1, str2, n, m, dp))


############### Question #4 ####################

n = 4  # there are four nodes in example graph (graph is 1-based)
 
# dist[i][j] represents shortest distance to go from i to j
# this matrix can be calculated for any given graph using 
# all-pair shortest path algorithms
dist = [[0, 0, 0, 0, 0], [0, 0, 10, 15, 20], [
    0, 10, 0, 25, 25], [0, 15, 25, 0, 30], [0, 20, 25, 30, 0]]
 
# memoization for top down recursion
memo = [[-1]*(1 << (n+1)) for _ in range(n+1)]
 
 
def fun(i, mask):
    # base case
    # if only ith bit and 1st bit is set in our mask,
    # it implies we have visited all other nodes already
    if mask == ((1 << i) | 3):
        return dist[1][i]
 
    # memoization
    if memo[i][mask] != -1:
        return memo[i][mask]
 
    res = -1  # result of this sub-problem
 
    # we have to travel all nodes j in mask and end the path at ith node
    # so for every node j in mask, recursively calculate cost of 
    # travelling all nodes in mask
    # except i and then travel back from node j to node i taking 
    # the shortest path take the minimum of all possible j nodes
    for j in range(1, n+1):
        if (mask & (1 << j)) != 0 and j != i and j != 1:
            res = max(res, fun(j, mask & (~(1 << i))) + dist[j][i])
    memo[i][mask] = res  # storing the minimum value
    return res
 
 
# Driver program to test above logic
ans = -1
for i in range(1, n+1):
    # try to go from node 1 visiting all nodes in between to i
    # then return from i taking the shortest route to 1
    ans = max(ans, fun(i, (1 << (n+1))-1) + dist[i][1])

print("\nQuestion #4")
print("The cost of most efficient tour = " + str(ans))





################# Question #5 ################

def greedy_algorithm(antenna_locations):
    antenna_locations.sort(key=lambda x: x[0])  # Sort antennas based on the starting point
    selected_antennas = []
    
    i = 0
    while i < len(antenna_locations):
        current_antenna = antenna_locations[i]
        selected_antennas.append(current_antenna)
        
        # Select the current antenna
        while i + 1 < len(antenna_locations) and antenna_locations[i + 1][0] <= current_antenna[1]:
            i += 1
            current_antenna = antenna_locations[i]
        
        i += 1

    return selected_antennas

# Example usage:
antenna_locations = [(1, 5), (2, 6), (3, 7), (4, 8)]
result = greedy_algorithm(antenna_locations)
print("\nQuestion #5\n")
print(result)


