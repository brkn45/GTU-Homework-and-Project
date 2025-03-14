def longestCommonSubstring(strings):
  if len(strings) == 1:
    return strings[0]
  else:
    mid = len(strings) // 2
    leftHalf = strings[:mid]
    rightHalf = strings[mid:]
    leftSubstring = longestCommonSubstring(leftHalf)
    rightSubstring = longestCommonSubstring(rightHalf)
    return longestCommonSubstringHelper(leftSubstring, rightSubstring)

def longestCommonSubstringHelper(left, right):
  print(left)
  print(right)  
  minLength = min(len(left), len(right))
  for i in range(minLength):
    if left[i] != right[i]:
      return left[:i]
  return left[:minLength]

# Test the algorithm
strings = ["programmable", "programming",
 "programmer", "programmatic", "programmability"]
print(longestCommonSubstring(strings)) # prints "h"