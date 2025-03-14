
#question 1
def find_maximum_score_from_coordinate(map, i, j, current_score, n, m):
    
    if i == n and j == m:
        return current_score

  
    if j < m:
        right_score = find_maximum_score_from_coordinate(map, i, j+1, current_score + map[i][j+1], n, m)
    else:
        right_score = -9999999

    
    if i < n:
        down_score = find_maximum_score_from_coordinate(map, i+1, j, current_score + map[i+1][j], n, m)
    else:
        down_score = -999999

    return max(right_score, down_score)
#question 2
  
def quickselect(array, k):
    if not array:
        return None

    # Choose pivot element and partition array
    pivot = array[len(array) // 2]
    left, right = [], []
    for element in array:
        if element < pivot:
            left.append(element)
        elif element > pivot:
            right.append(element)

    # Check if pivot is the kth smallest element
    if k < len(left):
        return quickselect(left, k)
    elif k >= len(array) - len(right):
        return quickselect(right, k - (len(array) - len(right)))
    return pivot

# Find median of an odd-length array
array = [5, 2, 7, 1, 3]
median = quickselect(array, len(array) // 2)
print(median)  # Output: 3

# Find median of an even-length array
array = [5, 2, 7, 1, 3, 4]
median = (quickselect(array, len(array) // 2 - 1) + quickselect(array, len(array) // 2)) / 2
print(median)  # Output: 3.5

#question 3 part1

class Player:
    def __init__(self, name):
        self.name = name
        self.next = None

class CircularLinkedList:
    def __init__(self, players):
        self.head = None
        self.tail = None

        for player in players:
            self.add(player)

    def add(self, player):
        if not self.head:
            self.head = player
            player.next = self.head
            self.tail = self.head
        else:
            self.tail.next = player
            player.next = self.head
            self.tail = player

def find_winner(players):
    linked_list = CircularLinkedList(players)
    current_player = linked_list.head

    while current_player.next != current_player:
        current_player.next = current_player.next.next
        current_player = current_player.next

    return current_player.name

#question 3 part 2
def find_winner(players, n):
    if n == 1:
        return players[0]
    i = n // 2
    if n % 2 == 0:
        i -= 1
    players.pop(i)
    return find_winner(players, n - 1)


def main():
    print("-----question 1-----")
    map = [[10, 31, 11, 15],
           [12, 22, 14, 12],
           [11, 11, 12, 13],
           [12, 11, 13, 14]]

    n = 3 
    m = 3
    start_i = 1
    start_j = 1
    current_score = 0
    max_score = find_maximum_score_from_coordinate(map, start_i, start_j, current_score, n, m)
    print("-----question 1-----")
    print("Maximum score:", max_score)


    
    # Find median of an odd length array
    array = [5, 2, 7, 1, 3]
    median = quickselect(array, len(array) // 2)
    print("Median:",median) 

    # Find median of an even length array
    array = [5, 2, 7, 1, 3, 4]
    median = (quickselect(array, len(array) // 2 - 1) + quickselect(array, len(array) // 2)) / 2
    print("Median:",median)  

    print("----question 3 Part 1-----")

    # Example usage
    players = [Player("player 1"), Player("player 2"), Player("player 3"), Player("player 4") ,Player("player 5"), Player("player 6")]
    winner = find_winner(players)
    print("n= 6 results: ",winner) 

    players = [Player("player 1"), Player("player 2"), Player("player 3"), Player("player 4") ,Player("player 5"), Player("player 6") ,Player("player 7")]
    winner = find_winner(players)
    print("n= 7 results: ",winner)
    
    players = [P1, P2, P3, P4, P5]
    n = len(players)
    winner = find_winner(players, n)
    print("The winner of the game is:", winner) 
main()
