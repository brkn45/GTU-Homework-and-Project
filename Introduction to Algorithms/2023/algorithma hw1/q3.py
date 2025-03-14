class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

#A
def MergeBSTs(BST1, BST2):
    if BST1 is not None:
        MergeBSTs(BST1.left, BST2)
        Insert(BST1.val, BST2)
        MergeBSTs(BST1.right, BST2)

def Insert(element, BST):
    if BST is None:
        return TreeNode(element)
    
    if element < BST.val:
        BST.left = Insert(element, BST.left)
    else:
        BST.right = Insert(element, BST.right)
    
    return BST

#B
def KthSmallest(root, k):
    count = 0
    result = None
    
    def InOrderTraversal(node):
        nonlocal count, result
        
        if node is None or count >= k:
            return
        
        InOrderTraversal(node.left)
        count += 1
        
        if count == k:
            result = node.val
            return
        
        InOrderTraversal(node.right)
    
    InOrderTraversal(root)
    return result

# C
def BalanceBST(root):
    nodes = InOrderTraversal(root)
    sortedArray = sorted(nodes)
    return BuildBalancedBST(sortedArray)

def BuildBalancedBST(sortedArray):
    if not sortedArray:
        return None
    
    middle = len(sortedArray) // 2
    root = TreeNode(sortedArray[middle])
    root.left = BuildBalancedBST(sortedArray[:middle])
    root.right = BuildBalancedBST(sortedArray[middle+1:])
    return root

def InOrderTraversal(root):
    if root is None:
        return []
    return InOrderTraversal(root.left) + [root.val] + InOrderTraversal(root.right)

#D
def RangeSearch(BST, min_val, max_val, result):
    if BST is None:
        return
    
    if BST.val >= min_val:
        RangeSearch(BST.left, min_val, max_val, result)
    
    if min_val <= BST.val <= max_val:
        result.append(BST.val)
    
    if BST.val <= max_val:
        RangeSearch(BST.right, min_val, max_val, result)

#A Test: 

bst1 = TreeNode(2)
bst1.left = TreeNode(1)
bst1.right = TreeNode(3)

bst2 = TreeNode(5)
bst2.left = TreeNode(4)
bst2.right = TreeNode(6)

def InOrderTraversal(root):
    if root is None:
        return []
    return InOrderTraversal(root.left) + [root.val] + InOrderTraversal(root.right)

print("BST1: ", InOrderTraversal(bst1))
print("BST2: ", InOrderTraversal(bst2))

# BST1 and BST2 Merge
MergeBSTs(bst1, bst2)

print("Merged BST2 with BST1: ", InOrderTraversal(bst2))





#        4
#       / \
#      2   6
#     / \   \
#    1   3   7

root = TreeNode(4)
root.left = TreeNode(2)
root.right = TreeNode(6)
root.left.left = TreeNode(1)
root.left.right = TreeNode(3)
root.right.right = TreeNode(7)

#  B Test: KthSmallest
k = 3
result_b = KthSmallest(root, k)
print(f"{k}. Smalest Element: {result_b}")

#C Test:
balanced_root = BalanceBST(root)
print("balanced BST:")
print(InOrderTraversal(balanced_root))

#D Test:  
min_value = 2
max_value = 5
result_d = []
RangeSearch(balanced_root, min_value, max_value, result_d)
print("Range Searc")
print(f"Min: {min_value}, Max: {max_value}, Result: {result_d}")
