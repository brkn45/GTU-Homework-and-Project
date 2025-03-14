package hw1;
/**
 * Office Class Need lenght,height, jobType,owner for instance
 * @author berkan
 *
 */
public class Office extends PrivateArea {
	private String jopType;
	private String owner;
	
	
	
	/**
	 * Need lenght,height, jobType,owner
	 * @param lenght
	 * @param height
	 * @param jopType
	 * @param owner
	 */
	public Office(int lenght,int height,String jopType, String owner) {
		super(lenght,height);
		this.jopType = jopType;
		this.owner = owner;
		setName(owner);
	}
	
	/**
	 * @return
	 */
	public String getJopType() {
		return jopType;
	}
	/**
	 * @param jopType
	 */
	public void setJopType(String jopType) {
		this.jopType = jopType;
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
