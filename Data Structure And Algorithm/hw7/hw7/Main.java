package hw7;

import hw7.BinaryTree.Node;

public class Main {

	public static void main(String[] args) {
		Q1 q1 = new Q1();
		
		
		System.out.println("Question #1 Test");
		BinarySearchTree bst = new BinarySearchTree();
		BinaryTree bt1 = new BinaryTree();
		
		bt1.root = new BinaryTree.Node<Integer>(0);
		bt1.root.left = new BinaryTree.Node<Integer>(0);
		bt1.root.left.left = new BinaryTree.Node<Integer>(0);
		bt1.root.left.left.left = new BinaryTree.Node<Integer>(0);
		
		bt1.root.right = new BinaryTree.Node<Integer>(0);
		bt1.root.right.right = new BinaryTree.Node<Integer>(0);
		bt1.root.right.right.left = new BinaryTree.Node<Integer>(0);
		
		
		Integer [] arr = {11,8,13,19,6,4,15};
		System.out.println("Test 1");
		
		bst =q1.transformation(arr, bt1);
		
		bst.print2D();
		
		BinaryTree bt = new BinaryTree();
		
		bt.root = new BinaryTree.Node<Integer>(0);
		bt.root.left = new BinaryTree.Node<Integer>(0);
		bt.root.left.left = new BinaryTree.Node<Integer>(0);
		bt.root.left.right = new BinaryTree.Node<Integer>(0);
		bt.root.left.right.right = new BinaryTree.Node<Integer>(0);
		bt.root.left.right.left = new BinaryTree.Node<Integer>(0);
		
		bt.root.right = new BinaryTree.Node<Integer>(0);
		bt.root.right.right = new BinaryTree.Node<Integer>(0);
		bt.root.right.right.left = new BinaryTree.Node<Integer>(0);
		BinarySearchTree bst2 = new BinarySearchTree();
		
		
		Integer []arr2 = {8,9,6,5,3,7,4,2,1};
		
		bst2 =q1.transformation(arr2, bt);
		
		System.out.println("Test 2");
		bst2.print2D();
		
		
		System.out.println("Question #2 Test");
		Q2 q2 = new Q2();

		BinarySearchTree<Integer> bst3 = new BinarySearchTree();
		bst3.add(42);
		bst3.add(35);
		bst3.add(31);
		bst3.add(19);
		bst3.add(27);
		bst3.add(14);
		bst3.add(10);
		System.out.println("First Case");
		bst3.print2D();
		
		bst3 = q2.transformation(bst3);
		
		System.out.println("\n\nResult");
		bst3.print2D();
		
		BinarySearchTree<Integer> bst4 = new BinarySearchTree();
		
		bst4.add(14);
		bst4.add(19);
		bst4.add(27);
		bst4.add(35);
		bst4.add(31);
		bst4.add(42);
		bst4.add(8);
		bst4.add(7);
		bst4.add(5);
		bst4.add(4);
		bst4.add(3);
		System.out.println("\n\n Before Transformation");
		bst4.print2D();
		System.out.println("\n\n Test2 Result");
		
		bst4 = q2.transformation(bst4);
		
		bst4.print2D();
		
		System.out.println("Question #3 SkipList Test");
		SkipList<Integer> tmp = new SkipList();
		System.out.println("Adding the first node");
		tmp.insert(50);
		tmp.print();
		
		System.out.println("Adding to the back");
		tmp.insert(40);
		tmp.print();
		
		
		System.out.println("Insertion of the node");
		tmp.insert(45);
		tmp.print();
		
		System.out.println("Adding at the end");
		tmp.insert(100);
		tmp.print();
		
		tmp.insert(30);
		tmp.insert(20);
		tmp.insert(10);
		tmp.insert(35);
		tmp.insert(25);
		tmp.insert(42);
		
		
		System.out.println("Leveling up test in multiples of 10");
		tmp.print();
		System.out.println("After adding the 11th element");
		tmp.insert(15);
		tmp.print();
		
		
		tmp.insert(28);
		tmp.insert(31);
		tmp.insert(42);
		tmp.insert(49);
		tmp.insert(19);
		tmp.insert(11);
		tmp.insert(9);
		tmp.insert(12);
		tmp.insert(13);
		tmp.insert(14);
		
		tmp.insert(16);
		tmp.insert(17);
		
		
		System.out.println("Insert run time analaysis");
		long time1 = System.nanoTime();
		tmp.insert(18);
		long time2 = System.nanoTime();
		System.out.println("Result time: " + (time2 - time1));
		
		
		System.out.println("Testing the connection between levels");
		System.out.println("Level 2 and Upper Item Test");
		tmp.printLevel2();
		
		System.out.println("Level 3 and Upper Item Test");
		tmp.printLevel3();
		
		System.out.println("Level 4 and Upper Item Test");
		tmp.printLevel4();
		
		System.out.println("All Item");
		tmp.print();
           
		
		
		
	}

}
