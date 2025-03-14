package hw5;
import java.util.Arrays;
import java.util.ListIterator;
import java.util.Iterator;

/**
 * Question 3
 * @author berkan
 *
 * @param <E>
 */
public class BinaryHeap<E> extends BinaryTree<E>{
    private int[] Heap;
    private int size;
    private int maxsize;
    int index=0;
    private static final int FRONT = 0;
    
    public BinaryHeap(int maxsize)
    {
        this.maxsize = 100;
        this.size = 0;
        Heap = new int[1000+ 1];
        Heap[0] = Integer.MIN_VALUE;
    }
  
    /** 
    * Function to return the position of
    *the parent for the node currently
    * at pos
    */
    private int parent(int pos)
    {
        return pos / 2;
    }
  
    // Function to return the position of the
    // left child for the node currently at pos
    private int leftChild(int pos)
    {
        return (2 * pos);
    }
  
    /** Function to return the position of
     *the right child for the node currently
     *at pos
     * @param pos
     * @return
     */
    private int rightChild(int pos)
    {
        return (2 * pos) + 1;
    }
  
    /** Function that returns true if the passed
    *node is a leaf node
     * 
     * @param pos
     * @return
     */
    private boolean isLeaf(int pos)
    {
        if (pos >= (size / 2) && pos <= size) {
            return true;
        }
        return false;
    }
  
    /**
     * Function to swap two nodes of the heap
     * @param fpos
     * @param spos
     */
    private void swap(int fpos, int spos)
    {
        int tmp;
        tmp = Heap[fpos];
        Heap[fpos] = Heap[spos];
        Heap[spos] = tmp;
    }
  
    /**Function to heapify the node at pos
     * 
     * @param pos
     */
    private void BinaryHeapify(int pos)
    {
  
        // If the node is a non-leaf node and greater
        // than any of its child
        if (!isLeaf(pos)) {
            if (Heap[pos] > Heap[leftChild(pos)]
                || Heap[pos] > Heap[rightChild(pos)]) {
  
                // Swap with the left child and heapify
                // the left child
                if (Heap[leftChild(pos)] < Heap[rightChild(pos)]) {
                    swap(pos, leftChild(pos));
                    BinaryHeapify(leftChild(pos));
                }
  
                // Swap with the right child and heapify
                // the right child
                else {
                    swap(pos, rightChild(pos));
                    BinaryHeapify(rightChild(pos));
                }
            }
        }
    }
  
    /** Function to insert a node into the heap
     * 
     * @param element 
     */
    public void insert(int element)
    {
        if (size >= maxsize) {
            return;
        }
        Heap[size] = element;
        int current = size;
        size++;
        while (Heap[current] < Heap[parent(current)]) {
            swap(current, parent(current));
            current = parent(current);
        }
    }
  
    /** Function to print the contents of the heap
     * 
     */
    public void print()
    {
        for (int i = 1; i <= size / 2; i++) {
            System.out.print(" PARENT : " + Heap[i]
                             + " LEFT CHILD : " + Heap[2 * i]
                             + " RIGHT CHILD :" + Heap[2 * i + 1]);
            System.out.println();
        }
    }
  
    /** Function to build the min heap using
     * the BinaryHeapify
     * 
     */
    public void minHeap()
    {
        for (int pos = (size / 2); pos >= 1; pos--) {
            BinaryHeapify(pos);
        }
        root =insertLevelOrder(Heap, root, 0);
        
    }
  public void printAll() {
	  for(int i=0;i< size;i++) {
		  System.out.println(Heap[i]);
	  }
  }
    /**Function to remove and return the minimum
     *element from the heap
     * 
     * @return removed Element
     */
    public int removet()
    {
        int popped = Heap[FRONT];
        size--;
        Heap[FRONT] = Heap[size];
        BinaryHeapify(FRONT);
        root =insertLevelOrder(Heap, root, 0);
        return popped;
    }
    /**
     * Merge 2 Heap Structrue
     * @param BinaryHeap1 take elemant other parameter
     * @param BinaryHeap2 give element to firts parameter
     */
    public void heapMerge(BinaryHeap BinaryHeap1,BinaryHeap BinaryHeap2) {
    	for(int i=0;i<BinaryHeap2.size;i++) {
    		BinaryHeap1.insert(BinaryHeap2.Heap[i]);
    	}
    	BinaryHeap1.minHeap();
    }
    /**
     * Searc element if there are in heap
     * @param value search in heap
     * @return
     */
    public boolean search(int value) {
    	for(int i=0;i<this.size;i++) {
    		if(this.Heap[i]==value) {
    			return true;
    		}
    	}
		return false;
    }
    /**
     * Print smallest to biggest
     * @param root 
     */
    public void inOrder(Node root)
    {
        if (root != null) {
            inOrder(root.left);
            System.out.print(root.data + " ");
            inOrder(root.right);
        }
    }
    /**
     * Translate Heap array to Binary Tree 
     * @param arr Heap Array
     * @param root Binary tree root
     * @param i  array index
     * @return root node
     */
    public Node insertLevelOrder(int[] arr, Node root, int i){
		// Base case for recursion
		if (i < size) {
		Node temp = new Node(arr[i]);
		root = temp;
		
		// insert left child
		root.left = insertLevelOrder(arr, root.left,2 * i + 1);
		
		// insert right child
		root.right = insertLevelOrder(arr, root.right,2 * i + 2);
		}
		return root;
		}
    
   
}   
