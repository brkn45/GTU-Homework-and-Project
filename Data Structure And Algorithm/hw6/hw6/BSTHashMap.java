package hw6;

public class BSTHashMap< K extends Comparable, V extends Comparable > implements KWHashMap<K, V> {
	
	private BinarySearchTree [] table;

	  /** The number of keys */
	  private int numKeys;

	  /** The capacity */
	  private static final int CAPACITY = 101;

	  /** The maximum load factor */
	  private static final double LOAD_THRESHOLD = 3.0;

	 

	
	
	public BSTHashMap() {
	    table = new BinarySearchTree[CAPACITY];
	  }

	  /** Method get for class HashtableChain.
	      @param key The key being sought
	      @return The value associated with this key if found;
	              otherwise, null
	   */
	  public V get(K key) {
	    int index = key.hashCode() % table.length;
	    if (index < 0)
	      index += table.length;
	    if (table[index] == null)
	      return null; // key is not in the table.

	    // Search the list at table[index] to find the key.
	   
	    

	    // assert: key is not in the table.
	    return (V) table[index].search( key).value;
	  }

	  /** Method put for class HashtableChain.
	      post: This key-value pair is inserted in the
	            table and numKeys is incremented. If the key is already
	            in the table, its value is changed to the argument
	            value and numKeys is not changed.
	      @param key The key of item being inserted
	      @param comparable The value for this key
	      @return The old value associated with this key if
	              found; otherwise, null
	   */
	  public V put(Comparable key, Comparable comparable) {
	    int index = key.hashCode() % table.length;
	    if (index < 0)
	      index += table.length;
	    if (table[index] == null) {
	      // Create a new linked list at table[index].
	      table[index] = new BinarySearchTree < K, V > ();
	    }
	    
	    table[index].insert(key,comparable);
	
	    numKeys++;
	    if (numKeys > (LOAD_THRESHOLD * table.length))
	      rehash();
	    return null;
	  }

	  /** Returns the number of entries in the map */
	  public int size() {
	    return numKeys;
	  }

	  /** Returns true if empty */
	  public boolean isEmpty() {
	    return numKeys == 0;
	  }

	  /**** BEGIN EXERCISE ****/
	  public V remove(K key) {
	    int index = key.hashCode() % table.length;
	    if (index < 0)
	      index += table.length;
	    if (table[index] == null)
	      return null; // Key not in table
	    table[index].deleteKey((Comparable) key);
	    
	    
	    return null; // Key not in table
	  }

	  /** Expands table size when loadFactor exceeds LOAD_THRESHOLD
	      post: the size of table is doubled and is an
	      odd integer. Each non-deleted entry from the original
	      table is reinserted into the expanded table.
	      The value of numKeys is reset to the number of items
	      actually inserted; numDeletes is reset to 0.
	   */
	  public void rehash() {
	    // Save a reference to oldTable
		  BinarySearchTree  [] oldTable = table;
	    // Double capacity of this table
	    table = new BinarySearchTree[2 * oldTable.length + 1];

	    // Reinsert all items in oldTable into expanded table.
	    numKeys = 0;
	    for (int i = 0; i < oldTable.length; i++) {
	      if (oldTable[i] != null) {
	        while(oldTable[i].root != null) {
	          // Insert entry in expanded table
	          put(oldTable[i].root.key,oldTable[i].root.value);
	          oldTable[i].deleteKey(oldTable[i].root.key);
	        }
	      }
	    }
	  }

	
	
	public void printTable() {
		int i=0;
		for(i=0;i<table.length;i++) {
			if(table[i] != null) {
				System.out.println("\nIndex: " + i);
				table[i].inorder();
			}
		}
	}
	
	

}
