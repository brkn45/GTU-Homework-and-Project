#include <stdio.h>

#define euro 6.69
#define dollar 6.14
int main(){
	double money=0, chance;
	int choice1=0,choice2=0;
	printf("***** Welcome to ABC Exchange Office *****\n");
	
		printf("Enter your amount\n");
		scanf("%lf",&money);
		printf("Please select your currency\n");
		printf("1.Turkish Lira\n2.Euro\n3.Dollar\n");
		scanf("%d",&choice1);


		
		switch (choice1){  // Menu
			case 1 : 
			printf("You have %lf Turkish Liras\n",money );
			break;
			case 2:
			printf("You have %lf Euro\n",money );
			break;
			case 3 :
			printf("you have %lf Dollar\n",money);	
			break;
			default :
			printf("Yuor selection is invalid\n");  
			break;
		}	
			printf("Choose which currency you want convert\n");
			scanf("%d",&choice2);

			if(choice1==1 && choice2==2){ // checking condition for change
				chance=money/euro;
				printf("You have %lf Euro \n",chance );

			}
			else if(choice1 == 1 && choice2 == 3){
				chance=money/dollar;
				printf("You have %lf Dollar  \n", chance);
			}
			else if(choice1==2 && choice2==1){
				chance=money*euro;
				printf("You have %lf Turkish Liras\n",chance );
			}
			else if( choice1 ==2 && choice2 ==3){
				chance=money*euro; //chance  euro to TL
				chance=chance/dollar;
				printf("You have %lf Dollar\n",chance );
			}
			else if(choice1==3 && choice2 ==1){
				chance=money*dollar;
				printf("You have %lf Turkish Liras\n",chance );
			}
			else if(choice1==3 && choice2 ==2){
				chance =money*dollar; // chance  dollar to TL 
				chance= chance /euro;
				printf("You have %lf Euro\n", chance );

			}
			else{
				printf("Your selection is invalid\n");
			}

			

		
}