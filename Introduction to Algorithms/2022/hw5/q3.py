def longest(arr,tmp) :
    
    if(len(arr) ==1) :
        return tmp
    else :
        if arr[0] < arr[1] :
            tmp.append(arr[0])
            arr2= longest(arr[1:],tmp)
        else :
            
            return tmp
        tmp = []    
        arr3  = longest(arr[1:],tmp)

        if(len(arr2) > len(arr3)) :
            return arr2
        else :
            return arr3    
exp1 = [1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7]
tmp = []
res = longest(exp1,tmp)

print(res)
