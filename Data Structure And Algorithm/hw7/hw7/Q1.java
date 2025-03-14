package hw7;

import java.util.Arrays;

import hw7.BinaryTree.Node;

public class Q1<E extends Comparable> {
	 protected boolean addReturn;
	/**
	 * Main Function for Question 1
	 * @param arr
	 * @param bt
	 * @return
	 */
	public BinarySearchTree transformation(E []arr,BinaryTree<E> bt ) {
		int index;
		E value;
		int i=0; 
		 Arrays.sort(arr);
		
		while(i<arr.length) {
		
			add(bt.root,arr[i]);
			i++;
			
		}
		BinarySearchTree bst = new BinarySearchTree();
		bst.root = bt.root;
		return bst;
		
	}
	/**
	 * Helper function search recursively and put optimal in node 
	 * @param localRoot
	 * @param item
	 * @return
	 */
	private boolean add(BinaryTree.Node<E> localRoot ,E item) {
		boolean flag =false;
		
		if(localRoot != null) {
			if(localRoot.left != null) {
				 flag = add(localRoot.left,item);
			}
			if(flag == false && localRoot.status == false) {
				localRoot.data = item;
				localRoot.status = true;
				return true;
			}
			if( flag == false && localRoot.right != null) {
				return add(localRoot.right,item);
			}
			return flag;
		}
		return flag;	   
	}
	
}
