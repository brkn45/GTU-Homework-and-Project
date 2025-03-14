package hw1;

/**
 * City class instance create street in constructer. Constructer dont need any parameter
 * @author berkan
 * 
 */
public class City {
	private Street street;
	private int streetCount;
	
	
	public City(Street street) {
		super();
		this.street = street;
		this.streetCount =0;
	}

	/**
	 * @return
	 */
	public Street getStreet() {
		return street;
	}
	
	/**
	 * @param streetArray
	 */
	public void setStreet(Street street) {
		this.street = street;
	}
	
	
	

	

	
	
	
}
