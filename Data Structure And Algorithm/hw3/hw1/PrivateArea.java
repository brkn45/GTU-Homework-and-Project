package hw1;
/**
 * This class is made for privately owned areas
 */
public abstract class PrivateArea extends Area{
	private String owner;
	
	/**
	 * @return
	 */
	public String getOwner() {
		return owner;
	}
	/**
	 * @param lenght
	 * @param height
	 */
	public PrivateArea(int lenght,int height) {
		super(lenght,height);
		
	}
	/**
	 * @param owner
	 */
	public void setOwner(String owner) {
		this.owner = owner;
	}
	
	
	
}
