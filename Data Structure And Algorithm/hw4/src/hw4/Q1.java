package hw4;

public class Q1 {
	
	public static int searchSub(String small,String big,int index){
        return searchSub(small,big,index,0);
    }
	
	private static int searchSub(String small,String big,int index,int n){ // Search again after index and return index
        
        if(big.length()<small.length()){            
            return -1;
        }

        else if( big.indexOf(small) != -1 && index-- == 1){
            return n;
        }

        else
            return searchSub(small,big.substring(big.indexOf(small)+1),index,n+big.indexOf(small)+1);
    }

    
}
