package hw1;
/**
 * ViewMode Class do
 * Display the total remaining length of lands on the street.
 * Display the list of buildings on the street
 * display the number and ratio of lenth of playgrounds in the street.
 * calculate the total length of street occupied by the markets, houses or offices.
 * @author berkan
 *
 */
public class ViewMode implements Mode {
	private City city;
	private int playgroundCount;
	/**
	 * @param city
	 */
	public ViewMode(City city) {
		super();
		this.city = city;
		this.playgroundCount =0;
	}
	
	public void printListofStreet() {
		city.getStreet().printBuildings();
	}
	public void printRemaingLenght() {
		System.out.println("Total Remaining Length: " +city.getStreet().getRemainder());
	}
	public void printRatioOfPlayground() {
		
		System.out.println( " Ratio of Playground: " + ratioOfPlayground() + " Number of Playground: " + playgroundCount);
	}
	private double ratioOfPlayground() {
		int i=0,sum=0;
		
		for(i=0; i<city.getStreet().getBuildingCountSide1();i++) {
			if(city.getStreet().getBuildingSide1()[i] instanceof Playground) {
				sum = sum + city.getStreet().getBuildingSide1()[i].getLength();
				playgroundCount++;
				
			}
		}
		for(i=0; i<city.getStreet().getBuildingCountSide2();i++) {
			if(city.getStreet().getBuildingSide2()[i] instanceof Playground) {
				sum = sum + city.getStreet().getBuildingSide2()[i].getLength();
				playgroundCount++;
			}
		}
		
		return ((double) sum)/(double)(2*city.getStreet().getLenght());
	}
	private int streetAccupied() {
		int i=0,sum=0;
		for(i=0;i < city.getStreet().getBuildingCountSide1();i++) {
			
			if(city.getStreet().getBuildingSide1()[i] instanceof House || city.getStreet().getBuildingSide1()[i] instanceof Market
						|| city.getStreet().getBuildingSide1()[i] instanceof Office) {
				
				sum = sum + city.getStreet().getBuildingSide1()[i].getLength();
				
			}
				
		}
		for(i=0;i<city.getStreet().getBuildingCountSide2();i++) {
			if(city.getStreet().getBuildingSide2()[i] instanceof House || city.getStreet().getBuildingSide2()[i] instanceof Market
					|| city.getStreet().getBuildingSide2()[i] instanceof Office) {
			sum = sum + city.getStreet().getBuildingSide2()[i].getLength();
			
		}
	}
		return sum;
	}
	public void printStreetAccupied() {
		System.out.println("Street Accupied: " + streetAccupied());
	}
	public void printSilhouette() {
		int i=0,k=0;
		int [] arr1 = new int[city.getStreet().getLenght()]; int [] arr3 = new int[city.getStreet().getLenght()];
		int [] arr2 = new int[city.getStreet().getLenght()];
		for(i=0;i < city.getStreet().getBuildingCountSide1();i++) {
			for(k=city.getStreet().getBuildingSide1()[i].getStartArea();k<city.getStreet().getBuildingSide1()[i].getEndArea();k++) {
				arr1[k] = city.getStreet().getBuildingSide1()[i].getHeight();
				
			}
		}
		for(i=0;i < city.getStreet().getBuildingCountSide2();i++) {
			for(k=city.getStreet().getBuildingSide2()[i].getStartArea();k<city.getStreet().getBuildingSide2()[i].getEndArea();k++) {
				arr2[k] = city.getStreet().getBuildingSide2()[i].getHeight();
			}
		}
	
		for(i=0;i<city.getStreet().getLenght();i++) {
			if(arr1[i] > arr2[i]) {
				arr3[i] = arr1[i];
			}
			else {
				arr3[i] = arr2[i];
			}
		}
		int mostBig=0,index =i;
		for(i=0;i<city.getStreet().getLenght()-1;i++) {
			if(arr3[i] < arr3[i+1]) {
				mostBig =arr3[i+1];
				
			}
		}
		int count =0;
		for(i=0;i<city.getStreet().getLenght();i++) {
			if(mostBig == arr3[i]) {
				
				System.out.print("-");
			}
		}
	}	
}
