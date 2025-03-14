package hw4;

public class Q3 {
	/*
	 * helper function find to index and extract to number arr to subArray
	 */
	public static int[] a3(int [] arr,int sum) {
		int [] range = {0,0};
		range = a3helper(sum,0, arr,range);
		int [] subArray = new int[range[1]-range[0]+1];
		int i=0;
		//Extract array
		for(i=0; range[0] <= range[1];range[0]++,i++) {
			subArray[i] = arr[range[0]];
		}
		return subArray;
	}
	/*
	 * Trying to equate to zero by subtracting numbers from sum
	 * range put subArray index
	 */
	private static int[] a3helper(int sum,int index, int [] arr,int [] range) { //
		
		if(sum < 0) { // if sum is smaller than zero, range zero move to one index and sum add range[0] index value
			sum = sum + arr[range[0]];
			range[0] = range[0] +1;
			return a3helper(sum,index,arr,range);
		}
		else if(sum == 0) { // finish recursive return range
			if(index==0) {
				range[1] =0;
			}
			range[1] = index-1;
			return range;
			
		}
		else if(index == arr.length) { // finish recursive
			range[0] = 0;
			range[1] = 0;
			return range;
		}
		else { // go on the recursive
			if(index == 0) {
				range[0] = 0;
			}
			sum = sum - arr[index];
			return a3helper(sum,index+1,arr,range);
		}
	}
}
