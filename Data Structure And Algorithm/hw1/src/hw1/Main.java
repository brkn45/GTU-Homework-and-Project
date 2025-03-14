package hw1;

import java.util.Scanner;
/**
 * Sofware driver class. Test all function, 
 * Start software application
 */
public class Main {

	/**
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {
		/*
		 * Unit test. All function tested below.
		 */
		try {
			City city = new City();
			
			House house1 = new House(10,2,5,"blue","Berkan"); // lenght,height,roomNumber, color, owner
			Market market1 = new Market(15,4,10,30,18,30,"Ahmet");
			Office office1 = new Office(10,4,"Software","Hatice");
		
			House house2 = new House(10,2,5,"blue","Bilal"); // lenght,height,roomNumber, color, owner
			Market market2 = new Market(15,4,10,30,18,30,"Mahmut");
			Office office2 = new Office(10,4,"Software","Ferhat");
			Playground pg = new Playground(10,"Hamdi");
			
			city.getStreet().addBuildingSide1(house1, 0);
			city.getStreet().addBuildingSide1(market1, 20);
			city.getStreet().addBuildingSide1(office1, 50);
			city.getStreet().addBuildingSide1(pg, 80);
			
			city.getStreet().addBuildingSide2(house2, 0);
			city.getStreet().addBuildingSide2(market2, 20);
			city.getStreet().addBuildingSide2(office2, 50);
			
			city.getStreet().printBuildings();
			System.out.println("-------------------------------------------------------------");
			System.out.println("Delete Test");
			city.getStreet().deleteBuildings("Berkan");
			city.getStreet().deleteBuildings("Mahmut");
			
			city.getStreet().printBuildings();
			System.out.println("-------------------------------------------------------------");
			System.out.println("Edit Mode Test");
			EditMode emode = new EditMode(city); // EditMode Test
			emode.addBuildingHouse("Alp", "blue", 5, 15, 5, 1, 70);
			emode.addBuildingMarket("Ali", 10, 30, 18, 30, 5, 2, 3, 45);
			emode.addBuildingOffice("Burak", "Software", 4, 3, 2, 90);
			emode.addBuildingPlayground("Gazi",10, 20, 30);
			
			city.getStreet().printBuildings();
			
			System.out.println("Edit Delete Test");
			emode.removeBuilding("Ali");
			emode.removeBuilding("Burak");
			emode.removeBuilding("Hasan");  // there arent in street
			
			city.getStreet().printBuildings();
			System.out.println("-------------------------------------------------------------");
			ViewMode vmode = new ViewMode(city);
			
			vmode.printListofStreet();
			
			vmode.printRatioOfPlayground();
			vmode.printRemaingLenght();
			vmode.printStreetAccupied();
			
			
			vmode.printSilhouette();
			
			int mode;
			/*
			 * Start Application below
			 */
			//-------------------------------------------------------------
			//-------------------------------------------------------------
			
			System.out.println("\nWelcome City Planer Appliacation");
			//-------------------------------------------------------------
			//-------------------------------------------------------------
			CitySystemApplication app = new CitySystemApplication(city);
			while(true) {
				System.out.println("Please Select Application Mode");
				System.out.println("1-)Edit Mode");
				System.out.println("2-)View Mode");
				Scanner myObj = new Scanner(System.in);
				mode = myObj.nextInt();
				if(mode == 1 || mode == 2) {
					
					app.startApplication(mode);
				}
				else {
					System.out.println("Wrong Choice");
				}
			}
		}
		catch(Exception e){
			e.printStackTrace();
		
		}
		
		
		
		
		
	}

}
