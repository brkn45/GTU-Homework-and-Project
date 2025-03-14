package hw4;

public class Q2 {
	public static int a2(int [] arr,int first,int last) {
		return a2(arr,0, first,last,0,0);
	}
	/*
	 * @Param fisrt and @Param last for range
	 */
	private static int a2(int [] arr,int index,int first,int last,int fIndex,int sIndex) { 
		
		
		if(arr[index] == last) { //
			sIndex = index;
			return sIndex - fIndex-1;
		}
		else if(index == arr.length-1) { // finish recursive and return element count
			sIndex= arr.length-1;
			if(arr[index] < last) {
				return sIndex - fIndex;
			}
			
			return 0;
		}
		
		else if(arr[index] == first) { // find first element index
			return a2(arr,index+1,first,last,index,sIndex);
		}
		else if(arr[index] < first && first < arr[index+1]) { // if first element index is between two index
			return a2(arr,index+1,first,last,index,sIndex);
		}
		else if(arr[index] < last && last < arr[index+1]) { // if last(second) element index is between two index
			sIndex = index;
			return sIndex - fIndex;
		}
		else if(arr[0] > first) { // if fisrt elemten is out of index
			return a2(arr,index+1,first,last,-1,sIndex);
		}
		else {// go on to search
			return a2(arr,index+1,first,last,fIndex,sIndex);
		}
		
		
	}
}
