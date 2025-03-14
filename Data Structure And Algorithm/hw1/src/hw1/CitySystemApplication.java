package hw1;

import java.util.Scanner;

/**
 * City system application, Create Building and add  or remove in street
 * @author berkan
 *
 */
public class CitySystemApplication {
	private int mode,lenght;
	private EditMode editMode;
	private ViewMode viewMode;
	private String streetName;
	private City city;
	
	/**
	 * 
	 * @param city
	 */
	public CitySystemApplication(City city) {
		super();
		
		this.editMode = new EditMode(city);
		this.viewMode = new ViewMode(city);
	}

	/**
	 * @return
	 */
	public City getCity() {
		return city;
	}

	/**
	 * @param city
	 */
	public void setCity(City city) {
		this.city = city;
	}

	/**
	 * @param mode
	 */
	public void startApplication(int mode) {
		
		Scanner myObj = new Scanner(System.in);
		if(mode ==1) {
			while(true) {
				System.out.println("1)Add Buildings");
				System.out.println("2)Delete Buildings");
				System.out.println("3)Back");
				mode = myObj.nextInt();
				if(mode==1) {
					addBuild();
					
				}
				else if(mode ==2 ) {
					deleteBuildings();
				}
				
				else if(mode == 3) {
					break;
				}
			}
			
		}
		else if(mode ==2) {
			while(true) {
				System.out.println("1)Display The Total Remaining Length");
				System.out.println("2)Display The List Of Buildings On The Street.");
				System.out.println("3)Display The Number and Ratio Of Lenth Of Playgrounds");
				System.out.println("4)Calculate The Total Length Of Street Occupied");
				System.out.println("5)Display the Skyline Silhouette Of The Street");
				System.out.println("6)Back");
				mode = myObj.nextInt();
				if(mode ==1 ) {
					viewMode.printRemaingLenght();
				}
				else if(mode == 2) {
					viewMode.printListofStreet();
				}
				else if(mode ==3 ) {
					viewMode.printRatioOfPlayground();
				}
				else if(mode == 4) {
					viewMode.printStreetAccupied();
				}
				else if(mode == 5) {
					
				}
				else if(mode == 6) {
					break;
				}
			}	
		}
	}
	
	
	/**
	 * 
	 */
	private void addBuild() {
		int side;
		while(true) {
			Scanner myObj = new Scanner(System.in);
			
			System.out.println("Select Side 1 or 2");
			side = myObj.nextInt();
			System.out.println("Select Buildings");
			System.out.println("1)House");
			System.out.println("2)Office");
			System.out.println("3)Market");
			System.out.println("4)Playground");
			System.out.println("5)Exit");
			mode = myObj.nextInt();
			if(mode ==1) {
				buildHouse(side);
				break;
			}
			else if(mode ==2) {
				buildOffice(side);
				break;
			}
			else if(mode == 3) {
				buildMarket(side);
				break;
			}
			else if(mode == 4) {
				buildPlayground(side);
				break;
			}
			else  if(mode ==5){
				break;
			}
		}
		
	}
		
	/**
	 * @param side
	 */
	private void buildHouse(int side) {
		Scanner myObj = new Scanner(System.in);
		String owner,color;
		int height,roomNumber,position,lenght;
		System.out.println("Please Enter Owner Name");
		owner = myObj.next();
		System.out.println("Please Enter Color");
		color = myObj.next();
		System.out.println("Please Enter Height");
		height = myObj.nextInt();
		System.out.println("Please Enter Lenght");
		lenght = myObj.nextInt();
		System.out.println("Please Enter Room Number");
		roomNumber = myObj.nextInt();
		System.out.println("Please Enter Position");
		position = myObj.nextInt();
		editMode.addBuildingHouse( owner, color, height,lenght,side, roomNumber, position);
	}
	private void buildOffice(int side) {
		Scanner myObj = new Scanner(System.in);
		String owner,jobType;
		int height,position,lenght;
		System.out.println("Please Enter Owner Name");
		owner = myObj.next();
		System.out.println("Please Enter Job Type");
		jobType = myObj.next();
		System.out.println("Please Enter Height");
		height = myObj.nextInt();
		System.out.println("Please Enter Lenght");
		lenght = myObj.nextInt();
		System.out.println("Please Enter Position");
		position = myObj.nextInt();
		editMode.addBuildingOffice( owner, jobType, lenght, height, side, position);
	}
	/**
	 * @param side
	 */
	private void buildMarket(int side) {
		Scanner myObj = new Scanner(System.in);
		String owner;
		int height,position,lenght,startHours,startMinute,endHours,endMinute;
		System.out.println("Please Enter Owner Name");
		owner = myObj.next();
		
		System.out.println("Please Enter Height");
		height = myObj.nextInt();
		System.out.println("Please Enter Lenght");
		lenght = myObj.nextInt();
		System.out.println("Please Enter Position");
		position = myObj.nextInt();
		System.out.println("Please Enter Start Hours");
		startHours = myObj.nextInt();
		System.out.println("Please Enter Start Minute");
		startMinute = myObj.nextInt();
		System.out.println("Please Enter Close Hour");
		endHours = myObj.nextInt();
		System.out.println("Please Enter Close Minute");
		endMinute = myObj.nextInt();
		editMode.addBuildingMarket( owner, startHours, startMinute, endHours, endMinute, side, height, side, position);
	}
	
	/**
	 * @param side
	 */
	private void buildPlayground(int side) {
		int lenght,position;
		Scanner myObj = new Scanner(System.in);
		System.out.println("Please Enter Owner Name");
		String name; 
		name = myObj.next();
		
		System.out.println("Please Enter Lenght");
		lenght = myObj.nextInt();
		System.out.println("Please Enter position");
		position = myObj.nextInt();
		editMode.addBuildingPlayground(name, lenght, position, side);
	}
	/**
	 * 
	 */
	private void deleteBuildings() {
		Scanner myObj = new Scanner(System.in);
		String name;
		System.out.println("Please Enter Owner or Building Name");
		name = myObj.next();
		city.getStreet().deleteBuildings(name);
	}
}
