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

def longest_subarray(array):
   
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

array = [1, 4, 5, 2, 4, 3, 6, 7, 1, 2, 3, 4, 7]
arr =longest_subarray(array)
print(arr)