package hw1;

/**
 * All buildings require these functions.
 * @author berkan
 * 
 */

public interface Building {
	
	public int getLength(); 
	public void setLenght(int lenght);
	//public int getWidth();
	public String getName();
	
	public void setName(String name);
	public void setBuildingType(int type);
	public int BuildingType();
	public int getSide();
	public void setSide(int side);
	public int getStartArea();
	public void setStartArea(int startArea);
	public int getEndArea();
	
	public void setEndArea(int endArea);
	
	public int getHeight();
	
	
}
