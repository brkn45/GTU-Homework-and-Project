def dynamic_programing(map, x, y):
  
  if 0 == x  and 0 == y :
    return map[x][y]
  
 
  if y >0 :
    right = dynamic_programing(score,  x, y-1) + map[x][y]
  else:
    right = -999999
  

  if x > 0:
    bottom = dynamic_programing(score, x -1, y) + map[x][y]
  else:
    bottom =-9999999
  
  
  return max(right, bottom)


def greedy(map, x, y):
    sum = 0
    i = 0
    j = 0
    
    while i <x and j <y:
        if map[i][j+1] > map[i+1][j]:
            sum += map[i][j+1]
            j += 1
        elif map[i+1][j] > map[i][j+1]:
            sum += map[i+1][j]
            i += 1
        else:
            sum += map[i][j+1]
            j += 1
    return sum


score = [[25,30,25], [45,15, 11], [1, 88, 15], [9, 4, 23]]

print("------Part 1------")
res = dynamic_programing(score,3,2)
print(res)

print("------Part 2--------")
res = greedy(score,3,2)
print(res)