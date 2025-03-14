package hw5;
/**
 * Question 4
 * @author berkan
 *
 * @param <E>
 */
public class ArrayTree<E extends Comparable<E> > implements SearchTree<E>  {
	  /**
     * Put Data
     */
	public static class Node<E> {
	    private E data;
	    private Node lChild;
	    private Node rChild;
	  
	    public Node() {
	        //// no loose end; otherwise it comes back to bite you
	        lChild = rChild = null;
	        data = null;
	    }
	    public Node (E data) {
	    	lChild = rChild = null;
	    	this.data = data;
	    }
	    public E getData() {
	        return data;
	    }

	    public void setData(E data) {
	        this.data = data;
	    }

	    public Node getlChild() {
	        return lChild;
	    }

	    public void setlChild(Node lChild) {
	        this.lChild = lChild;
	    }

	    public Node getrChild() {
	        return rChild;
	    }

	    public void setrChild(Node rChild) {
	        this.rChild = rChild;
	    }
	}
	
	    private Node []array;
	    private static final int SIZE = 128;

	    public ArrayTree() {
	        array = new Node[SIZE];
	        //ensure all nulls
	        // don't need to
	        for (int i = 0; i < array.length; i++) {
	            array[i] = null;
	        }
	    }
	    /**
	     * Add Data in BST Array
	     */
	    @Override
	    public void add(E data) {
	        if (array[0] == null) {
	        	array[0] = new Node(data);
	            
	            return;
	        }

	        recAdd(0, data);
	    }
	    /**
	     * Helper Function Add Method.
	     * @param root
	     * @param data
	     */
	    private void recAdd(int root, E data) {
	        if (array[root] == null) {
	            return;
	        }
	        int res = data.compareTo((E) array[root].getData());
	        if (res < 0) {
	            // this is the formula to access the left node
	            if (array[root * 2 + 1] == null) {
	                array[root * 2 + 1] = new Node(data);
	                return;
	            } else {
	                recAdd(root * 2 + 1, data);
	            }

	        } else {
	            // this is the formula to access the right node
	            if (array[root * 2 + 2] == null) {
	                array[root * 2 + 2] = new Node(data);
	                return;
	            } else {
	                recAdd(root * 2 + 2, data);
	            }

	        }
	    }
	    /**
	     * Print inOrder data. Smallet to Bigest
	     */
	    public void inOrder() {
	        inOrder(0);
	    }

	    private void inOrder(int root) {
	        if (array[root] == null) {
	            return;
	        }

	        inOrder(root * 2 + 1);
	        System.out.print(array[root].getData() + " ");
	        inOrder(root * 2 + 2);
	    }

	    @Override
	    public String toString() {
	        String rtn = "";
	        for (int i = 0; i < array.length; i++) {
	            if (array[i] != null) {
	                rtn += array[i].getData().toString() + " ";
	            }
	        }

	        return rtn;
	    }
	    /**
	     * Check data if there ara in BST Array
	     */
		@Override
		public boolean contains(E data) {
			return contains(0,data);
		}
		/**
		 * Helper fonction for Contains
		 * @param root
		 * @param data
		 * @return
		 */
		private boolean contains(Integer root,E data) {
				
				
				if(array[root] == null) {
					return false;
				}
				int res = data.compareTo((E) array[root].getData());
				if(res == 0) {
					return true;
				}
				
		        if (res < 0) {
		            
		                return contains(root * 2 + 1, data);
		            

		        } else {
		            // this is the formula to access the right node
		            
		               return contains(root * 2 + 2, data);
		            

		        }
			 
			
		}
		/*
		 * Find Data if there ara in BST Array then return it;
		 */
		@Override
		public E find(E data) {
			if(contains(data)) {
				return data;
			}
			else {
				return null;
			}
			
		}
		
		
	}
