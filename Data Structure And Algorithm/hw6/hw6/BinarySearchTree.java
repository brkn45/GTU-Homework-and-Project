package hw6;

class BinarySearchTree<K extends Comparable,V extends Comparable > { 
    //node class that defines BST node
    class Node<K extends Comparable,V extends Comparable > { 
        K key;
        V value;
        Node<K,V> left, right;
		/**
		 * @return the key
		 */
		public K getKey() {
			return key;
		}
		/**
		 * @param key the key to set
		 */
		public void setKey(K key) {
			this.key = key;
		}
		/**
		 * @return the value
		 */
		public V getValue() {
			return value;
		}
		/**
		 * @param value the value to set
		 */
		public void setValue(V value) {
			this.value = value;
		}
		/**
		 * @return the left
		 */
		public Node<K,V> getLeft() {
			return left;
		}
		/**
		 * @param left the left to set
		 */
		public void setLeft(Node<K,V> left) {
			this.left = left;
		}
		/**
		 * @return the right
		 */
		public Node<K,V> getRight() {
			return right;
		}
		/**
		 * @param right the right to set
		 */
		public void setRight(Node<K,V> right) {
			this.right = right;
		}
		public Node(K key, V value) {
			super();
			this.key = key;
			this.value = value;
		} 
		
        
    } 
    // BST root node 
    Node<K,V> root; 
  
   // Constructor for BST =>initial empty tree
    BinarySearchTree(){ 
        root = null; 
    } 
    //delete a node from BST
    Node<K,V> deleteKey(K key) { 
        root = delete_Recursive(root, key); 
        if(root == null) {
        	return null;
        }
        else {
        	return root;
        }
        
    } 
   
    //recursive delete function
    Node<K,V> delete_Recursive(Node<K,V> root,K key)  { 
        //tree is empty
        if (root == null)  return root; 
   
        //traverse the tree
        if (key.compareTo(root.key) < 0)     //traverse left subtree 
            root.left = delete_Recursive(root.left, key); 
        else if (key.compareTo(root.key) > 0)  //traverse right subtree
            root.right = delete_Recursive(root.right, key); 
        else  { 
            // node contains only one child
            if (root.left == null) 
                return root.right; 
            else if (root.right == null) 
                return root.left; 
   
            // node has two children; 
            //get inorder successor (min value in the right subtree) 
            root.value =  minValue(root.right).value; 
            root.key = 		minValue(root.right).key;
            // Delete the inorder successor 
            root.right = delete_Recursive(root.right, root.key); 
        } 
        return root; 
    } 
   
    Node<K,V> minValue(Node<K,V> root)  { 
        //initially minval = root
        Node<K,V> minval = root; 
        //find minval
        while (root.left != null)  { 
            minval = root.left; 
            root = root.left; 
        } 
        return minval; 
    } 
   
    // insert a node in BST 
    void insert(K key,V value)  { 
        root = insert_Recursive(root, key, value); 
    } 
   
    //recursive insert function
    Node<K,V> insert_Recursive(Node<K,V> root, K key, V value) { 
          //tree is empty
        if (root == null) { 
            root = new Node(key,value); 
            return root; 
        } 
        //traverse the tree
        if (key.compareTo(root.key) < 0)     //insert in the left subtree
            root.left = insert_Recursive(root.left, key,value); 
        else if (key.compareTo(root.key) > 0)    //insert in the right subtree
            root.right = insert_Recursive(root.right, key,value); 
          // return pointer
        return root; 
    } 
 
// method for inorder traversal of BST 
    void inorder() { 
        inorder_Recursive(root); 
    } 
   
    // recursively traverse the BST  
    void inorder_Recursive(Node<K,V> root) { 
        if (root != null) { 
            inorder_Recursive(root.left); 
            System.out.print(root.value.toString() + " "); 
            inorder_Recursive(root.right); 
        } 
    } 
     
    public Node<K,V> search(K key)  { 
        root = search_Recursive(root,key); 
        if (root!= null)
            return root;
        else
            return null;
    } 
   
    //recursive insert function
    private Node<K,V> search_Recursive(Node<K,V> root, K key)  { 
        // Base Cases: root is null or key is present at root 
        if (root==null || root.key.compareTo(key)==0) 
            return root; 
        // val is greater than root's key 
        if (root.key.compareTo(key) > 0) 
            return search_Recursive(root.left, key); 
        // val is less than root's key 
        return search_Recursive(root.right, key); 
    }
	
}
