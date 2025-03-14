import random
#---------------------question 1 --------------------------------------------------------
def sub_str_compare(str) :
    
    if len(str) == 1 :
        return str[0]
    else :
        mid = len(str) // 2
        left_word = sub_str_compare(str[:mid])
        right_word = sub_str_compare(str[mid:])
        return string_compare(left_word,right_word)

    

def string_compare(left_srt,right_srt) :
    
    minLength = min(len(left_srt), len(right_srt))
    for i in range(minLength):
        if left_srt[i] != right_srt[i]:
            return left_srt[:i]
    return left_srt[:minLength]

#--------------------------question 2---------------------------------------------
#part a
def find_profit(prices) :
    if(len(prices) == 2) :
        return prices
    elif len(prices) ==1:
        tmp =[prices[0],prices[0]]
        return tmp        
    else :
        mid = len(prices) // 2
        
        price1 = find_profit(prices[:mid])
        price2 = find_profit(prices[mid:])
        
        if price1[0] > price1[1] :
            price1[0],price1[1] = price1[1], price1[0]
        if price2[0] > price2[1] :
            price2[0],price2[1] = price2[1],price2[0]
        if price1[0] >price2[0] :
            price1[0] = price2[0]
        if price1[1] < price2[1] :
            price1[1] = price2[1]; 
        return price1       
#part B         
def b_part(prices) :
    min =999999
    max = -9999999
    i=0
    while(i < len(prices)) :
        if(prices[i] < min) :
            min = prices[i]
        if(prices[i] > max) :
            max = prices[i] 
        i= i+1        
    tmp = [min,max]
    return tmp

#-------------------question 3 ------------------------------------------
def find_subarray(array, lengths, prev, index) :
    
    if lengths[index] > 0:
        return lengths[index]
    
    lengths[index] = 1
    
   
    for i in range(index):
        size = find_subarray(array, lengths, prev, i)
        if array[index] > array[i] and lengths[index] < size + 1 :
            lengths[index] = find_subarray(array, lengths, prev, i) + 1
            prev[index] = i
    
    
    return lengths[index]

def longest(array):
   
    lengths = [0] * len(array)
    prev = [None] * len(array)

    longest = 0
    for i in range(len(array)):
        longest = max(longest, find_subarray(array, lengths, prev, i))

    result = []
    index = lengths.index(longest)
    
    while index is not None:
        result.append(array[index])
        index = prev[index]

    return result[::-1]

#------------------Question 4 ---------------------
#part1
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

#part 2
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




#------------------question 1 ---------------------

exp1 =["programmable", "programming",
 "programmer", "programmatic", "programmability"]
exp2 = ["compute", "compatible", "computer", "compare", "compactness"]
#example 1
print("-------#example 1------")
print(exp1)
print("Result: " + sub_str_compare(exp1))

print("-------#example 2------")
print(exp2)
print("Result: " + sub_str_compare(exp2))

#------------------question 2 ---------------------

exp1 = [random.randint(10, 99) for _ in range(10)]
exp2 = [random.randint(10, 99) for _ in range(10)]
print("\n\n--------Question 2 Part 1----------\n")

exp1_res = find_profit(exp1)
buy_index = exp1.index(exp1_res[0])
sell_index = exp1.index(exp1_res[1])
print("Example 1-----------")
print(exp1)
print("Buy on 𝐷𝑎𝑦{0} for {1} and sell on 𝐷𝑎𝑦{2} for {3}.".format(buy_index,exp1_res[0],sell_index,exp1_res[1]))

exp1_res = find_profit(exp2)
buy_index = exp2.index(exp1_res[0])
sell_index = exp2.index(exp1_res[1])
print("\nExample 2----------")
print(exp2)
print("Buy on 𝐷𝑎𝑦{0} for {1} and sell on 𝐷𝑎𝑦{2} for {3}.".format(buy_index,exp1_res[0],sell_index,exp1_res[1]))

print("\n\n--------Part 2----------\n")

exp1_res = b_part(exp1)
buy_index = exp1.index(exp1_res[0])
sell_index = exp1.index(exp1_res[1])
print("Example 1----------")
print("Buy on 𝐷𝑎𝑦{0} for {1} and sell on 𝐷𝑎𝑦{2} for {3}.".format(buy_index,exp1_res[0],sell_index,exp1_res[1]))

exp1_res = b_part(exp2)
buy_index = exp2.index(exp1_res[0])
sell_index = exp2.index(exp1_res[1])
print("Example 2----------")
print("Buy on 𝐷𝑎𝑦{0} for {1} and sell on 𝐷𝑎𝑦{2}for {3}.".format(buy_index,exp1_res[0],sell_index,exp1_res[1]))

#---------Question 3-----------
exp1 = [random.randint(10, 99) for _ in range(10)]
tmp = []
res = longest(exp1)
print("------Question 3--------------")
print(exp1)
print(res)

#---------Question 4-----------

score = [[25,30,25], [45,15, 11], [1, 88, 15], [9, 4, 23]]

print("\n\n------Part 1------\n")
print(score)
res = dynamic_programing(score,3,2)
print("results:{}".format(res))

print("\n------Part 2--------")
res = greedy(score,3,2)
print("results:{}".format(res))