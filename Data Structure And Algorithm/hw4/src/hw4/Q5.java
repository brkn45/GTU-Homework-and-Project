package hw4;
/*
 * 
 */
public class Q5 {
	/*
	 * 
	 */
	public static void a5(int[] arr ,int [] range,boolean line) {
		int i=0;
		if((range[1] - range[0] ) == arr.length-1) {
			
			print(arr,range,line);
			return;
		}
		else if(range[1] == (arr.length-1)) {
			
			print(arr,range,line);
			int tmp;
			tmp = range[1] - range[0];
			range[0] = 0;
			range[1] = tmp +range[0]+1;
			
			a5(arr,range,!line);
		}
		else {
			int k=0;
			
			print(arr,range,line);
			
			range[0] = range[0] +1;
			range[1] = range[1] +1;
			a5(arr,range,!line);
		}
	}
	
	private static void print(int [] arr,int [] range,boolean line) {
		int i=0;
		for(i=0;i<arr.length;i++) {
			if( range[0] <= i && i <= range[1]) {
				System.out.print("*");
				
			}
			else {
				System.out.print(".");
			}
			
		}
		if(line) {
			System.out.print("    ");
		}
		else {
			System.out.println("");
		}
	}
}
