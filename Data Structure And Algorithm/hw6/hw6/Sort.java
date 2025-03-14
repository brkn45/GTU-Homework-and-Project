package hw6;

public class Sort {
	void merge(int Arr[], int start, int mid, int end) {

		// create a temp array
		int temp[] = new int[end - start + 1];

		// crawlers for both intervals and for temp
		int i = start, j = mid+1, k = 0;

		// traverse both arrays and in each iteration add smaller of both elements in temp 
		while(i <= mid && j <= end) {
			if(Arr[i] <= Arr[j]) {
				temp[k] = Arr[i];
				k += 1; i += 1;
			}
			else {
				temp[k] = Arr[j];
				k += 1; j += 1;
			}
		}

		// add elements left in the first interval 
		while(i <= mid) {
			temp[k] = Arr[i];
			k += 1; i += 1;
		}

		// add elements left in the second interval 
		while(j <= end) {
			temp[k] = Arr[j];
			k += 1; j += 1;
		}

		// copy temp to original interval
		for(i = start; i <= end; i += 1) {
			Arr[i] = temp[i - start];
		}
	}

	// Arr is an array of integer type
	// start and end are the starting and ending index of current interval of Arr

	void mergeSort(int Arr[], int start, int end) {

		if(start < end) {
			int mid = (start + end) / 2;
			mergeSort(Arr, start, mid);
			mergeSort(Arr, mid+1, end);
			merge(Arr, start, mid, end);
		}
	}
	void quickSort(int[] arr, int low, int high)
	{
	    if (low < high)
	    {
	         
	        // pi is partitioning index, arr[p]
	        // is now at right place
	        int pi = partition(arr, low, high);
	 
	        // Separately sort elements before
	        // partition and after partition
	        quickSort(arr, low, pi - 1);
	        quickSort(arr, pi + 1, high);
	    }
	}
	
	int partition(int[] arr, int low, int high)
	{
	     
	    // pivot
	    int pivot = arr[high];
	     
	    // Index of smaller element and
	    // indicates the right position
	    // of pivot found so far
	    int i = (low - 1);
	 
	    for(int j = low; j <= high - 1; j++)
	    {
	         
	        // If current element is smaller
	        // than the pivot
	        if (arr[j] < pivot)
	        {
	             
	            // Increment index of
	            // smaller element
	            i++;
	            swap(arr, i, j);
	        }
	    }
	    swap(arr, i + 1, high);
	    return (i + 1);
	}
	
	void swap(int[] arr, int i, int j)
	{
	    int temp = arr[i];
	    arr[i] = arr[j];
	    arr[j] = temp;
	}
}
