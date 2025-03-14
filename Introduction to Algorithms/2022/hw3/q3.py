
from argparse import OPTIONAL
from typing import List


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

# Take user input to fill in the board


# Solve the Sudoku game using exhaustive search
solution = solve_sudoku(board)

# Print the solution, if one was found
if solution:
    print("Solved Sudoku board:")
    for i in range(9):
        print(" ".join(str(x) for x in solution[i]))
else:
    print("Unable to solve the Sudoku game.")



