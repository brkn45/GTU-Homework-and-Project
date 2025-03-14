#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GAME_NUM 2000
#define WORD_SIZE 100
#define	GENRE_NUM 12
#define GENRE_SIZE 20
#define PLATFORM_NUM 10
#define PLATFORM_SIZE 5
#define DATA_TYPE 7	

#define GENRE 0 // Data Array
#define PLATFORM 1
#define YEARS 2
#define NA_SALES 3
#define EU_SALES 4
#define GLOBAL_SALES 5
#define USER_SCORE 6

void readfile(char name[2000][100],char genre[12][20],char platform[10][5], float data[2000][7]); // read file main function
void read_names(char name[2000][100],char line[105],int order); // read  names than set in names array
void read_genre(char genre[12][20],char line[105],float data[2000][7],int order); // read genre than set in genre array and take number data array 
void read_platform(char platform[10][5],char line[105],float data[2000][7],int order); // read platform set in platform array take number data array
void read_data(float data[2000][7],char line[105],int order); // read Eu sales and Na sales than set data array
void menu(char name[2000][100],char genre[12][20],char platform[10][5],float data[2002][7]); // choice option menu
void list_genres(char genre[12][20]); // print genre
void list_platforms(char platform[10][5]); // print platforms
void through_years(float data[2000][7],char name[2000][100]); // print  since or until through years game names
void all_information(char name[2000][100],char genre[12][20],char platform[10][5], float data[2000][7]); // print all information
int my_strcmp(char word1[100],char word2[100]); // find name equal order
void average(float data[2000][7]); // calculate avarage
void geografical(char name[2000][100],float data[2000][7]); // print more sales contient
void frequence_platform(float data[2000][7],char platform[10][5]); // print frequance platform
void frequence_genre(float data[2000][7],char genre[12][20]);	// print frequence genre
int main(){
	char name[GAME_NUM][WORD_SIZE];
	char genre[GENRE_NUM][GENRE_SIZE];
	char platform[PLATFORM_NUM][PLATFORM_SIZE];
	float data[GAME_NUM][DATA_TYPE];
	readfile(name,genre,platform,data);
	menu(name,genre,platform,data);
}
void menu(char name[2000][100],char genre[12][20],char platform[10][5],float data[2002][7]){ // users select option
	int choice=0;
	while(1){
		printf("0: List of the Genres\n1: List of the Platforms\n2: List of the Games Through the Years\n3: All information of a Single Game\n4: Average of the User Scores\n5: Geogrografical Information of Single Game\n6: Frequence of the Genres\n7: Frequence of the platforms\n8: EXIT\n\nPlease Select an Oparation:");
		scanf("%d",&choice);
		switch (choice){
			case 0:
				list_genres(genre);
				break;
			case 1:
				list_platforms(platform);
				break;
			case 2:
				through_years(data,name);
				break;
			case 3:
				all_information(name,genre,platform,data);
				break;		 	
			case 4:
				average(data);
				break;
			case 5:
				geografical(name,data);
				break;
			case 6:
				frequence_genre(data,genre);
				break;
			case 7:
				frequence_platform(data,platform);
				break;
			case 8:
				exit(1);
				break;
			default :
				printf("\nTRY AGAİN\n\n");
				break;		
				

		}
	}
}
void frequence_platform(float data[2000][7],char platform[10][5]){ // find frequance platform and write
	int counter=0,i=0,j=0;

	for(i=0;i<10;i++){
		for(j=0;j<2000;j++){
			if((int)data[j][PLATFORM]==i){
				counter++;
			}
		}
		printf("%s      \t\t%d\n",platform[i],counter );
		counter=0;
	}
	printf("\n\n");

}
	

void frequence_genre(float data[2000][7],char genre[12][20]){ // find frequence genres and write
	int counter=0,i=0,j=0;

	for(i=0;i<12;i++){
		for(j=0;j<2000;j++){
			if((int)data[j][GENRE]==i){
				counter++;
			}
		}
		printf("%s    \t\t%d\n",genre[i],counter );
		counter=0;
	}
	printf("\n\n"); 
}
void geografical(char name[2000][100],float data[2000][7]){  // write more sales contienent
	int i=0,flag=0,order=0;
	char game[100];
	
	while(flag!=2){
		printf("Please enter the name of game\n");
		scanf("%s",game);
		for(i=0;i<2000;i++){
			if(my_strcmp(game,name[i])){
				flag=1;
				order=i;
				break;
			}
		}
		if(flag==1){
			if(data[order][NA_SALES] > data[order][EU_SALES]){
				printf("This Game is more populer is North America\n");
			}
			else if(data[order][NA_SALES] < data[order][EU_SALES]){
				printf("This Game is more populer is Europe\n");
			}
			else if(data[order][NA_SALES] == data[order][EU_SALES]){
				printf("This Game is Same Sales North America and Europe \n");
			}
			flag=2;

		}
		else{
			printf("TRY AGAIN\n");
		}
	}	
}	
void average(float data[2000][7]){ //calculate average
	float sum=0, result=0;
	int i=0;
	for(i=0;i<2000;i++){
		sum=sum+data[i][USER_SCORE];
	}
	result=sum/2000;
	printf("\nAverage:\t%lf\n\n\n",result );
}

void all_information(char name[2000][100],char genre[12][20],char platform[10][5], float data[2000][7]){ // find information and write terminale
	char game[100];
	int i=0,order=0,flag=0,num=0;
	while(flag!=2){
		printf("Please enter the name of game\n");
		scanf("%s",game);
		for(i=0;i<2000;i++){
			if(my_strcmp(game,name[i])){
				flag=1;
				break;
			}
		}
		if(flag==1){
			printf("Name:\t\t\t%s\n",name[i]);
			num=(int)data[i][GENRE];
			printf("Genre:\t\t\t%s\n",genre[num] );
			num=(int)data[i][PLATFORM];
			printf("Platform:\t\t%s\n",platform[num]);
			printf("Year:\t\t\t%.0lf\n",data[i][YEARS] );
			printf("Sales In NA:\t\t%lf\n",data[i][NA_SALES]);
			printf("Sales In EU:\t\t%lf\n",data[i][EU_SALES]);
			if(data[i][GLOBAL_SALES]==0.0)
				printf("Total Sales:\t\tNot Aviable\n" );
			else
				printf("Total Sales:\t\t%lf\n",data[i][GLOBAL_SALES]);
			printf("User Score:\t\t%lf\n",data[i][USER_SCORE] );
			flag=2;
		}
		else{
			printf("TRY AGAIN\n");
		}
	}
	printf("\n\n");
	
}
int my_strcmp(char word1[100],char word2[100]){ // name compare 
	int i=0,flag=1;

	for(i=0;word1[i]!='\0' || word2[i]!='\0';i++){
		if(word1[i]!=word2[i])
			return 0;
	}
	return 1; 
}
void through_years(float data[2000][7],char name[2000][100]){ // write game until or since
	float year=0,time=0;
	int i=0;
	printf("Enter a year\n");
	scanf("%f",&year);
	printf("Until (0) or Since (1) %.0lf \n",year);
	scanf("%f",&time);

	if(time==0){
		for(i=0;i<2000;i++){
			if(data[i][YEARS]<year){
				printf("%s\n",name[i] );
			}
		}
	}
	else if(time==1){
		for(i=0;i<2000;i++){
			if(data[i][YEARS]>year){
				printf("%s\n",name[i] );
			}
		}
	}
		printf("\n\n");

}
void list_platforms(char platform[10][5]){ // list platforms on terminale
	int i=0;
	printf("\n\n");
	for (i = 0; i <10; ++i){
		printf("%s\n",platform[i] );
	}
		printf("\n\n");

}
void list_genres(char genre[12][20]){ // wite genres on terminale
	int i=0;
	printf("\n\n");
	for (i = 0; i <12; ++i){
		printf("%s\n",genre[i] );
	}
	printf("\n\n");
}
void readfile(char name[2000][100],char genre[12][20],char platform[10][5], float data[2000][7]){ // read a sentence
	int i=0;
	char line[105];
	FILE *fp;
	fp=fopen("Video_Games.txt","r");
	fscanf(fp,"%s",line);
	//printf("%s\n",line );
	for(i=0;i<2000;i++){
		fscanf(fp,"%s",line);
		
		read_names(name,line,i);
		//printf("%s\n",name[i] );
		read_genre(genre,line,data,i);
		read_platform(platform,line,data,i);
		read_data(data,line,i);
	}
	
}
void read_data(float data[2000][7],char line[105],int order){ // read data than third comma
	int i=0, counter=0,flag=0;
	float value=0.0;

	for(i=0;line[i]!='\n';i++){
		if(line[i]==','){
			counter++;
			flag=1;
		}
		else if(counter==3 && flag==1){
			sscanf(&line[i],"%f,",&data[order][2]);
			flag=0;
			
		}

		else if(counter==4 && flag==1){
			sscanf(&line[i],"%f,",&data[order][3]);
			flag=0;
		}
		else if(counter==5 && flag==1){
			sscanf(&line[i],"%f,",&data[order][4]);
			flag=0;
		}
		else if(counter==6 && flag==1){
			sscanf(&line[i],"%f,",&data[order][5]);
			flag=0;
		}
		else if(counter==7 && flag==1){
			sscanf(&line[i],"%f,",&data[order][6]);
			flag=0;
		}
	}
}	

void read_platform(char platform[10][5],char line[105],float data[2000][7],int order){
	int i=0,j=0 ,counter=0,flag=1;
	char word_platform[5];
	for(i=0;counter!=3;i++){
		if(line[i]==','){
			counter++;
		}
		else if(counter==2){
			word_platform[j]=line[i];
			j++;
		}
	}
	word_platform[j]='\0';

	for(i=0;i<10;i++){  // this loop is checking if it has the same
		flag=strcmp(word_platform,platform[i]);
		if(flag==0){
			data[order][1]=(float)i;
			i++;
			break;
		}
		if(platform[i][0]=='\0'){
			data[order][1]=(float)i;
			break;
		}

	}
	if(flag!=0){
		strcpy(platform[i],word_platform);
	}
}
void read_genre(char genre[12][20],char line[105],float data[2000][7],int order){ // read first mamodan than  until second comma
	int i=0,j=0,counter=0,flag=1;
	char word_genre[20];
	for(i=0;counter!=2;i++){
		if(line[i]==','){
			counter++;
		}
		else if(counter==1){
			word_genre[j]=line[i];
			j++;
		}
	}
	word_genre[j]='\0';
	//printf("%s\n",word_genre );

	for(i=0;i<12;i++){ //this loop is checking if it has the same
		flag=strcmp(word_genre,genre[i]);
		if(flag==0){
			data[order][0]=(float)i;
			i++;
			break;
		}
		if(genre[i][0]=='\0'){
			data[order][0]=(float)i;
			break;
		}
	}
	if(flag!=0){
		strcpy(genre[i],word_genre);
	}
}
void read_names(char name[2000][100],char line[105],int order){ // read until first comma
	int i=0,counter=0;
	for(i=0;counter!=1;i++){
		if(line[i]==','){
			counter++;
			name[order][i]='\0';
		}
		else
			name[order][i]=line[i];
	}
	
}	
