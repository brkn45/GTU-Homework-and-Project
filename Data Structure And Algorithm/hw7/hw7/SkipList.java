package hw7;

import java.util.Random;

/* Class SkipList */
class SkipList<E extends Comparable>
{
	SLNode<E> head;
	private int maxLevel =2;
	static final double LOG2 = Math.log(2.0);
	private int size =0;
   static class SLNode<E extends Comparable>{
	   SLNode<E>[] links;
	   E data;
   
   /** create a node of level m*/
    SLNode(int m,E data){
	   links = (SLNode<E> []) new SLNode[m];
	   this.data = data;
   }
   
}
   /**
    * helper function 
    * @param target
    * @return
    */
   private SLNode<E>[] search(E target){
	   SLNode<E>[] pred = (SLNode<E>[]) new SLNode[maxLevel];
	   SLNode<E> current = head;
	   for(int i = current.links.length -1;i>=0; i--) {
		   while(current.links[i] != null
			   && current.links[i].data.compareTo(target) < 0){
				   current = current.links[i];
			   }
		   
		   pred[i] = current;
	   }
	   return pred;
   }
   public int getMaxLevel() 
   {
	   return maxLevel;
   }
   public E find(E target) {
	   SLNode<E> [] pred = search(target);
	   if(pred[0].links[0].data.compareTo(target) ==0) {
		   return pred[0].links[0].data;
	   }
	   else {
		   return null;
	   }
   }
   /**
    * Main function for insert
    * @param item
    */
   public void insert(E item) {
	   if(head== null) {
		   head = new  SLNode(2,item);
		   head.links[0] = null;
		   
	   }
	   else {
		   add(item);
	   }
	   size++;
	   if(size > (maxLevel-1)*10) {
		   maxLevel++;
		   increaseLevel();
		   connect();
	   }
   }
   /**
    * if item size bigger than multiple of maxlevel then increase maxLevel. Node has most level in skipList then
    * increase one level
    */
   private void increaseLevel() {
	   SLNode<E> iter = head;
	   SLNode<E> tmpIter;
	   int tmpLevel =0;
	   while(iter != null) {
		   if(iter.links.length > tmpLevel) {
			   tmpLevel = iter.links.length;
		   }
		   iter = iter.links[0];
	   }
	   iter = head;
	   while(iter.links[0] != null) {
		   if(iter.links[0].links.length == tmpLevel) {
			   tmpIter = iter.links[0];
			   iter.links[0] = new SLNode(tmpLevel+1,iter.links[0].data);
			   
				   iter.links[0].links[0] =  tmpIter.links[0];   
		   }
		   iter =iter.links[0];
	   }
   }
   /**
    * Helper function for insert method
    * @param item
    */
   private void add(E item) {
	   int lenght;
	   int level; // temp value
	   SLNode<E> iter = head;
	   SLNode<E> lastItem = null;
	   boolean flag = false;
	   if(head.data.compareTo(item) > 0) { // add front
		   level = getLevel(8);
		   SLNode<E> tmp = new SLNode(level,item); 
		   tmp.links[0] = head;
		   this.head = tmp;
		   flag = true;
		   connect();
	   }
	   while(iter != null) { // add between 2 node
		   lastItem = iter;
		   if(iter.data.compareTo(item) <0 && iter.links[0] != null) {
			   
			   if(iter.links[0].data.compareTo(item) >0) {
				   lenght = findLenght(iter);
				   level = getLevel(lenght);
				   SLNode<E> tmp = new SLNode(level,item);
				   tmp.links[0] = iter.links[0];
				   iter.links[0] = tmp;
				   connect();
				   flag = true;
				   break;
			   }
		   }
		   iter = iter.links[0];
	   }
	   if(lastItem != null && flag == false) { // add end of node
		   lenght = findLenght(lastItem);
		   level = getLevel(lenght);
		   SLNode<E> tmp = new SLNode(level,item);
		   tmp.links[0] = null;
		   lastItem.links[0] = tmp;
	   }
	   
   }
   /**
    * Calculate between  most big Level how many node then return it
    * @param iter
    * @return
    */
   private int findLenght(SLNode<E> iter) {
	   SLNode<E> priv = head;
	   SLNode<E> next = iter.links[0];
	   int height =0;
	   int countPriv=0,countNext =0;
	   while(priv != iter) {
	   		if(height <= priv.links.length) {
	   			height = priv.links.length;
	   			countPriv =0;
	   			priv = priv.links[0];
	   		}
	   		else {
	   			countPriv++;
	   			priv = priv.links[0];
	   		}
	   }
	   height =0;
	   while(next != null) {
		   if(height <= next.links.length) {
	   			height = next.links.length;
	   			countNext =0;
	   			next = next.links[0];
	   		}
	   		else {
	   			countNext++;
	   			next = next.links[0];
	   		}
	   }
	   return countPriv + countNext;
   }
   /*
    * Connect 2 and bigger level node
    */
   private void connect() {
	   SLNode<E> iter = head;
	   SLNode<E> priv = head;
	   int level =1;
	   
	   while(priv.links.length <=level && iter != null) {
		   priv =priv.links[0];
		   iter = iter.links[0];
	   }
	   iter = iter.links[0];
	   while(level<= maxLevel) {
		   while(iter != null) {
			   
			   if(priv.links.length > level && iter.links.length >level ) {
				   priv.links[level] = iter;
				   priv = iter;
				   
			   }
			   
			   iter = iter.links[0];
		   }
		   level++;
		   
		   priv = head;
		   iter = head.links[0];
		   while(priv.links.length <=level && iter != null) {
			   priv =priv.links[0];
			   iter = iter.links[0];
		   }
	   }
	   
   }
   /**
    * calculate node level with given probability formula
    * @param lenght
    * @return
    */
   public int getLevel(int lenght) {
	   int [] arr = new int[(maxLevel-1)*10];
	   int i =0;
	   for(i=0;i<arr.length;i++) {
		   if(i<lenght)
			   arr[i] =1;
		   else
			   arr[i] =0;
	   }
	   rand(arr,arr.length);
	   Random rd = new Random();
	   	i=0;
	   int level=0;
	   while(i<maxLevel) {
		   level = level + arr[Math.abs(rd.nextInt())%arr.length];
		   i++;
	   }
	   if(level == 0) {
		   return level+1;
	   }
	   else {
		   return level;
	   }
   }
   /**
    * shuffle array for probability
    * @param array
    * @param a
    */
   private void rand( int array[], int a)
   {
       // Creating object for Random class
       Random rd = new Random();
        
       // Starting from the last element and swapping one by one.
       for (int i = a-1; i > 0; i--) {
            
           // Pick a random index from 0 to i
           int j = rd.nextInt(i+1);
            
           // Swap array[i] with the element at random index
           int temp = array[i];
           array[i] = array[j];
           array[j] = temp;
       }
   }
   /**
    * Print all node
    */
   public void print() {
	   SLNode<E> tmp = head;
	   int i=0;
	   while(tmp != null) {
		   System.out.print("data: " + tmp.data);
		   System.out.println("  lenght: " + tmp.links.length);
		   tmp= tmp.links[0];
	   }
	   
   }
   /**
    * printLevel 2 connected node
    */
   public void printLevel2() {
	   SLNode<E> tmp = head;
	   int i=0;
	   while(tmp.links.length <=1 && tmp != null) {
		   tmp =tmp.links[0];
		   
	   }
	   while(tmp != null) {
		   System.out.print("data: " + tmp.data);
		   System.out.println("  lenght: " + tmp.links.length);
		   if(tmp.links.length > 1) {
			   tmp= tmp.links[1];
		   }
		   
		   
	   }
	   
   }
   /**
    * printLevel 3 connected node
    */
   public void printLevel3() {
	   SLNode<E> tmp = head;
	   int i=0;
	   while(tmp.links.length <=2 && tmp != null) {
		   tmp =tmp.links[0];
		   
	   }
	   while(tmp != null) {
		   System.out.print("data: " + tmp.data);
		   System.out.println("  lenght: " + tmp.links.length);
		   if(tmp.links.length > 2) {
			   tmp= tmp.links[2];
		   }
		   
		   
	   }
	   
   }
   /**
    * printLevel 4 connected node
    */
   public void printLevel4() {
	   SLNode<E> tmp = head;
	   int i=0;
	   while(tmp.links.length <=3 && tmp != null) {
		   tmp =tmp.links[0];
		   
	   }
	   while(tmp != null) {
		   System.out.print("data: " + tmp.data);
		   System.out.println("  lenght: " + tmp.links.length);
		   if(tmp.links.length > 3) {
			   tmp= tmp.links[3];
		   }
		   
		   
	   }
	   
   }
} 
/* Class SkipListTest */
   
  
   
