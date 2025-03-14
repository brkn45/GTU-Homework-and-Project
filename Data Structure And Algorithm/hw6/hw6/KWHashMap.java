package hw6;

public interface KWHashMap< K, V > {

	  V get(K key);

	  V put(K key, V value);

	  V remove(K key);

	  int size();

	  boolean isEmpty();

	}
