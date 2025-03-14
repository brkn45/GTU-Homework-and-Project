package hw1;

import java.util.AbstractList;

/**
 * Lazy Deletion Linked List has been re-implemented as desired in the assignment.
 * I keep the nodes I removed in a linklist. The head of them is deletedHead. DeletedIter keeps the last added node.
 * @author berkan
 *
 * @param <E>
 * 
 */
public class LDLinkedList<E> extends AbstractList<E> {
	
	private static class Node<E> {
		
		private E data;
		private Node<E> next;
		
		/**
		 * Node class that LDLinklist will use
		 * @param dataItem
		 * 
		 */
		private Node(E dataItem) {
			this.data = dataItem;
			
		}
		private Node(E dataItem,Node<E> nodeRef) {
			this.data =dataItem;
			this.next =nodeRef;
		}
	}
	private Node<E> head  = null;
	private int size =0;
	private Node<E> deletedHead; // keep Removed Node linkist head 
	private Node<E> deletedIter; // keep last removed Node 
	
	
	private Node<E> getNode(int index){
		Node<E> node = head;
		for(int i=0; i< index && node != null; i++) {
			node = node.next;
		}
		return node;
	}
	
	@Override
	public E get(int index) {
		if(index <0 || index >= size) {
			throw new IndexOutOfBoundsException(Integer.toString(index));
		}
		Node<E> node = getNode(index);
		return node.data;
	}

	@Override
	public int size() {
		// TODO Auto-generated method stub
		return 0;
	}
	public boolean add(E item) {
		add(size,item);
		return true;
	}
	@Override
	public void add(int index, E item){
		
		if(index ==0) {
			addFirst(item);
		}
		else {
			Node<E> node = getNode(index -1);
			addAfter(node,item);
		}
	}
	@Override
	public E set(int index, E newValue){
		if(index <0 || index >= size) {
			throw new IndexOutOfBoundsException(Integer.toString(index));
		}
		Node<E> node = getNode(index);
		E result = node.data;
		node.data = newValue;
		return result;
	}
	
	public void addFirst(E item) {
		if(deletedHead == null) {
			head = new Node<E>(item);
		}
		else {
			head = deletedIter;
			head.data = item;
			if(deletedHead == deletedIter) {
				deletedHead = null;
				deletedIter = null;
			}
			else {
				deletedHead = deletedHead.next;
			}
		}
		size++;
	}
	
	
	/**
	 * firstly controll delete node if there is than use it.
	 * @param node
	 * @param item
	 */
	private void addAfter(Node<E> node, E item) {
		if(deletedHead == null) { // if there is deleted node if there is not than create new Node
			node.next = new Node<E>(item,node.next);
		}
		else { // if there is node than use it and head next other node;
			deletedHead.next = node.next;
			node.next = deletedHead;
			deletedHead.data = item;
			if(deletedHead == deletedIter) {
				deletedHead = null;
				deletedIter = null;
			}
			else {
				deletedHead = deletedHead.next;
			}
		}
		size++;
	}
	/**
	 * If the node is to be removed, I get the node in the other arraylist.
	 * @param node
	 * @return
	 */
	private E removeAfter(Node<E> node) {
		Node<E> temp = node.next;
		if(deletedHead == null) {  // if removed Linklist empty 
			deletedHead = node.next; 
			deletedIter = node.next;
		}
		else { // if removed linklist iter a Node than deletedIter iter removed Node
			deletedIter.next = node.next;
			deletedIter = deletedIter.next;
		}
		if(temp != null) {
			node.next = temp.next;
			size--;
			return temp.data;
		}
		else {
			return null;
		}
	}
	/**
	 * If the node is to be removed, I get the node in the other arraylist.
	 * @param node
	 * @return
	 */
	private E removeFirst() {
		Node<E> temp = head;
		if(deletedHead == null) {
			deletedHead = head; // deleted linklist start
			deletedIter = head;
		}
		else {
			deletedIter.next = head;
			deletedIter = deletedIter.next;
		}
		if(head != null) {
			
			head = head.next;	
		}
		
		
		if(temp != null) {
			size--;
			return temp.data;
		}
		else {
			return null;
		}
	}
	/**
	 * If the node is to be removed, I get the node in the other arraylist.
	 * @param node
	 * @return
	 */
	public E remove(int index) {
		if(index <0 || index >= size) {
			throw new IndexOutOfBoundsException(Integer.toString(index));
		}
		if(index == 0) {
			return removeFirst();
		}
		else {
			//System.out.println(")
			return removeAfter(getNode(index-1));
		}
	}
	
}
