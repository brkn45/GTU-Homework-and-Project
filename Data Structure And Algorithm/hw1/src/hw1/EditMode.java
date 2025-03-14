package hw1;
/**
 * Editmode class do add and remove every building
 * @author berkan
 *
 */
public class EditMode implements Mode {
	private City city;
	private int streetCount;
	
	/**
	 * @param city
	 */
	public EditMode(City city) {
		this.city = city;
	}
	
	
	/**
	 * @param owner
	 * @param color
	 * @param height
	 * @param lenght
	 * @param roomNumber
	 * @param side
	 * @param position
	 * Add house in street
	 */
	public void addBuildingHouse(String owner,String color,int height,int lenght,int roomNumber,int side,int position) {
		
			if(side ==1) {
				city.getStreet().addBuildingSide1(new House(lenght,height,roomNumber,owner,color), position);
			}
			else if(side ==2){
				city.getStreet().addBuildingSide2(new House(lenght,height,roomNumber,owner,color), position);
			}
			
		
	}
	/**
	 * @param owner
	 * @param jobType
	 * @param lenght
	 * @param height
	 * @param side
	 * @param position
	 * add Office in street
	 */
	public void addBuildingOffice(String owner,String jobType,int lenght,int height,int side,int position) {
		if(side == 1) {
			city.getStreet().addBuildingSide1(new Office(lenght,height,jobType,owner), position);
		}
		else if(side == 2) {
			city.getStreet().addBuildingSide2(new Office(lenght,height,jobType,owner), position);
		}
	}
	/**
	 * @param owner
	 * @param startHours
	 * @param startMinute
	 * @param endHours
	 * @param endMinute
	 * @param lenght
	 * @param height
	 * @param side
	 * @param position
	 * Add market in street
	 */
	public void addBuildingMarket(String owner,int startHours, int startMinute, int endHours, int endMinute,int lenght,int height,int side,int position) {
		if(side == 1) {
			try {
				city.getStreet().addBuildingSide1(new Market(lenght,height,startHours,startMinute,endHours,endMinute,owner), position);
			} catch (Exception e) {
				
				e.printStackTrace();
			}
		}
		else if(side == 2) {
			try {
				city.getStreet().addBuildingSide2(new Market(lenght,height,startHours,startMinute,endHours,endMinute,owner), position);
			} catch (Exception e) {
				
				e.printStackTrace();
			}
		}
	}
	/**
	 * @param name
	 * @param lenght
	 * @param position
	 * @param side
	 * Add playground in street
	 */
	public void addBuildingPlayground(String name,int lenght,int position,int side) {
		if(side == 1) {
			city.getStreet().addBuildingSide1(new Playground(lenght,name), position);
		}
		else if(side == 2) {
			city.getStreet().addBuildingSide2(new Playground(lenght,name), position);
		}
	}
	/**
	 * @param name
	 */
	public void removeBuilding(String name) {
		city.getStreet().deleteBuildings(name);
	}
}
