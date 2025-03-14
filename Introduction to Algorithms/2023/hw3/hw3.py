################# Question 1
def calc_discount(set_of_stores): #Asumes Function
   
    return len(set_of_stores)

def findMaxDiscount(stores, currentSet):
    if not stores:
        return calc_discount(currentSet), currentSet

    maxDiscount = 0
    bestSet = None

    for store in stores:
        newSet = currentSet + [store]
        remainingStores = [s for s in stores if s != store]
        discount, _ = findMaxDiscount(remainingStores, newSet)

        if discount > maxDiscount:
            maxDiscount = discount
            bestSet = newSet

    return maxDiscount, bestSet

# Test case
initialStores = ["Store1", "Store2", "Store3"]
maxDiscount, maxDiscountSet = findMaxDiscount(initialStores, [])
print("Max Discount", maxDiscount)
print("Best Shop Set:", maxDiscountSet)

#  test case
initialStores2 = ["ShopA", "ShopB"]
maxDiscount, maxDiscountSet = findMaxDiscount(initialStores2, [])
print("Max Discount", maxDiscount)
print("Best Shop Set:", maxDiscountSet)

################### Question 2

def exhaustiveSearch(costMatrix):
    n = len(costMatrix)
    minCost = float('inf')
    optimalAssignment = []

    def generateAssignments(currentAssignment, assignedUsers):
        nonlocal minCost, optimalAssignment
        if len(currentAssignment) == n:
            totalCost = calculateTotalCost(currentAssignment, costMatrix)
            if totalCost < minCost:
                minCost = totalCost
                optimalAssignment = currentAssignment[:]
        else:
            for user in range(n):
                if user not in assignedUsers:
                    newAssignment = currentAssignment + [user]
                    newUserSet = assignedUsers.copy()
                    newUserSet.add(user)
                    generateAssignments(newAssignment, newUserSet)

    generateAssignments([], set())

    return minCost, optimalAssignment

def calculateTotalCost(assignment, costMatrix):
    totalCost = 0
    for processor, user in enumerate(assignment):
        totalCost += costMatrix[processor][user]
    return totalCost

# Test Case
costMatrix = [
    [2, 3, 1],
    [4, 2, 5],
    [3, 1, 4]
]

min_cost, assignment = exhaustiveSearch(costMatrix)
print("Minimum Cost:", min_cost)
print("Optimal Assignment:", assignment)


##################### Question 3

def findMinimumEnergySequence(parts):
    min_energy = float('inf')
    min_sequence = []

    def allPermutations(current, remaining):
        if not remaining:
            return [current]
        permutations = []
        for i, part in enumerate(remaining):
            new_remaining = remaining[:i] + remaining[i+1:]
            permutations += allPermutations(current + [part], new_remaining)
        return permutations

    for sequence in allPermutations([], parts):
        energy = calculateEnergy(sequence)
        if energy < min_energy:
            min_energy = energy
            min_sequence = sequence

    return min_sequence, min_energy

def calculateEnergy(sequence): #asumes function 
    
    return sum(sequence)  

# Main execution
parts = [1, 2, 3, 4]  # Example parts list
optimal_sequence, energy_cost = findMinimumEnergySequence(parts)
print("Optimal sequence:", optimal_sequence)
print("Energy cost:", energy_cost)

###################### Question 4

def minCoins(coins, target):
    INF = float('inf')
    minCoins = [INF] * (target + 1)
    minCoins[0] = 0

    for i in range(1, target + 1):
        for j in range(len(coins)):
            if coins[j] <= i:
                subResult = minCoins[i - coins[j]]
                if subResult != INF and subResult + 1 < minCoins[i]:
                    minCoins[i] = subResult + 1

    return minCoins[target]

#Example Test Case
coins = [1, 3, 4]
target_amount = 6
result = minCoins(coins, target_amount)
print(f"Minimum number of coins needed for {target_amount}: {result}")
