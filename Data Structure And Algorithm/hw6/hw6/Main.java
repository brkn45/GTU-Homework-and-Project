package hw6;

import java.util.Random;

public class Main {

	public static void main(String[] args) {
		int i=0;
		BinarySearchTree<String,Integer> bst = new BinarySearchTree(); 
         /*BST tree example
              45 
           /     \ 
          10      90 
         /  \    /   
        7   12  50   */
        //insert data into BST
       bst.insert("kirk5",45); 
        bst.insert("on",10); 
        bst.insert("yedi",7); 
        bst.insert("oniki",12); 
        bst.insert("doksan",90); 
        bst.insert("elli",50); 
        //print the BST
        System.out.println("The BST Created with input data(Left-root-right):"); 
        bst.inorder(); 
        
        //delete leaf node  
        System.out.println("\nThe BST after Delete 12(leaf node):"); 
        bst.deleteKey("oniki"); 
        bst.inorder(); 
        //delete the node with one child
        System.out.println("\nThe BST after Delete 90 (node with 1 child):"); 
        bst.deleteKey("doksan"); 
        bst.inorder(); 
                 
        //delete node with two children  
        System.out.println("\nThe BST after Delete 45 (Node with two children):"); 
        bst.deleteKey("kirk5"); 
        bst.inorder(); 
        //search a key in the BST
        Integer ret_val = bst.search ("elli").getValue();
        System.out.println("\nKey 50 found in BST:" + ret_val );
        ret_val = bst.search ("oniki").getValue();
        System.out.println("\nKey 12 found in BST:" + ret_val );

        BSTHashMap<String,Integer> bstHash = new BSTHashMap();
        BSTHashMap<Integer,Integer> bstHash2 = new BSTHashMap();
        BSTHashMap<Integer,Integer> bstHash1000 = new BSTHashMap();
        BSTHashMap<Integer,Integer> bstHash100000 = new BSTHashMap();
        bstHash.put("berkan", 10);
        bstHash.put("akin", 20);
        bstHash.put("elif", 30);
        bstHash.put("ahmet", 50);
        bstHash.put("hatice", 60);
        bstHash.put("yusuf", 70);
        bstHash.put("ali", 80);
        bstHash.put("ismail", 90);
        bstHash.put("ibrahim", 100);
        
        System.out.println("ne oluyor:"+ bstHash.get("akin"));
        bstHash.printTable();
        
        System.out.println("\n100 item test");
        for(i=0;i<100;i++) {
        	bstHash2.put(i, i);
        }
        bstHash2.printTable();
        
        System.out.println("\n1000 item test");
        for(i=0;i<1000;i++) {
        	bstHash1000.put(i, i);
        }
        bstHash1000.printTable();
        
        System.out.println("\n100 000 item test");
        for(i=0;i<100000;i++) {
        	bstHash100000.put(i, i);
        }
        bstHash100000.printTable();
		
		DoubleHash<Integer,Integer> dh = new DoubleHash();
		System.out.println("result: " + dh.primeNumber( (int) Math.round(21.0*0.8)));
		dh.put(3, 3);
		dh.put(12,12);
		dh.put(13, 13);
		dh.put(25, 25);
		dh.put(23, 23);
		dh.put(51, 51);
		dh.printTable();
		System.out.println("Get function Test");
		DoubleHash<Integer,String> dh2 = new DoubleHash();
		dh2.put(20,"honda");
		dh2.put(32,"toyota");
		dh2.put(40,"subaru");
		dh2.put(55,"isuzu");
		dh2.put(22,"acura");
		dh2.put(35, "lexus");
		dh2.put(16, "mazda");
		dh2.put(37, "suziki");
		dh2.put(25, "nissan");
		dh2.put(45, "mitsubishi");
		dh2.printTable();
		System.out.println("key:40" +" Value: " +dh2.get(40));
		System.out.println("key:22" +" Value: " +dh2.get(22));
		System.out.println("Remove function Test");
		dh2.remove(16);
		dh2.remove(22);
		
		dh2.printTable();
		System.out.println("After Remove function Add Element");
		dh2.put(16, "mazda");
		dh2.put(22,"acura");
		dh2.printTable();
		
		System.out.println("Small Test");
		DoubleHash<Integer,Integer> dh100 = new DoubleHash();
		for(i=0;i<100;i++) {
			dh100.put(i,i );
		}
		dh100.printTable();
		System.out.println("Medium Test");
		DoubleHash<Integer,Integer> dh1000 = new DoubleHash();
		for(i=0;i<1000;i++) {
			dh1000.put(i,i );
		}
		dh1000.printTable();
		
		System.out.println("Large Test");
		DoubleHash<Integer,Integer> dh10000 = new DoubleHash();
		for(i=0;i<10000;i++) {
			dh10000.put(i,i );
		}
		dh10000.printTable();
		System.out.println("Medium Test");
		
		Random random = new Random();
		Sort sort = new Sort();
		long startTime,endTime,time;
		final int size1 =100; 
		int[] arraySmall = new int[100];
		for(i=0;i<arraySmall.length;i++) {
			arraySmall[i] = random.nextInt();
		}
		startTime = System.nanoTime();
		sort.mergeSort(arraySmall, 0,99 );
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println("Small Time: " + time);
		
		for(i=0;i<arraySmall.length;i++) {
			System.out.println("i: " + i+ "array: " + arraySmall[i]);
		}
		
		System.out.println("Merge Sort Medium Test");
		
		int[] arrayMedium = new int[1000];
		for(i=0;i<arrayMedium.length;i++) {
			arrayMedium[i] = random.nextInt();
		}
		startTime = System.nanoTime();
		sort.mergeSort(arrayMedium, 0,999);
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println("Medium Time: " + time);
		
		for(i=0;i<arrayMedium.length;i++) {
			System.out.println("i: " + i+ " array: " + arrayMedium[i]);
		}
		
		System.out.println("Merge Sort Large Test");
		
		int[] arrayLarge = new int[10000];
		for(i=0;i<arrayLarge.length;i++) {
			arrayLarge[i] = random.nextInt();
		}
		startTime = System.nanoTime();
		sort.mergeSort(arrayLarge, 0,9999 );
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println("Large Time: " + time);
		for(i=0;i<arrayLarge.length;i++) {
			System.out.println("i: " + i+ " array: " + arrayLarge[i]);
		}
		
		System.out.println("Quick Sort Small Test");
		
		for(i=0;i<arraySmall.length;i++) {
			arraySmall[i] = random.nextInt();
		}
		startTime = System.nanoTime();
		sort.quickSort(arraySmall, 0, 99);
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println("Large Time: " + time);
		for(i=0;i<arrayLarge.length;i++) {
			System.out.println("i: " + i+ " array: " + arraySmall[i]);
		}
		
		System.out.println("Quick Sort Medium Test");
		
		for(i=0;i<arrayMedium.length;i++) {
			arrayMedium[i] = random.nextInt();
		}
		startTime = System.nanoTime();
		sort.quickSort(arrayMedium, 0, 999);
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println("Medium Time: " + time);
		for(i=0;i<arrayLarge.length;i++) {
			System.out.println("i: " + i+ " array: " + arrayMedium[i]);
		}
		
		System.out.println("Quick Sort Large Test");
		
		for(i=0;i<arrayLarge.length;i++) {
			arrayLarge[i] = random.nextInt();
		}
		startTime = System.nanoTime();
		sort.quickSort(arrayLarge, 0, 999);
		endTime = System.nanoTime();
		time = endTime - startTime;
		System.out.println("Medium Time: " + time);
		for(i=0;i<arrayLarge.length;i++) {
			System.out.println("i: " + i+ " array: " + arrayLarge[i]);
		}
	}
	

}
