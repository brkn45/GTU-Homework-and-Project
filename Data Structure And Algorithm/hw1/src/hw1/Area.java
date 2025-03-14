package hw1;

/**
 * Same function implement this abstract class
 */
public abstract class Area implements Building {
	private int lenght;
	private int buildingType;
	private int startArea, endArea;
	private int side,height;
	String name; //every Building has name. 
	
	/**
	 * Every Building has lenght and height. Playground every time 0 by default value zero
	 * @param lenght
	 * @param height
	 * 
	 */
	Area(int lenght,int height){
		this.lenght = lenght;
		this.height = height;
	}
	public int getLenght() {
		return lenght;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	public int getSide() {
		return side;
	}

	public void setSide(int side) {
		this.side = side;
	}

	public int getStartArea() {
		return startArea;
	}
	
	/**
	 *@param startArea
	 *Every buildings has start and end value, 
	 */
	public void setStartArea(int startArea) {
		this.startArea = startArea;
	}

	public int getEndArea() {
		return endArea;
	}
	/**
	 * Every buildings has start and end value, 
	 *@param endArea
	 *
	 */
	public void setEndArea(int endArea) {
		this.endArea = endArea;
	}

	@Override
	public int getLength() {
		return lenght;
	}
	
	@Override
	public void setLenght(int lenght) {
		this.lenght = lenght;
	}

	@Override
	public void setBuildingType(int type) {
		if(type > 4) { // enum has 4 element 
			this.buildingType = type;
		}
		
		
	}

	@Override
	public int BuildingType() {
		return this.buildingType;
	}
	@Override
	public int getHeight() {
		return height;
	}
	
	public void setHeight(int height) {
		this.height = height;
	}
	

}
