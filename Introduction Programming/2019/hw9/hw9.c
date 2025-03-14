#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct person{
 char name[20];
 char surname[20];
 char musical_Work[20];
 int age;
struct person *next;
} *top;


void menu();
void deleteNode();
void add_node(char name[20],char surname[20],char musical_Work[20],int age);
void print_stack();
void Sort_Alphabetically();
void Sort_Increasingly();
int main(){
	top=(struct person*)malloc(sizeof(struct person));
	top->next=NULL; 	
	menu();

}
void menu(){
	int num=0,age;
	char name[20],surname[20],musical_Work[20];

	while(num!=5){	
		
		
		printf("****MENU****\n1- Add a Person to the Stack\n2- Pop a Person from the Stack\n3- Sort Alphabetical Order\n4- Sort Age in Increasing Order\n5- Exit menu\n*************\n");
		
		if (scanf("%d", &num) < 1)
   			break;
		
		if(num==1){
			printf("name surname musical_Work and age\n");
			scanf("%s",name);
			scanf("%s",surname);
			scanf("%s",musical_Work);
			scanf("%d",&age);
			add_node(name,surname,musical_Work,age);
			print_stack();
			

		}
		else if(num==2){
			deleteNode();
		}
		else if(num==3){
			Sort_Alphabetically();
			print_stack();
		}
		else if(num ==4){
			Sort_Increasingly();
			print_stack();

		}
		else if(num==5){
			break;
		}
		else if(num==6){
			printf("%s\n",top->name );
			printf("%s\n",top->next->name );
			printf("%s\n",top->next->next->name );
			print_stack();

		}
	}
}
void add_node( char name[20],char surname[20],char musical_Work[20],int age){
	struct person *iter;
	iter=top;

	
	while(iter->next!=NULL){
		printf("girdi\n");
	
		iter=iter->next;
	}

	strcpy(iter->name,name);
	strcpy(iter->surname,surname);
	strcpy(iter->musical_Work,musical_Work);
	iter->age=age;
	iter->next=(struct person*)malloc(sizeof(struct person));
	iter=iter->next;
	iter->next=NULL;
	
	
	


}
void deleteNode(){
	struct person *iter;
	struct person *temp;
	iter=top;
	while(iter->next->next !=NULL){
		 iter=iter->next;
	}
	temp=iter->next;
	iter->next=NULL;
	free(temp);
}
void Sort_Alphabetically(){
	struct person *iter;
	struct person *temp;
	temp=(struct person*)malloc(sizeof(struct person));
	iter=top;
	while(iter->next!=NULL){
		printf("neden\n");
		if(iter->name[0]>iter->next->name[0]){
			printf("girdi\n");
			strcpy(temp->name,iter->name);
			strcpy(temp->surname,iter->surname);
			strcpy(temp->musical_Work,iter->musical_Work);
			temp->age=iter->age;

			strcpy(iter->name,iter->next->name);
			strcpy(iter->surname,iter->next->surname);
			strcpy(iter->musical_Work,iter->next->musical_Work);
			iter->age=iter->next->age;

			strcpy(iter->next->name,temp->name);
			strcpy(iter->next->surname,temp->surname);
			strcpy(iter->next->musical_Work,temp->musical_Work);
			iter->next->age=temp->age;


			iter=top;
			
		}
		else{
			printf("else\n");
			iter=iter->next;
		}
		
	}
}
void print_stack(){
	struct person *iter;
	iter=top;

	while(iter->next!=NULL){
		printf("name:%s\n",iter->name );
		printf("surname:%s\n",iter->surname );
		printf("musical_Work:%s\n",iter->musical_Work );
		printf("Age:%d\n",iter->age );
		printf("------------------------------\n");
		iter=iter->next;

	}

}
void Sort_Increasingly(){
	struct person *iter;
	struct person *temp;
	temp=(struct person*)malloc(sizeof(struct person));
	iter=top;						
	while(iter->next!=NULL){
		printf("neden\n");
		if(iter->age > iter->next->age){
			printf("girdi\n");
			strcpy(temp->name,iter->name);
			strcpy(temp->surname,iter->surname);
			strcpy(temp->musical_Work,iter->musical_Work);
			temp->age=iter->age;

			strcpy(iter->name,iter->next->name);
			strcpy(iter->surname,iter->next->surname);
			strcpy(iter->musical_Work,iter->next->musical_Work);
			iter->age=iter->next->age;

			strcpy(iter->next->name,temp->name);
			strcpy(iter->next->surname,temp->surname);
			strcpy(iter->next->musical_Work,temp->musical_Work);
			iter->next->age=temp->age;

			iter=top;
			
		}else{
			printf("else\n");
			iter=iter->next;
		}
		
	}
	
}