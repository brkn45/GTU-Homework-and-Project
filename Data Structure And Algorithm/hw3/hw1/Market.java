package hw1;
/**
 * Market class need owner start and end time, lenght, height value
 * @author berkan
 *
 */
public class Market extends PrivateArea {
	private String owner;
	private final int startHours;
	private final int startMinute;
	private final int endHours, endMinute;
	/**
	 * Start and End time take int value
	 * @param owner
	 * @param startHours
	 * @param startMinute
	 * @param endHours
	 * @param endMinute
	 * @throws Exception 
	 * 
	 */
	public Market( int lenght,int height,int startHours, int startMinute, int endHours, int endMinute, String owner) throws Exception {
		super(lenght,height);
		if(startHours  > -1 && startHours < 24 && startMinute > -1 && startMinute < 60 && endHours > -1 && endHours < 24 && endMinute > -1 && endMinute < 60) {
			this.owner = owner;
			setName(owner);
			this.startHours = startHours;
			this.startMinute = startMinute;
			this.endHours = endHours;
			this.endMinute = endMinute;
		}
		else {
			throw new Exception("Input Value of Wrong");
		}
		
	}
	/**
	 *
	 */
	public String getOwner() {
		return owner;
	}
	/**
	 *
	 */
	public void setOwner(String owner) {
		this.owner = owner;
	}
	/**
	 * @return
	 */
	public int getStartHours() {
		return startHours;
	}
	/**
	 * @return
	 */
	public int getStartMinute() {
		return startMinute;
	}
	/**
	 * @return
	 */
	public int getEndHours() {
		return endHours;
	}
	/**
	 * @return
	 */
	public int getEndMinute() {
		return endMinute;
	}
	/**
	 * @return
	 */
	/**
	 * @return
	 */
	public String  closingTime() {
		return Integer.toString(endHours) + ":" +Integer.toString(endMinute);
	}
	/**
	 * @return
	 */
	public String openTime() {
		return Integer.toString(startHours) + ":" +Integer.toString(startMinute);
	}
	/**
	 * 
	 */
	public void printHours() {
		System.out.println("Open time: " + openTime() + "  Closing Time: " + closingTime());
	}
	
	
}
