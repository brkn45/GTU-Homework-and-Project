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



exp1 = [10, 11, 10, 9, 8, 7, 9, 11]
exp2 = [100, 110, 80, 90, 110, 70, 80, 80, 90]
print("\n\n--------Part 1----------\n")

exp1_res = find_profit(exp1)
buy_index = exp1.index(exp1_res[0])
sell_index = exp1.index(exp1_res[1])
print("Example 1-----------")
print("Buy on 𝐷𝑎𝑦{0} for {1} and sell on 𝐷𝑎𝑦{2} for {3}.".format(buy_index,exp1_res[0],sell_index,exp1_res[1]))

exp1_res = find_profit(exp2)
buy_index = exp2.index(exp1_res[0])
sell_index = exp2.index(exp1_res[1])
print("\nExample 2----------")
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