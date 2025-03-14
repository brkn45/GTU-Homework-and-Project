package hw1;

/**
 * It is made for different data types in Street class.
 * @author berkan
 *
 */
public interface Street {
	public void addBuildingSide1(Building building,int position);
	public void addBuildingSide2(Building building,int position);
	public void printBuildings();
	public void deleteBuildings(String name);
	public int getRemainder();
	public int getBuildingCountSide1();
	public int getBuildingCountSide2();
	public Building  getBuildingS1(int index);
	public Building  getBuildingS2(int index);
	public int getLenght();
}
