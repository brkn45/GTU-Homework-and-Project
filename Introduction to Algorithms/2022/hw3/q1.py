from collections import defaultdict

def dfs(graph, visited, ordering, vertex):
    visited.add(vertex)

    for neighbor in graph[vertex]:
        if neighbor not in visited:
            dfs(graph, visited, ordering, neighbor)

    ordering.append(vertex)

def sort1(graph):
    visited = set()
    ordering = []

    for vertex in graph:
        if vertex not in visited:
            dfs(graph, visited, ordering, vertex)

    return ordering




def sort2(graph):
    in_degree = defaultdict(int)
    ordering = []

    for vertex in graph:
        for neighbor in graph[vertex]:
            in_degree[neighbor] += 1

   
    queue = [vertex for vertex in graph if in_degree[vertex] == 0]

   
    while queue:
        
        vertex = queue.pop(0)
        ordering.append(vertex)

        
        for neighbor in graph[vertex]:
            in_degree[neighbor] -= 1

            
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

   
    if len(ordering) < len(graph):
        return None

    return ordering

# Create the graph
graph = {
    102: [241],
    241: [222],
    222: [321],
    211: [321],
    321: [422],
    422: []
}

# Obtain the topological ordering
ordering1 = sort1(graph)
ordering2 = sort2(graph)
# Print the ordering
print("Order with DFS")
print(ordering1)
print("Order with non-DFS")
print(ordering2)