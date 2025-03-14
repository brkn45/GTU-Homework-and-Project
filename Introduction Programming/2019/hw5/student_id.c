#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int find(char matris[15][15],int coord[][4]);
void add_matris(char **dict,int coord[][4],int dict_counter);
void print_matris(char matris[][15]);
void upper_number(char matris[15][15],int coord[][4],int i);

int get_line_size(char *line) {
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}







int main(){
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	FILE *fp = fopen("word_hunter.dat", "r");
	
	int line_counter = 0;
	int dict_counter = 0;
	int i;
	char **matris;

	while(fgets(line, LINE_LEN, fp) != NULL) {
		
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	fclose(fp);
	//print_dictionary(dict);
	//print_coord(coord);
	
	add_matris(dict,coord,dict_counter);


	
		
	return 0;
}

int find(char matris[15][15], int coord[15][4]){
	int i,num1,num2, control=0;
	char let;
	while(control!=15){
		print_matris(matris);
		printf("enter cordinate and letter\n");
		scanf("%d %d %c",&num1,&num2,&let);
		for(i=0;i<15;i++){
			if((coord[i][0]==num1 &&coord[i][1]==num2) || (coord[i][2]==num1 &&coord[i][3]==num2) ){
				if(matris[num2][num1]==let){
					upper_number(matris,coord,i);
					control++;
				}
			}
		}
	}	


}

void upper_number(char matris[15][15],int coord[][4],int i){
		int dx1,dy1,dx2,dy2;
		dx1=coord[i][0];
		dy1=coord[i][1];
		dx2=coord[i][2];
		dy2=coord[i][3];
		

		if(dx1==dx2){
			while(dy1!=dy2+1){
				matris[dy1][dx1]=matris[dy1][dx1]- 32;
				
				dy1++;	

			}

		}

		else if(dy1==dy2){
			while(dx1!=dx2+1){
				matris[dy1][dx1]=matris[dy1][dx1]- 32;
				printf("matris:%c ",matris[dx1][dy1]);
				
				dx1++;
			}
		}
		else{
			while(dx1!=dx2+1 && dy1!=dy2+1){
				matris[dy1][dx1]=matris[dy1][dx1]- 32;
				
				dx1++;
				dy1++;
			}
		}
		
	
	
}
void add_matris(char **dict,int coord[][4],int dict_counter){
	char matris[15][15];
	int dx1,dx2,dy1,dy2;
	int i,j,counter=0,word=0;
	

	
	
	for(i=0;i<15;i++){
		for(j=0;j<15;j++){
			matris[i][j]='a'+rand()%26;
		}
	}
	print_matris(matris);

	
	for(i=0;i<dict_counter;i++){
		dx1=coord[i][0];
		dy1=coord[i][1];
		dx2=coord[i][2];
		dy2=coord[i][3];
		

		if(dx1==dx2){
			while(dy1!=dy2+1){
				matris[dy1][dx1]=dict[counter][word];
				word++;
				dy1++;	

			}

		}

		else if(dy1==dy2){
			while(dx1!=dx2+1){
				matris[dy1][dx1]=dict[counter][word];
				printf("matris:%c ",matris[dx1][dy1]);
				word++;
				dx1++;
			}
		}
		else{
			while(dx1!=dx2+1 && dy1!=dy2+1){
				matris[dy1][dx1]=dict[counter][word];
				word++;
				dx1++;
				dy1++;
			}
		}
		counter++;
		word=0;
	}
	printf("its okey\n");

	find(matris,coord);

	

		
		

}

void print_matris(char matris[][15]){
	int i,j;
	for(i=0;i<15;i++){
		for(j=0;j<15;j++){
			printf("%c ",matris[i][j] );
		}
		printf("\n");
	}
}



