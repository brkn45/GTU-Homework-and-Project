from collections import defaultdict
from argparse import OPTIONAL
from typing import List
#Question1
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

#Question 2
def calculate(a: int, n: int) -> int:
    if n == 0:
        return 1
    if n == 1:
        return a
    if n % 2 == 0:
        return calculate(a, n // 2) * calculate(a, n // 2)
    else:
        return a * calculate(a, n - 1)


#Question 3       

def solve_sudoku(board: List[List[int]]) :
    solution = [row[:] for row in board]

    def find_solution(board: List[List[int]], i: int, j: int) -> bool:
        if i == 9 and j == 0:
            return True

        if j == 9:
            i += 1
            j = 0
        if i == 9 and j == 0:
            return True

        
        if board[i][j] != 0:
            return find_solution(board, i, j + 1)

        for num in range(1, 10):
            if is_valid_move(board, i, j, num):
                board[i][j] = num
                if find_solution(board, i, j + 1):
                    solution[i][j] = num
                    return True
                board[i][j] = 0

        return False

    if find_solution(board, 0, 0):
        return solution
    else:
        return None

def is_valid_move(board: List[List[int]], i: int, j: int, num: int) -> bool:
    # Check if the number appears in the same row
    for k in range(9):
        if board[i][k] == num:
            return False

    # Check if the number appears in the same column
    for k in range(9):
        if board[k][j] == num:
            return False

    # Check if the number appears in the same 3x3 block
    row_start = (i // 3) * 3
    col_start = (j // 3) * 3
    for k in range(3):
        for l in range(3):
            if board[row_start + k][col_start + l] == num:
                return False

    return True

# Initialize the Sudoku board
board = [[5,1,7,6,0,0,0,3,4], #0
		[2,8,9,0,0,4,0,0,0], #1
		[3,4,6,2,0,5,0,9,0], #2
		[6,0,2,0,0,0,0,1,0], #3
		[0,3,8,0,0,6,0,4,7], #4
		[0,0,0,0,0,0,0,0,0], #5
		[0,9,0,0,0,0,0,7,8], #6
		[7,0,3,4,0,0,5,6,0], #7
		[0,0,0,0,0,0,0,0,0]] #8

# Question 1 Graph2

graph = {
    102: [241],
    241: [222],
    222: [321],
    211: [321],
    321: [422],
    422: []
}

   

def main() -> None:
    #Question 1
    # Create the graph

    print("Question 1")
    # Obtain the topological ordering
    ordering1 = sort1(graph)
    ordering2 = sort2(graph)
    # Print the ordering
    print("Order with DFS")
    print(ordering1)
    print("Order with non-DFS")
    print(ordering2)
    #Question 2
    print("Question 2")
    a_number = input("please enter a number:")
    n_number = input("please enter n number:")
    n_number =int(n_number)
    a_number =int(a_number)
    sum =1
    sum=calculate(a_number,n_number)
    print("res:")
    print(sum)
    #Question 3
    print("Question 1")
    solution = solve_sudoku(board)
    
    # Print the solution, if one was found
    if solution:
        print("Solved Sudoku board:")
        for i in range(9):
            print(" ".join(str(x) for x in solution[i]))
    else:
        print("Unable to solve the Sudoku game.") 

if __name__ == "__main__":
    main()



    