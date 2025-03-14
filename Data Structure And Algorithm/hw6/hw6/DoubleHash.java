package hw6;

public class DoubleHash< K, V > implements KWHashMap < K, V > {
	// Data Fields
	private Entry < K, V > [] table;
	private static final int START_CAPACITY = 10;
	private double LOAD_THRESHOLD = 0.75;
	private int numKeys;
	private int numDeletes;
	private final Entry < K, V > DELETED = new Entry < K, V > (null, null);
	
	// Constructor
	public DoubleHash() {
		table = new Entry[START_CAPACITY];
		numKeys =0;
		numDeletes =0;
	}
	
	/** Contains key-value pairs for a hash table. */
	private static class Entry < K, V > {
	
		/** The key */
		private K key;
		
		/** The value */
		private V value;
		
		private Entry next;
		private int index;
		/**
		 * @return the next
		 */
		public Entry getNext() {
			return next;
		}

		/**
		 * @param next the next to set
		 */
		public void setNext(Entry next) {
			this.next = next;
		}

		/**
		 * @return the index
		 */
		public int getIndex() {
			return index;
		}

		/**
		 * @param index the index to set
		 */
		public void setIndex(int index) {
			this.index = index;
		}

		/**
		 * @param key the key to set
		 */
		public void setKey(K key) {
			this.key = key;
		}

		
		
		
		/** Creates a new key-value pair.
		    @param key The key
		    @param value The value
		 */
		public Entry(K key, V value) {
		  this.key = key;
		  this.value = value;
		  this.index = -1;
		}
		
		/** Retrieves the key.
		    @return The key
		 */
		public K getKey() {
		  return key;
		}
		
		/** Retrieves the value.
		    @return The value
		 */
		public V getValue() {
		  return value;
		}
		
		/** Sets the value.
		    @param val The new value
		    @return The old value
		 */
		public V setValue(V val) {
		  V oldVal = value;
		  value = val;
		  return oldVal;
		}
	}
	
	/** Returns the number of entries in the map */
	public int size() {
		return numKeys;
	}
	
	/** Returns true if empty */
	public boolean isEmpty() {
		return numKeys == 0;
	}

	@Override
	public V get(K key) {
		int index = hashFunction(key,0)%table.length;
		if(table[index].key.equals(key)) {
			return table[index].value;
		}
		else {
			int tmpIndex;
			while(table[index].index != -1) {
				index = table[index].index;
				if(table[index].key.equals(key)) {
					return table[index].value;
				}
				
			}
			return null;
		}
	}

	@Override
	public V put(K key, V value) {
		int index = hashFunction(key,0);
		int i=0,fullIndex;
	
		double loadFactor =
		          (double) (numKeys + numDeletes) / table.length;
		      if (loadFactor > LOAD_THRESHOLD)
		        rehash();
		      
		if(table[index] == null || table[index] == DELETED ) {
			table[index] = new Entry(key,value);
			numKeys++;
			return value;
		}
		else {
			while(i<table.length) {
				i++;
				fullIndex = index;
				index = hashFunction(key,i);
				if(table[index] == null || table[index] == DELETED) {
					table[index] = new Entry(key,value);
					table[fullIndex].index = index;
					table[fullIndex].next = table[index];
					numKeys++;
					return value;
				}	
			}
			
		}
		
		return null;
	}
	
	private int hash1(K key) {
		//System.out.println("key: "+key +"  hashCode:" + key.hashCode());
		return key.hashCode()%table.length;
	}
	
	private int hash2(K key) {
		int primeNum = primeNumber((int) Math.round(table.length*0.8));
		//System.out.println("PrimeNumber: " +primeNum);
		return primeNum - (key.hashCode()%primeNum);
	}
	private int hashFunction(K key,int i) {
		int hash1 = hash1(key);
		int hash2 = hash2(key);
		return (hash1+(i*hash2))%table.length;
	}
	public int primeNumber(int n)
    {
 
        // All prime numbers are odd except two
        if (n % 2 != 0)
            n -= 2;
        else
            n--;
 
        int i, j;
        for (i = n; i >= 2; i -= 2) {
            if (i % 2 == 0)
                continue;
            for (j = 3; j <= Math.sqrt(i); j += 2) {
                if (i % j == 0)
                    break;
            }
            if (j > Math.sqrt(i))
                return i;
        }
 
        // It will only be executed when n is 3
        return 2;
    }
	
	private void rehash() {
	    // Save a reference to oldTable.
	    Entry < K, V > [] oldTable = table;
	    // Double capacity of this table.
	    table = new Entry[2 * oldTable.length + 1];

	    // Reinsert all items in oldTable into expanded table.
	    numKeys = 0;
	    numDeletes = 0;
	    for (int i = 0; i < oldTable.length; i++) {
	      if ( (oldTable[i] != null) && (oldTable[i] != DELETED)) {
	        // Insert entry in expanded table
	        put(oldTable[i].key, oldTable[i].value);
	      }
	    }
	}
	/** Remove the item with a given key value
	   *  @param key The key to be removed
	   *  @return The value associated with this key, or null
	   *  if the key is not in the table.
	   */
	  public V remove(K key) {
		  int index = hashFunction(key,0)%table.length;
			if(table[index].key.equals(key)) {
				V oldValue = table[index].value;
			    table[index] = DELETED;
			    numKeys--;
				return oldValue;
			}
			else {
				int fullIndex;
				while(table[index].index != -1) {
					fullIndex = index;
					index = table[index].index;
					if(table[index].key.equals(key)) {
						V oldValue = table[index].value;
					    table[index] = DELETED;
					    numKeys--;
					    table[fullIndex].index =-1;
					    table[fullIndex].next = null;
						return oldValue;
					}
					
				}
			}
			return null;
		}
	
	public void printTable() {
		int i=0;
	
		for(i=0;i<table.length;i++) {
			if(table[i] != null) {
				System.out.println(i  + "  " + table[i].key + "/"+ table[i].value +"  " + table[i].index);
			}
			else {
				System.out.println(i  + "  " + "null" +"  " + "null");
			}
			
			
		}
	}
	
}
