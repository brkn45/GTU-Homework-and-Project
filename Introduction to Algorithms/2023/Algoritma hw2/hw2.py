#question 2
class TreeNode:
    def __init__(self, value):
        self.val = value
        self.left = None
        self.right = None

def is_balanced(root):
    def check_balance(node):
        if not node:
            return True, 0
        
        left_balanced, left_height = check_balance(node.left)
        right_balanced, right_height = check_balance(node.right)
        
        balanced = abs(left_height - right_height) <= 1
        height = max(left_height, right_height) + 1
        
        return balanced and left_balanced and right_balanced, height
    
    balanced, _ = check_balance(root)
    return balanced

#B
def height_of_tree(root):
    if not root:
        return 0
    
    left_height = height_of_tree(root.left)
    right_height = height_of_tree(root.right)
    
    height = max(left_height, right_height) + 1
    
    return height

# Balanced BSTBST
# 
#        5
#       / \
#      3   8
#     / \
#    1   4
root = TreeNode(5)
root.left = TreeNode(3)
root.right = TreeNode(8)
root.left.left = TreeNode(1)
root.left.right = TreeNode(4)

#A
result = is_balanced(root)
if result:
    print("This BST is Balanced.")
else:
    print("This BST  is not Balanced.")

tree_height = height_of_tree(root)
print("Height of the tree:", tree_height)
print("Added Node to Below")
# Not Balanced BST
# 
#        5
#       / \
#      3   8
#     / \
#    1   4
#         \
#          5
root.left.right.right = TreeNode(5)
result = is_balanced(root)
if result:
    print("This BST is Balanced.")
else:
    print("This BST  is not Balanced.")


#B
def height_of_tree(root):
    if not root:
        return 0
    
    left_height = height_of_tree(root.left)
    right_height = height_of_tree(root.right)
    
    height = max(left_height, right_height) + 1
    
    return height

tree_height = height_of_tree(root)
print("Height of the tree:", tree_height)