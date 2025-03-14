#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define MY_HOME_X 1 // my home adress
#define MY_HOME_Y 1

struct Hospital{
	char* name;
	char citiesServed[3];
}results[4];

struct card {
const char *face;
const char *suit;
}card_num[52];

int numPathsHome(int street, int avenue); // combination calculation
int canOfferCovidCoverage(char cities[6], char locations[4][3], int numHospitals, struct Hospital results[4]); // is covred all area
void cart_read(char faces[13][6],char suits[4][10],int num); // diffrent cart write struct 
void cart_write(int index);  // print mix screen 

void part1();
void part2();
void part3();

int counter=0;

int main(){
	part1();
	part2();
	part3();
}
void part3(){
	char faces[13][6]={"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	char suits[4][10]={"Hearts", "Diamonds", "Clubs", "Spades"};
	
	cart_read(faces,suits,0);
	srand(time(NULL)); 
	cart_write(0);
}
void cart_write(int index){ // write cart
	int random,count=0,i=0;
	int numbers[52];
	for(i=0;i<52;i++){
		random=rand()%52;
		while(i>count){
			if(numbers[count]==random){
				random=rand()%52;
				count=0;
			}
			count++;
		}

		printf("  %s of %s  \t",card_num[random].face,card_num[random].suit );
		numbers[i]=random;
		count=0;
		random=rand()%52;
		while(i>count){
			if(numbers[count]==random){
				random=rand()%52;
				count=0;
			}
			count++;

		}
		i++;
		printf(" %s of %s\n",card_num[random].face,card_num[random].suit );
		count=0;
		numbers[i]=random;
		
	}	

}	
void cart_read(char faces[13][6],char suits[4][10],int num){ // struct take cart name
	if(num==52){

		return;
	}
	else{
		card_num[num].face=faces[num%13];
		card_num[num].suit=suits[num%4	];
		cart_read(faces,suits,num+1);	
	}
}



void part2(){
	int flag=0,numHospitals=0;
	char cities[6] = {'A','B','C','D', 'E', 'F' };
	char locations[4][3] = {  {'A', 'B', 'C'},{'A','C','D'},  {'B', 'F'},{'C','E','F'}};
	
	printf("Enter the maximum number of hospitals that can be constructed:");
	scanf("%d",&numHospitals);
	
	flag=canOfferCovidCoverage(cities,locations,numHospitals,results);
	if(flag==0){
		printf("No, Same cities aren't covered\n");
	}
	
}
int canOfferCovidCoverage(char cities[6], char locations[4][3], int numHospitals, struct Hospital results[4]){ // the firts step find location ,the second step is checking if all cities are there
	int flag=0 ,control=0;
	
	if(numHospitals==0){ // second step
		if(counter==6){
			printf("Yes, can offer health care to all!\n\n");
			return 1;
		}
		
		
		if(cities[0]==results[0].citiesServed[0]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[0].citiesServed[1]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[0].citiesServed[2]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[1].citiesServed[0]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[1].citiesServed[1]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[1].citiesServed[2] ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[2].citiesServed[0] ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[2].citiesServed[1] ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[2].citiesServed[2] ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[3].citiesServed[0]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[3].citiesServed[1]  ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else if(cities[0]==results[3].citiesServed[2] ){
			counter++;
			return canOfferCovidCoverage(cities+1,locations,numHospitals,results);
		}
		else{
			counter=0;
			return 0;
		}
		
	}	
	if( flag==0){// first step
		strcpy(&results[numHospitals].citiesServed[0],&locations[0][0]);
		strcpy(&results[numHospitals].citiesServed[1],&locations[0][1]);
		strcpy(&results[numHospitals].citiesServed[2],&locations[0][2]);
		flag=canOfferCovidCoverage(cities,locations+1,numHospitals-1,results);
		control=1;
	}
	if( flag==0){
		strcpy(&results[numHospitals].citiesServed[0],&locations[1][0]);
		strcpy(&results[numHospitals].citiesServed[1],&locations[1][1]);
		strcpy(&results[numHospitals].citiesServed[2],&locations[1][2]);
		flag=canOfferCovidCoverage(cities,locations+1,numHospitals-1,results);
		control=2;	
	}
	if(flag==0){
		strcpy(&results[numHospitals].citiesServed[0],&locations[2][0]);
		strcpy(&results[numHospitals].citiesServed[1],&locations[2][1]);
		strcpy(&results[numHospitals].citiesServed[2],&locations[2][2]);
		flag=canOfferCovidCoverage(cities,locations+1,numHospitals-1,results);
		control=3;
	}
	if( flag==0){
		strcpy(&results[numHospitals].citiesServed[0],&locations[3][0]);
		strcpy(&results[numHospitals].citiesServed[1],&locations[3][1]);
		strcpy(&results[numHospitals].citiesServed[2],&locations[3][2]);
		flag=canOfferCovidCoverage(cities,locations+1,numHospitals-1,results);
		control=4;
	}
	
	
	if(flag==1 && control==1){ // third step
		printf("Hospital -%d\n",numHospitals );
		printf("Hospital location: %c%c%c \n",locations[0][0],locations[0][1],locations[0][2] );
		return 1;
	}
	else if(flag==1 && control==2){
		printf("Hospital -%d\n",numHospitals );
		printf("Hospital location: %c%c%c \n",locations[1][0],locations[1][1],locations[1][2] );
		return 1;
	}
	else if(flag==1 && control==3){
		printf("Hospital -%d\n",numHospitals );
		printf("Hospital location: %c%c%c \n",locations[2][0],locations[2][1],locations[2][2] );
		return 1;
	}
	else if(flag==1 && control==4){
		printf("Hospital -%d\n",numHospitals );
		printf("Hospital location: %c%c%c \n",locations[3][0],locations[3][1],locations[3][2] );
		return 1;
	}
}
void part1(){
	int street, avenue,result=0;
	printf("Enter the street Number\n");
	scanf("%d",&street);
	printf("Enter the Avenue\n");
	scanf("%d",&avenue);
	result=numPathsHome(street- MY_HOME_X+avenue -MY_HOME_Y ,avenue - MY_HOME_Y);
	printf("result:%d\n",result );
}
int numPathsHome(int street, int avenue){ // calculete combination
	if (avenue == 0){
        return 1;
	}
    else if(avenue==street){
    	return 1;
    }
    else if (street > avenue){
        return numPathsHome(street-1, avenue) + numPathsHome(street-1,avenue-1);
    }
    

  } 