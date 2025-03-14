# Grafın düğümlerinin sayısını ve kenarlarını belirtir
n = 5
edges = [(1, 2), (1, 3), (2, 3), (2, 4), (2, 5), (4, 5)]

 

# Düğümlerin listesi
vertices = [i for i in range(n)]

 

# Düğümlerin ve kenarların bir yığını oluşturun
graph = (vertices, edges)

 

# DFS sırasında ziyaret edilen düğümleri takip eden bir liste oluşturun
visited = []

 

def dfs(graph, vertex, visited):
  """DFS ile grafı tarar ve ziyaret edilen düğümleri visited listesine ekler"""
  visited.append(vertex)
  for neighbor in graph[1]:
    if neighbor[0] == vertex:
      if neighbor[1] not in visited:
        dfs(graph, neighbor[1], visited)
    elif neighbor[1] == vertex:
      if neighbor[0] not in visited:
        dfs(graph, neighbor[0], visited)

 

# Bölücü düğümleri bulmak için grafı tarar ve ziyaret edilen düğümleri bir yığını oluşturur
def find_cut_vertices(graph):
  """Graf içinde bölücü düğümleri bulur"""
  cut_vertices = []
  for vertex in graph[0]:
    visited = []
    dfs(graph, vertex, visited)
    if len(visited) < len(graph[0]):
      cut_vertices.append(vertex)
  return cut_vertices

 

# Bölücü düğümleri bulun ve yazdırın
cut_vertices = find_cut_vertices(graph)
print(cut_vertices)