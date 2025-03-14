################### Question #1
def findMalfunctioningFuse(fuses):
    start = 0
    end = len(fuses) - 1

    while start <= end:
        mid = (start + end) // 2

        if fuses[mid] == 'healthy':
            start = mid + 1
        else:
            end = mid - 1

    return start

# Test cases for the function
test_cases = [
    (['healthy', 'healthy', 'not healthy', 'not healthy'], 2),
    (['healthy', 'healthy', 'healthy', 'not healthy'], 3),
    (['not healthy', 'not healthy', 'not healthy', 'not healthy'], 0),
    (['healthy', 'healthy', 'healthy', 'healthy'], 4),
    (['healthy', 'not healthy', 'not healthy', 'not healthy'], 1),
]

# Testing the function
print("#Question 1")
for fuses, expected in test_cases:
    result = findMalfunctioningFuse(fuses)
    print(f"Test with fuses {fuses}: Expected {expected}, got {result}")


################### Question #2
    
def findBrightestPixel(grid):
    top, bottom = 0, len(grid) - 1
    left, right = 0, len(grid[0]) - 1

    while left <= right and top <= bottom:
        midRow = (top + bottom) // 2
        midCol = (left + right) // 2
        brightestPixel = (midRow, midCol)

        if isBrightestAmongNeighbors(brightestPixel, grid):
            return brightestPixel

        
        currentBrightness = grid[midRow][midCol]
        topBrightness = grid[midRow - 1][midCol] if midRow > 0 else float('-inf')
        bottomBrightness = grid[midRow + 1][midCol] if midRow < len(grid) - 1 else float('-inf')
        leftBrightness = grid[midRow][midCol - 1] if midCol > 0 else float('-inf')
        rightBrightness = grid[midRow][midCol + 1] if midCol < len(grid[0]) - 1 else float('-inf')

       
        if topBrightness > currentBrightness:
            bottom = midRow - 1
        elif bottomBrightness > currentBrightness:
            top = midRow + 1
        elif leftBrightness > currentBrightness:
            right = midCol - 1
        elif rightBrightness > currentBrightness:
            left = midCol + 1
        else:
            
            return brightestPixel

    return None

def isBrightestAmongNeighbors(pixel, grid):
    row, col = pixel
    pixelBrightness = grid[row][col]

   
    if row > 0 and grid[row - 1][col] > pixelBrightness:
        return False
    if row < len(grid) - 1 and grid[row + 1][col] > pixelBrightness:
        return False
    if col > 0 and grid[row][col - 1] > pixelBrightness:
        return False
    if col < len(grid[0]) - 1 and grid[row][col + 1] > pixelBrightness:
        return False

    return True

#Test Case
grid1 = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]

grid2 = [
    [10, 9, 8],
    [7, 12, 5],
    [4, 3, 2]
]

print("\n#Question 2")

print("Brightest pixel in Grid 1:", findBrightestPixel(grid1))
print("Brightest pixel in Grid 2:", findBrightestPixel(grid2))


###############Question #3
# Defining the functions calculateArea and maximizeArea

def calculateArea(f, start, end):
    """
    Calculates the total area under the function f(x) from start to end.
    """
    area = 0
    for x in range(start, end + 1):
        area += f(x)
    return area

def maximizeArea(f, n):
    """
    Finds the interval within [0, n] that produces the maximal total area under the function f(x).
    """
    maxArea = calculateArea(f, 0, n)
    maxInterval = (0, n)

    for i in range(0, n):
        for j in range(i, n):
            currentArea = calculateArea(f, i, j)
            if currentArea > maxArea:
                maxArea = currentArea
                maxInterval = (i, j)

    return maxInterval, maxArea

# Example usage with a test function and upper limit
f = lambda x: x**2 - 4*x + 3  # Example function
n = 10                        # Example upper limit
interval, area = maximizeArea(f, n)

interval, area  # Displaying the results
print("\n#Question 3")
print("interval:",interval)
print("area:",area)


################### Question #4
def dfs(graph, current, destination, current_latency, path, min_path, min_latency):
    path.append(current)
    if current == destination:
        if current_latency < min_latency[0]:
            min_latency[0] = current_latency
            min_path.clear()
            min_path.extend(path)
    else:
        for neighbor, latency in graph[current].items():
            if neighbor not in path:
                new_latency = current_latency + latency
                dfs(graph, neighbor, destination, new_latency, path, min_path, min_latency)
    path.pop()

def find_minimum_latency_path(graph):
    min_latency = [float('inf')]
    min_path = []
    for source in graph:
        for destination in graph:
            if source != destination:
                path = []
                dfs(graph, source, destination, 0, path, min_path, min_latency)
    return min_path, min_latency[0]

# Example graph (dictionary of dictionaries)
graph = {
    'A': {'B': 5, 'C': 4}, #DC shortest path
    'B': {'A': 5, 'C': 2, 'D': 5},
    'C': {'A': 4, 'B': 2, 'D': 1},
    'D': {'B': 5, 'C': 1}
}

# Find minimum latency path
min_path, min_latency = find_minimum_latency_path(graph)

print("\n#Question 4")
print("Min Path:",min_path)
print("Min Lantency:",min_latency)

################### Question #5
class Task:
    def __init__(self, name, resources):
        self.name = name
        self.resources = resources

    def __repr__(self):
        return f"Task({self.name}, Resources: {self.resources})"

def findResourceExtremes(tasks):
    if len(tasks) == 1:
        return tasks[0], tasks[0]
    else:
        mid = len(tasks) // 2
        leftMax, leftMin = findResourceExtremes(tasks[:mid])
        rightMax, rightMin = findResourceExtremes(tasks[mid:])

        maxTask = max(leftMax, rightMax, key=lambda task: task.resources)
        minTask = min(leftMin, rightMin, key=lambda task: task.resources)

        return maxTask, minTask

# Example usage
allTasks = [
    Task("Task1", 10),
    Task("Task2", 15),
    Task("Task3", 5),
    Task("Task4", 20),
    Task("Task5", 8)
]

maxTask, minTask = findResourceExtremes(allTasks)
print("\n#Question 5")
print(f"Task requiring most resources: {maxTask}")
print(f"Task requiring least resources: {minTask}")
