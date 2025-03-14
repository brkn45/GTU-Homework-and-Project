package hw4;

public class Main {

	public static void main(String[] args) {
		int i=0;
		//Question 1
		int x = Q1.searchSub("araba","marabamarabamaraba",2);
        System.out.println("Result: " + x +" "+ "marabamaraba".substring("marabamaraba".indexOf("araba")+1));

        x = Q1.searchSub("araba","gaeg",1);
        System.out.println("Result: " + x);

        x = Q1.searchSub("araba","araba",2);
        System.out.println("Result: " + x);

        x = Q1.searchSub("araba","arabamarabakaraba",3);
        System.out.println("Result: " + x);

        x = Q1.searchSub("araba","arabamarabakaraba",1);
        System.out.println("Result: " + x);
		
        //Question 2
        System.out.println("Question 2");
		int count;
		int [] arr = {1,3,5,7,9,11,13,17}; // array size 8
		System.out.println("Test1 between indexes");	
		count = Q2.a2(arr,10,15);
		System.out.println("count: " + count);
		System.out.println("Test2 between out of indexes");
		count = Q2.a2(arr,-1,18);
		System.out.println("count: " + count);
		System.out.println("Test3 between  indexes");
		count = Q2.a2(arr,5,11);
		System.out.println("count: " + count);
		//Question 3
		
		
		System.out.println("\nQuestion 3");
		System.out.println("Test 1");
		
		int [] subArray = Q3.a3( arr,27);  // 7 ,9 ,11 the above array
		System.out.println("SubArray");
		for(i=0;i<subArray.length;i++) {
			System.out.print(subArray[i]+" ");
		}
		System.out.println("\nTest 2");
		
		 subArray = Q3.a3( arr,30);  // 13 17 the above array
		System.out.println("SubArray");
		for(i=0;i<subArray.length;i++) {
			System.out.print(subArray[i]+" ");
		}
		
		System.out.println("\n\nQuestion 5");
		int [] range = {0,2};
		int [] arr2 = new int[7];
		Q5.a5(arr2,range,true);
		
	}

}
