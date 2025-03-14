package hw5;
/**
 * Question 4
 * @author berkan
 *
 * @param <E>
 */
public interface SearchTree<E> {
	public void add(E data);
	public boolean contains(E data);
	public E find(E data);
}
