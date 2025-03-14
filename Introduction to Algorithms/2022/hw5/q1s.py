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