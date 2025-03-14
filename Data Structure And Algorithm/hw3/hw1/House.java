package hw1;
/**
 * House class need lenght,height,roomnumber,color,owner value
 * @author Berkan
 *
 */
public class House extends PrivateArea {
	private int roomNumber;
	private String color;
	private String owner;
	/**
	 * @param lenght
	 * @param height
	 * @param roomNumber
	 * @param color
	 * @param owner
	 */
	public House(int lenght,int height,int roomNumber, String color, String owner) {
		super(lenght,height);
		this.roomNumber = roomNumber;
		this.color = color;
		this.owner = owner;
		setName(owner);
	}
	
	/**
	 * @return
	 */
	public int getRoomNumber() {
		return roomNumber;
	}
	/**
	 * @param roomNumber
	 */
	public void setRoomNumber(int roomNumber) {
		this.roomNumber = roomNumber;
	}
	/**
	 * @return
	 */
	public String getColor() {
		return color;
	}
	/**
	 * @param color
	 */
	public void setColor(String color) {
		this.color = color;
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
}
