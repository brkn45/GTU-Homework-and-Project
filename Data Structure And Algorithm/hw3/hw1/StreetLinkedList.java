package hw1;

import java.util.LinkedList;
import java.util.LinkedList;

/**
 * Street class do add and remove building. Street has  2 pieces building  array. (side1 and side2)
 * Used to Simple array
 * @author berkan Simple LinkedList
 *
 */
public class StreetLinkedList implements Street{
	private int lenght;
	//private int startX, startY, endX, endY;
	private LinkedList<Building>  buildingSide1, buildingSide2;
	private int buildingCountSide1, buildingCountSide2;
	private int remainder;

	/**
	 * @param lenght
	 * 
	 */
	public StreetLinkedList(int lenght) {
		this.lenght = lenght;
		buildingSide1 = new LinkedList<Building>();
		buildingSide2 = new LinkedList<Building>();
		buildingCountSide1 =0;
		buildingCountSide2 =0;
		remainder = 2*lenght;
		
	}
	public int getRemainder() {
		return remainder;
	}


	public void setRemainder(int remainder) {
		this.remainder = remainder;
	}


	public int getBuildingCountSide1() {
		return buildingCountSide1;
	}


	public void setBuildingCountSide1(int buildingCountSide1) {
		this.buildingCountSide1 = buildingCountSide1;
	}


	public int getBuildingCountSide2() {
		return buildingCountSide2;
	}


	public void setBuildingCountSide2(int buildingCountSide2) {
		this.buildingCountSide2 = buildingCountSide2;
	}


	public LinkedList<Building> getBuildingSide1() {
		return buildingSide1;
	}


	public void setBuildingSide1(LinkedList<Building> buildingSide1) {
		this.buildingSide1 = buildingSide1;
	}


	public LinkedList<Building> getBuildingSide2() {
		return buildingSide2;
	}


	public void setBuildingSide2(LinkedList<Building> buildingSide2) {
		this.buildingSide2 = buildingSide2;
	}
	public Building  getBuildingS1(int index) {
		return buildingSide1.get(index);
	}
	public Building  getBuildingS2(int index) {
		return buildingSide2.get(index);
	}
	
	
	
	
	
	public int getLenght() {
		return lenght;
	}
	public void setLenght(int lenght) {
		this.lenght = lenght;
	}
	
	
	/**
	 * Adds which position the building will be in
	 *@param building 
	 *@param position
	 */
	public void addBuildingSide1(Building building,int position) {
		int i=0,k=0;
		boolean flag =true;
		for(k=position;k<lenght;k++) {
			for(i=0;i<buildingCountSide1;i++) {
				if(buildingSide1.get(i).getStartArea() <= k 
						&& buildingSide1.get(i).getEndArea() >= k) {
					flag = false;
					break;
				}
			}
				
		}
		
		if(flag == true) {
			buildingSide1.add(building); 
			
			buildingCountSide1++;
			building.setStartArea(position);
			building.setEndArea(building.getLength()+ position-1);
			building.setSide(1);
			remainder = remainder - building.getLength();
		}
		else {
			System.out.println("The field is Full");
		}
	}
	/**
	 * Adds which position the building will be in
	 *@param building 
	 *@param position
	 */
	public void addBuildingSide2(Building building,int position) {
		int i=0,k=0;
		boolean flag =true;
		int tmp=position;
		for(k=position;k<building.getLength()+lenght;k++) {
			for(i=0;i<buildingCountSide2;i++) {
				if(buildingSide2.get(i).getStartArea() <= position 
						&& buildingSide2.get(i).getEndArea() >= position) {
					flag = false;
					break;
				}
			}
			
		}
		
		if(flag == true) {
			buildingSide2.add(building);
			buildingCountSide2++;
			building.setStartArea(position);
			building.setEndArea(building.getLength()+ position);
			building.setSide(2);
			remainder = remainder - building.getLength();
		}
		else {
			System.out.println("The field is Full");
		}
	}
	/**
	 * print All Side in street
	 */
	public void printBuildings() {
		printSide1();
		printSide2();
	}
	
	/**
	 * Delete building in street if there is building
	 * @param name
	 */
	public void deleteBuildings(String name) {
		int i=0,k=0;
		
		for(i=0;i < buildingCountSide1;i++) {
			
			if(name.equals((buildingSide1.get(i)).getName())) {
				buildingSide1.remove(i);
				buildingCountSide1--;
				return;
			}
				 
		}
		for(i=0;i < buildingCountSide2;i++) {
			if(name.equals(buildingSide2.get(i).getName())) {
				buildingSide2.remove(i);
				buildingCountSide2--;
				break;
			}
				 
		}
	}
	private void printSide1() {
		int i=0;
		System.out.println("Side 1");
		for(i=0;i<buildingCountSide1;i++) {
			System.out.println("Building Position:" +buildingSide1.get(i).getStartArea() +"-" +
					buildingSide1.get(i).getEndArea());
			
			if(buildingSide1.get(i) instanceof House) {
				System.out.println("House");
				System.out.println("Building Owner: " +((House) buildingSide1.get(i)).getOwner());
				System.out.println("House color: "+ ((House) buildingSide1.get(i)).getColor());
				System.out.println("Room Number: " +((House) buildingSide1.get(i)).getRoomNumber());
				System.out.println("Building Height: " + ((House) buildingSide1.get(i)).getHeight());
				
			}
			else if(buildingSide1.get(i) instanceof Market) {
				System.out.println("Market");
				System.out.println("Building Owner: " +((Market) buildingSide1.get(i)).getOwner());
				 ((Market) buildingSide1.get(i)).printHours();
				 System.out.println("Building Height: " + ((Market) buildingSide1.get(i)).getHeight());
				
			}
			else if(buildingSide1.get(i) instanceof Office) {
				System.out.println("Office");
				System.out.println("Building Owner: " +((Office) buildingSide1.get(i)).getOwner());
				System.out.println("JobType: " +((Office) buildingSide1.get(i)).getJopType());
				System.out.println("Building Height: " + ((Office) buildingSide1.get(i)).getHeight());
			}
			else if(buildingSide1.get(i) instanceof Playground) {
				System.out.println("Playground");
				System.out.println("Building Name: " +((Playground) buildingSide1.get(i)).getName());
			}
			System.out.println("-------------------------------------------------------------");
		}
	}
	private void printSide2() {
		int i=0;
		System.out.println("Side 2");
		for(i=0;i<buildingCountSide2;i++) {
			
			System.out.println("Building Position:" +buildingSide2.get(i).getStartArea() +"-" +
					buildingSide2.get(i).getEndArea());
			if(buildingSide2.get(i) instanceof House) {
				System.out.println("House");
				System.out.println("Building Owner: " +((House) buildingSide2.get(i)).getOwner());
				System.out.println("House color: "+ ((House) buildingSide2.get(i)).getColor());
				System.out.println("Room Number: " +((House) buildingSide2.get(i)).getRoomNumber());
				System.out.println("Building Height: " + ((House) buildingSide2.get(i)).getHeight());
				
			}
			else if(buildingSide2.get(i) instanceof Market) {
				System.out.println("Market");
				System.out.println("Building Owner: " +((Market) buildingSide2.get(i)).getOwner());
				 ((Market) buildingSide2.get(i)).printHours();
				 System.out.println("Building Height: " + ((Market) buildingSide2.get(i)).getHeight());
				
			}
			else if(buildingSide2.get(i) instanceof Office) {
				System.out.println("Office");
				System.out.println("Building Owner: " +((Office) buildingSide2.get(i)).getOwner());
				System.out.println("JobType: " +((Office) buildingSide2.get(i)).getJopType());
				System.out.println("Building Height: " + ((Office) buildingSide2.get(i)).getHeight());
			}
			else if(buildingSide2.get(i) instanceof Playground) {
				System.out.println("Playground");
				System.out.println("Building Name: " +((Playground) buildingSide2.get(i)).getName());
			}
			System.out.println("-------------------------------------------------------------");
		}
	}
}
