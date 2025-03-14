#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define row_size 20
#define colum_size 20
#define word_count 10
#define word_size 20


void readfile(char text_area[20][20],char words[10][20]); // read word
void random_word(char word[20],char text_area[20][20]); // set in matris randomly 
void write(char text_area[20][20],char words[10][20]);// print matris on terminale
int find_word(char text_area[20][20],int row,int colum,char word[20]); // find word in matris
int turn_int(char colum); //  return letter to int number 
int my_atoi(char row);
void upper_case(char text_area[20][20],int flag,int row,int colum,int counter); // change uppercese in matris
int is_there(char words[10][20],char word[20]); //    word is exist or there isnt word and if word there is change upprecese words array
void words_array_upper(char words[10][20],char word[20]);

int main(){
	char text_area[row_size][colum_size]; // matriss
	int i=0,j=0;
	int num_culom,row,flag=1,counter=0;
	char words[word_count][word_size]; // 10 words
	char colum,word[word_size];
	
	for(i=0;i<20;i++){ // for esay to write on terminale
		for(j=0;j<20;j++){
			text_area[i][j]='*'; 
		}
		
	}
	readfile(text_area,words);
	while(counter<10){ 
		write(text_area,words);
		printf("\nPlease enter the coordinate and the word\n");
		scanf(" %c",&colum);
		scanf(" %d",&row);
		scanf("%s",word);
		num_culom=turn_int(colum);
		if(strncmp(word,"XIT",3)==0 && colum=='E') // if user input EXIT
			exit(1);

		flag=is_there(words ,word); // if word is  , flag is 0 word 
		if(flag==0){
			counter++;	
			flag=find_word(text_area,row,num_culom,word);
			if(flag!=0){
				words_array_upper(words,word);
			}
		}
	}	
}
void words_array_upper(char words[10][20],char word[20]){
	int i =0,j=0,flag=0,lenght=0;

	lenght=strlen(word);
	
	for(i=0;i<10;i++){
		flag=strncmp(words[i],word,lenght);
		
		if(flag==0){
			for(j=0;j<lenght;j++){ // letter chance uppercase
				words[i][j]=words[i][j] - 32;
			}
			break;
		}
	}
}
int is_there(char words[10][20],char word[20]){
	int i =0,j=0,flag=0,lenght=0;

	lenght=strlen(word);
	
	for(i=0;i<10;i++){
		flag=strncmp(words[i],word,lenght);
		
		if(flag==0){
			break;
		}
	}
	return flag;
}

int turn_int(char colum){
	return colum -65;
}

void readfile(char text_area[20][20],char words[10][20]){
	FILE *fp;
	char word[20],ch;
	int random=0,i=0,j=0,k=0;
	int word_number[10]; //take  line number
	
	fp=fopen("words.txt","r");

	srand(time(NULL)); 
	
	
	for(i=0;i<10;i++){ // read 10 word
		fseek(fp,0,SEEK_SET);
		random=rand()%99; // for random line
		while(j<i){ // for loop not select same word
			if(word_number[j]==random){ // for same number
				random=rand()%99;
				j=0;
				
			}
			j++;
		}
		j=0;
		while(random!=j){ // go line number
			fscanf(fp,"%c",&ch);
			if(ch=='\n'){ 
				j++;
			}
		}
		ch='\0';
		while(ch!='\n'){ // read word
			fscanf(fp,"%c",&ch);
			word[k]=ch;
			words[i][k]=ch;
			k++;
			
		}
		word[k-1]='\0'; // last character  is space
		words[i][k-1]='\0';
		
		random_word(word,text_area); // function place word
		word_number[i]=random;
		k=0;
		j=0;
	}

	
}
void random_word(char word[20],char text_area[20][20]){
	
	
	int x=0,y=0,i=0,flag=0;
	int random=0, counter=0,direction=0; 
	/* 
		1-) left to right horizontal
		2-) right to left horizontal
		3-) up to down vertical
		4-) down to up vertical
		5-) left up to right down diognal
		6-) right up to left down diognal
		7-) right down to left up diognal
		7-) left down to right up diognal
	*/
	
		x=rand()%19; // randum row
		y=rand()%19; // randum colum
		direction=1+rand()%8; // randum direction 


		
		counter=strlen(word);
		counter--;  //counter more +1 character so last character is '\0';
		
		if(direction==1){ // this condition search empty area for direction and word
			while(x +counter>19){
				x=rand()%19;
			}
			for(i=0;i<counter;i++){ // search empty or full
				if(text_area[y][x+i]!='*'){
					x=rand()%19;
					y=rand()%19;
					while(x +counter>19){
						x=rand()%19;
					}
					i=0;
				}
			}
			
			for(i=0;i<counter;i++){ // this loop place word in array
				text_area[y][x+i]=word[i];

			}
			
		}
		else if(direction==2){
			
			while(x-counter<0){
				x=rand()%19;
			}
			for(i=0;i<counter;i++){
				if(text_area[y][x-i]!='*'){
					x=rand()%19;
					y=rand()%19;
					while(x -counter<0){
						x=rand()%19;
					}
					i=0;
				}	
			}
			for(i=0;i<counter;i++){
				text_area[y][x-i]=word[i];
			}
		}
		else if(direction==3){
			while(y+counter > 19){
				y=rand()%19;
			}
			for(i=0;i<counter;i++){
				if(text_area[y+i][x]!='*'){
					x=rand()%19;
					y=rand()%19;
					while(y +counter>19){
						y=rand()%19;
					}
					i=0;
				}
			}
			for(i=0;i<counter;i++){
				text_area[y+i][x]=word[i];

			}
		}
		else if(direction==4){
			while(y-counter > 19){
				y=rand()%19;
			}
			for(i=0;i<counter;i++){
				if(text_area[y-i][x]!='*'){
					x=rand()%19;
					y=rand()%19;
					while(y-counter > 19){
						y=rand()%19;
					}
					i=0;
				}
			}
			for(i=0;i<counter;i++){
				text_area[y-i][x]=word[i];

			}
		}
		else if(direction==5){
			while((x+counter > 19) || (y + counter > 19)){
					y=rand()%19;
					x=rand()%19;
			}
			for(i=0;i<counter;i++){
				if(text_area[y+i][x+i]!='*'){
					y=rand()%19;
					x=rand()%19;
					while((x+counter > 19) || (y + counter > 19)){
						y=rand()%19;
						x=rand()%19;
					}
					i=0;
				}
			}
			for(i=0;i<counter;i++){
				text_area[y+i][x+i]=word[i];

			}
		}
		else if(direction==6){
			while((x-counter < 0) || (y + counter > 19)){
					y=rand()%19;
					x=rand()%19;
					
			}
			for(i=0;i<counter;i++){
				if(text_area[y+i][x-i]!='*'){
					y=rand()%19;
					x=rand()%19;
					while((x-counter < 0) || (y + counter > 19)){
						y=rand()%19;
						x=rand()%19;
						
					}
					
					i=0;
				}
			}

			for(i=0;i<counter;i++){
				text_area[y+i][x-i]=word[i];

			}
		}
		else if(direction==7){
			while((x-counter < 0) || (y - counter < 0)){
					y=rand()%19;
					x=rand()%19;
			}
			for(i=0;i<counter;i++){
				//fprintf(fp, ":i:%d  ",i );
				if(text_area[y-i][x-i]!='*'){
					y=rand()%19;
					x=rand()%19;
					while((x-counter < 0) || (y - counter < 0)){
						y=rand()%19;
						x=rand()%19;
					}
					i=0;
				}
			}

			for(i=0;i<counter;i++){
				text_area[y-i][x-i]=word[i];

			}
		}
		else if(direction==8){
			while((x+counter > 19) || (y - counter < 0)){
					y=rand()%19;
					x=rand()%19;
			}
			for(i=0;i<counter;i++){
				if(text_area[y-i][x+i]!='*'){
					y=rand()%19;
					x=rand()%19;
					while((x+counter > 19) || (y - counter < 0)){
						y=rand()%19;
						x=rand()%19;
					}
					i=0;
				}
			}
			for(i=0;i<counter;i++){
				text_area[y-i][x+i]=word[i];
			}
		}
		
		//printf("word:%s\n",word ); // word, direction and cordinate
		//printf("direction:%d\n", direction );
		//printf("row:%d colum:%d\n",y,x );

}
void write(char text_area[20][20],char words[10][20]){ // print matris text_area
	int i=0,j=0;

	
	
	printf("\n");
	printf("    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19\n A|");

	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			if(text_area[i][j]=='*')
				printf(" %c ",97+rand()%26);
			else
				printf(" %c ",text_area[i][j] );
		}
		if(i<10)
			printf("  %s \n %c|",words[i],'A'+i+1 );
		else if(i!=19)
			printf("\n %c|",'A'+i+1);
	}


}
int find_word(char text_area[20][20],int row,int colum,char word[20]){
	int counter=0,i=0 ,flag=0;
	


	while(word[counter]!='\0')
		counter++;
	
	/* 
		1-) left to right horizontal
		2-) right to left horizontal
		3-) up to down vertical
		4-) down to up vertical
		5-) left up to right down diognal
		6-) right up to left down diognal
		7-) right down to left up diognal
		8-) left down to right up diognal
	*/
	
	//printf("row:%d colum:%d text_area:%c\n",row ,colum,text_area[colum][row] );
	for(i=0;i<counter;i++){
		//	printf(" %c ",text_area[colum][row+i] );
		if(text_area[colum][row+i]==word[i]){ // if flag equal 1 word exist, flag is equal is 0 word nothing
			//printf("-%d ",i);
			flag=1;
		}	
		else{
			flag=0;
			//printf("evet+%d\n",i );
			break;
		}
	}
	if(flag==0){	
		for(i=0;i<counter;i++){
			if(text_area[colum][row-i]==word[i])
				flag=2;
			else{
				flag=0;
				break;
			}
			
		}
	}
	if(flag==0){	
		for(i=0;i<counter;i++){
			if(text_area[colum+i][row]==word[i])
				flag=3;
			else{
				flag=0;
				break;
			}
		} 
	}
	if(flag==0){
		for(i=0;i<counter;i++){
			if(text_area[colum-i][row]==word[i])
				flag=4;
			else{
				flag=0;
				break;
			}
		} 
	}	
	if(flag==0){
		for(i=0;i<counter;i++){
			if(text_area[colum+i][row+i]==word[i])
				flag=5;
			else{
				flag=0;
				break;
			}
		} 
	}
	if(flag==0){
		for(i=0;i<counter;i++){
			if(text_area[colum+i][row-i]==word[i])
				flag=6;
			else{
				flag=0;
				break;
			}
		} 
	}
	if(flag==0){
		for(i=0;i<counter;i++){
			if(text_area[colum-i][row-i]==word[i])
				flag=7;
			else{
				flag=0;
				break;
			}
		}
	}
	if(flag==0){
		for(i=0;i<counter;i++){
			if(text_area[colum-i][row+i]==word[i])
				flag=8;
			else{
				flag=0;
				break;
			}
		} 
	}	
	if(flag!=0){
		
		upper_case(text_area,flag,row,colum,counter);
	}
	return flag;
}
void upper_case(char text_area[20][20],int flag,int row,int colum,int counter){ // upprecase in matris
	int i=0;
	/* 
		1-) left to right horizontal
		2-) right to left horizontal
		3-) up to down vertical
		4-) down to up vertical
		5-) left up to right down diognal
		6-) right up to left down diognal
		7-) right down to left up diognal
		8-) left down to right up diognal
	*/
	if(flag==1){
		for(i=0;i<counter;i++){
			text_area[colum][row+i]=text_area[colum][row+i]-32;
		}
	}
	else if(flag==2){
		for(i=0;i<counter;i++){
			text_area[colum][row-i]=text_area[colum][row-i]-32;
		}
	}
	else if(flag==3){
		for(i=0;i<counter;i++){
			text_area[colum+i][row]=text_area[colum+i][row]-32;
		}
	}
	else if(flag==4){
		for(i=0;i<counter;i++){
			text_area[colum-i][row]=text_area[colum-i][row]-32;
		}
	}
	else if(flag==5){
		for(i=0;i<counter;i++){
			text_area[colum+i][row+i]=text_area[colum+i][row+i]-32;
		}
	}
	else if(flag==6){
		for(i=0;i<counter;i++){
			text_area[colum+i][row-i]=text_area[colum+i][row-i]-32;
		}
	}
	else if(flag==7){
		for(i=0;i<counter;i++){
			text_area[colum-i][row-i]=text_area[colum-i][row-i]-32;
		}
	}
	else if(flag==8){
		for(i=0;i<counter;i++){
			text_area[colum-i][row+i]=text_area[colum-i][row+i]-32;
		}
	}
}


