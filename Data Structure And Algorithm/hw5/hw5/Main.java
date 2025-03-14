package hw5;

public class Main {

	public static void main(String[] args) {
		BinaryHeap minHeap = new BinaryHeap(15);
        BinaryHeap minHeap2 = new BinaryHeap(15);
        
        minHeap.insert(17);
        minHeap.insert(10);
        minHeap.insert(84);
        minHeap.insert(19);
        minHeap.insert(6);
        minHeap.insert(3);
        minHeap.insert(22);
        minHeap.insert(9);
        minHeap.insert(5);
        minHeap.minHeap();
       
        minHeap.inOrder(minHeap.getRoot());
        System.out.println("\nTree Representation");
        System.out.println(minHeap.toString());
       System.out.println("\nRemove min element");
        minHeap.removet();
        minHeap.minHeap();
       minHeap.inOrder(minHeap.getRoot());
       System.out.println("\ndata:" +minHeap.getRoot().data);
       System.out.println("data right:" +minHeap.getRoot().right.data);
       System.out.println("data left:" +minHeap.getRoot().left.data);
       
       
       minHeap2.insert(15);
       minHeap2.insert(25);
       minHeap2.insert(35);
       minHeap2.insert(2);
       minHeap2.insert(55);
       minHeap2.insert(7);
       minHeap2.minHeap();
       
       minHeap.heapMerge(minHeap, minHeap2);
       minHeap.minHeap();
       System.out.println("After Merger");
       minHeap.inOrder(minHeap.getRoot());
       
       System.out.println("\ndata root:" +minHeap.getRoot().data);
       System.out.println("data right:" +minHeap.getRoot().right.data);
       System.out.println("data left:" +minHeap.getRoot().left.data);
       System.out.println(minHeap.toString());
       System.out.println("\nRemove min element");
       minHeap.removet();
       minHeap.minHeap();
       minHeap.inOrder(minHeap.getRoot());
       System.out.println("\ndata:" +minHeap.getRoot().data);
       System.out.println("data right:" +minHeap.getRoot().right.data);
       System.out.println("data left:" +minHeap.getRoot().left.data);
       
       
       System.out.println(minHeap.toString());
		
       
       System.out.println("Array Binary Tree Test");
		ArrayTree arrayTree = new ArrayTree();
		
		arrayTree.add(30);
		arrayTree.add(20);
		arrayTree.add(50);
		arrayTree.add(10);
		arrayTree.add(15);
		arrayTree.add(80);
		arrayTree.add(25);
		arrayTree.add(70);
		arrayTree.add(90);
		arrayTree.add(60);
		System.out.println("Print in Order");
		arrayTree.inOrder();
		
		System.out.println("\n\nContains Methot Test");
		System.out.println("Contains 50: " + arrayTree.contains(50));
		System.out.println("Contains 100: " + arrayTree.contains(100));
		
		System.out.println("\nFind Method Test");
		
		System.out.println("Find 80: " + arrayTree.find(80));
		System.out.println("Find 100: " + arrayTree.find(100));
		
		
	}

}
