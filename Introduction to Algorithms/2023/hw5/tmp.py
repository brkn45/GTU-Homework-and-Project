def find_peak_element(arr, low, high):
    """ Find the index of the peak element in a bitonic array using divide and conquer. """
    if low == high:
        return low

    mid = (low + high) // 2

    # Check if the mid element is greater than its neighbors
    if (mid == 0 or arr[mid - 1] <= arr[mid]) and (mid == len(arr) - 1 or arr[mid + 1] <= arr[mid]):
        return mid
    # If the mid element is less than its left neighbor, then the peak lies on the left side
    elif mid > 0 and arr[mid - 1] > arr[mid]:
        return find_peak_element(arr, low, mid-1)
    # If the mid element is less than its right neighbor, then the peak lies on the right side
    else:
        return find_peak_element(arr, mid + 1, high)

def find_peak(arr):
    """ Wrapper function to find peak element index in a bitonic array. """
    return find_peak_element(arr, 0, len(arr) - 1)

# Example array
arr = [1, 3, 8, 12, 4, 2]
peak_index = find_peak(arr)
peak_index


def greedy_change_making(coins, amount):
    """
    Solve the change making problem using a greedy approach.
    :param coins: List of coin denominations.
    :param amount: The amount of money to make change for.
    :return: The minimum number of coins needed to make change for the given amount.
    """
    coins.sort(reverse=True)  # Sort the coins in descending order
    count = 0
    for coin in coins:
        while amount >= coin:
            amount -= coin
            count += 1

    return count if amount == 0 else -1  # Return -1 if no solution exists

# Example coin denominations and amount
coins = [1, 5, 10, 25]  # US coin denominations
amount = 63  # Example amount

# Find the minimum number of coins
min_coins = greedy_change_making(coins, amount)
min_coins
