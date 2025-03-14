package hw7;

public class Q2<E extends Comparable> {
	/**
	 * main function Question 2 
	 * @param bst
	 * @return AVL Tree
	 */
	public  BinarySearchTree transformation(BinarySearchTree bst) {
		BinarySearchTree tmp = new BinarySearchTree();
		
		if(bst.root != null) {
			bst.root = inOrder(bst.root);
			
		}
		return bst;
	}
	/**
	 * Send every node in rotation function. function traverse the tree recursively 
	 * @param root
	 * @return
	 */
	private BinaryTree.Node<E> inOrder(BinaryTree.Node<E> root){
		if (root == null)
            return null;
		root =rotation(root);
		root.left =inOrder(root.left);
		root =rotation(root);
		root.right =inOrder(root.right);
		root =rotation(root);
		return root;
	}
	// A utility function to
    // do inorder traversal of BST
	/**
	 * function controll the tree for balance, if tree is not balanced, call bstRotation function then this fix
	 * @param root
	 * @return
	 */
    private BinaryTree.Node<E> rotation(BinaryTree.Node<E> root)
    {
    	if(root != null) {
    		int balance = getBalance(root);
    	
        		while(balance >1 || balance < -1) {
        			root =bstRotation(root);
        			balance = getBalance(root);
        		}
        	
    		
        	return root;
    	}
    	else {
    		return null;
    	}
    }
    /**
     * if tree is not balance , turn node
     * @param root
     * @return
     */
	private BinaryTree.Node<E> bstRotation(BinaryTree.Node<E> root) {
	  int balance = getBalance(root);
	
	  // If this node becomes unbalanced, then there
	  // are 4 cases
	  // Left Left Case
	  if(root.left != null && root.left.left != null) {
		  if (balance > 1 
					&& maxDepth(root.left) - maxDepth(root.left.left) > 0) {
					  
					  root = rightRotate(root);
				  }
	  }
	  
	      
	
	  // Right Right Case
	  if(root.right != null && root.right.right != null ) {
		  if (balance < -1 &&
				  maxDepth(root.right) - 
				  maxDepth(root.right.right) > 0  )
		      root = leftRotate(root);
	  }
	  
	
	  // Left Right Case
	  if(root.left != null && root.left.right != null) {
		  if (balance > 1 && 
				  maxDepth(root.left.right)
				  - maxDepth(root.left.left)  > 0) {
		      root.left = leftRotate(root.left);
		       root = rightRotate(root);
		  }
	  }
	  // Right Left Case
	  if(root.right != null  && root.right.left != null) {
		  if (balance < -1 && 
				  maxDepth(root.right.left) 
				  - maxDepth(root.right.right) >0) {
		      root.right = rightRotate(root.right);
		      root = leftRotate(root);
		  }
	  }
	 
		return root;
		
	}
	// A utility function to right rotate subtree rooted with y
    // See the diagram given above.
    public BinaryTree.Node<E> rightRotate(BinaryTree.Node<E> y) {
    	BinaryTree.Node<E> x = y.left;
    	BinaryTree.Node<E> T2 = x.right;
 
        // Perform rotation
        x.right = y;
        y.left = T2;
 
        // Return new root
        return x;
    }
	// A utility function to left rotate subtree rooted with x
    // See the diagram given above.
    public BinaryTree.Node<E> leftRotate(BinaryTree.Node<E> x) {
    	BinaryTree.Node<E> y = x.right;
    	BinaryTree.Node<E> T2 = y.left;
 
        // Perform rotation
        y.left = x;
        x.right = T2;
 
        //  Update heights
       
 
        // Return new root
        return y;
    }
	/* Compute the "maxDepth" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
	public int maxDepth(BinaryTree.Node<E> node){
	     if (node == null)
	         return -1;
	     else{
	         /* compute the depth of each subtree */
	         int lDepth = maxDepth(node.left);
	         int rDepth = maxDepth(node.right);
	
	         /* use the larger one */
	         if (lDepth > rDepth)
	             return (lDepth + 1);
	          else
	             return (rDepth + 1);
	     }
	 }
	
	// Get Balance factor of node N
    int getBalance(BinaryTree.Node<E> root) {
        if (root == null)
            return 0;
 
        return maxDepth(root.left) - maxDepth(root.right) ;
    }
}
