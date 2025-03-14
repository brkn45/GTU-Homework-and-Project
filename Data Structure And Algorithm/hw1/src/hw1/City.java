package hw1;

/**
 * City class instance create street in constructer. Constructer dont need any parameter
 * @author berkan
 * 
 */
public class City {
	private Street street;
	private int streetCount;
	
	
	public City() {
		super();
		this.street = new Street(100);
		this.streetCount =0;
	}

	/**
	 * @return
	 */
	public Street getStreet() {
		return street;
	}

	/**
	 * @param street
	 */
	public void setStreet(Street street) {
		this.street = street;
	}
	
	
	

	

	
	
	
}
