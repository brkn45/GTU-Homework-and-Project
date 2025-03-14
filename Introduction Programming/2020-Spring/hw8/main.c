#include <stdio.h>
#include <math.h>
#define N 8
#define ARRAY_SIZE 500

void menu();
void part1(); // for part1 menu
int generate_hofstadters_sequence (int *arr, int n); 
int find_max (int arr[], int index, int max_value); // find max value
 int sum_array (int arr[]);// calculate sum array elements 
double std_array (int arr[], double *mean, int n, int index); 
char *remove_duplicates (char* str); // remove dublicate character
void install_pipes (int visited[N][N], int x, int y, int orientation,int *counter); // fill l shape in array 
void wr(int visited[N][N]); // write array
void write_ori(int visited[N][N],int num); // write orientit
int is_okey(int x, int y);//  is era empty
int main(){
 menu();
}
void menu(){ 
	int choice=0;
	char str[ARRAY_SIZE];
	int x,y,orientation, visited[N][N]={0},counter=0;

	while(choice!=4){
		printf("\n1) Exacute part 1\n");
		printf("2) Exacute part 2\n");
		printf("3) Exacute part 3\n");
		printf("4) Exit\n");
		scanf("%d",&choice);	
		switch (choice){
			case 1:
				part1();
				break;
			case 2:
				install_pipes(visited,0,0,1,&counter);
				break;
			case 3:
				printf("Enter a string \n");
				scanf(" %[^\n]",str);
				remove_duplicates (str);
				
				printf("%s\n",str );	
				break;
			case 4:
				break;
			default :
				printf("Again Enter Number\n");
				break;		
		}
	}
}
void install_pipes (int visited[N][N], int x, int y, int orientation,int *counter){
	
	if(*counter==10)
		return;
	visited[x][y]=orientation;
	
	if(orientation>=64){
		wr(visited);
		printf("\n\norientation %d:",*counter +1);
		write_ori(visited,1);
		*counter=*counter+1;
		
		visited[x][y]=0;
		return;
	}
	
	if (is_okey(x+2, y+1) && visited[x+2][y+1]==0){
		install_pipes(visited, x+2, y+1,orientation+1, counter );
		
	}
	if (is_okey(x+1, y-2) && visited[x+1][y-2]==0){
		install_pipes(visited, x+1, y-2,orientation+1, counter );
	}

	if (is_okey(x-2, y-1) && visited[x-2][y-1]==0){
		install_pipes(visited, x-2, y-1,orientation+1, counter );
	}
	if (is_okey(x-1, y+2) && visited[x-1][y+2]==0){
		install_pipes(visited, x-1, y+2,orientation+1, counter );
	}

	if (is_okey(x+1, y+2) && visited[x+1][y+2]==0){
		install_pipes(visited, x+1, y+2,orientation+1, counter );
	}

	if (is_okey(x+2, y-1) && visited[x+2][y-1]==0){
		install_pipes(visited, x+2, y-1,orientation+1, counter);
	}
	if (is_okey(x-1, y-2) && visited[x-1][y-2]==0){
		install_pipes(visited, x-1, y-2,orientation+1, counter );
	}

	if (is_okey(x-2, y+1) && visited[x-2][y+1]==0){
		install_pipes(visited, x-2, y+1,orientation+1, counter );
	}
	visited[x][y]=0;

}
void write_ori(int visited[N][N],int num){ // wirite orientation
	int x,y;
	int i=0,j=0;
	if(num==65)
		return;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(num==visited[i][j]){
				x=i;
				y=j;
			}
		}
	}

	
	if (visited[x+2][y+1]==num+1){
		printf("O%d ",1 );
		write_ori(visited,num+1);
	}
	
	else if (visited[x+1][y-2]==num+1){
		printf("O%d ", 2);
		write_ori(visited,num+1);
		}

	else if (visited[x-2][y-1]==num+1){
		printf("O%d ", 3);
		write_ori(visited,num+1);
		}
	else if (visited[x-1][y+2]==num+1){
		printf("O%d ",4 );
		write_ori(visited,num+1);
		}

	else if (visited[x+1][y+2]==num+1){
		printf("O%d ",5 );
		write_ori(visited,num+1);
		}

	else if ( visited[x+2][y-1]==num+1){
		printf("O%d ",6 );
		write_ori(visited,num+1);

	}
	else if (visited[x-1][y-2]==num+1){
		printf("O%d ", 7);
		write_ori(visited,num+1);
	}

	else if (visited[x-2][y+1]==num+1){
		printf("O%d ", 8);
		write_ori(visited,num+1);

	}

}
int is_okey(int x,int y){
	if (x < 0)
		return 0;
	if( y < 0 )
		return 0;
	if (x >= 8) 
		return 0; 
	if( y >= 8)
		return 0;

	return 1;
}
void wr(int visited[N][N]){ 
	int i=0,j=0;
	printf("\n\n");
	for ( i = 0; i < N; ++i){
		for(j=0;j<N;j++){
			printf("%d ",visited[i][j] );
		}
		printf("\n");
	}
}

char* remove_duplicates (char* str){ // remove dublicate characters

    if (str[0] == '\0') 
        return str; 
    
    if (str[0] == str[1] || str[0]=='*') { 
        str[0]='*';
        if(str[1]=='\0'){
        	str[0]=str[1];
        	return str;
        }
        else{
        	str[0]=str[1];	
        	str[1]='*';
        }
    } 
	remove_duplicates(str + 1); //sometimes the characters can repeat so I call the function twice
    remove_duplicates(str +1); 

}
void part1(){
	int choice=0,arr[500]={0},n=0,max_value=0,result=0,index=0;
	int *p;

	double std=0.0,mean=0.0,average=0.0;
	while(choice!=5){
		printf("Plaese make your choice\n");
		printf("------------------------\n");
		printf("1) Fill Array\n");
		printf("2) Find Bigest Number\n");
		printf("3) Calculate Sum\n");
		printf("4) Calculate Standart Deviation\n" );
		printf("5) Exit\n");
		scanf("%d",&choice);
		switch (choice){
			case 1:
				printf("please enter n value\n");
				scanf("%d",&n);
				generate_hofstadters_sequence(arr,n);
				
				/*for(int i=0;i<500;i++){
					printf("%d Num:%d\n",i,arr[i] );
				}*/
				break;
			case 2:
				max_value=find_max(arr,n-1	,max_value);
				printf("max_value : %d\n",max_value );
				break;	
			case 3:
				result=sum_array (arr);
				printf("Sum :%d\n",result );
				
				break;
			case 4:
				std=sqrt(std_array(arr,&mean,n,0));
				printf("Standard Deviation:%lf\n",std );
				break;
			case 5:
				break;	

		}
	}
	
}
double std_array (int arr[], double *mean, int n, int index){ // mean return average and std array return standard deviation variance
	
	if(arr[index]==0){
		if(arr[1]==0){
			return (*mean-(double)arr[0])*(*mean-(double)arr[0])/(double)(n-1);
		}
		else {
			return  (*mean-(double)arr[0])*(*mean-(double)arr[0])/(double)(n-1)+std_array(arr+1,mean,n,index);
		}	

	}
	else{
		*mean = (*mean +arr[index]);
		if(arr[index+1]==0)
			*mean=*mean/(double)n;
		return std_array(arr,mean,n,index+1);
 	}
 	 
 	
}
int sum_array (int arr[]){ // sum array
	if(arr[0]==0)
		return  0;
	else
		return arr[0]+ sum_array(arr+1);
	
	
}
int find_max (int arr[], int index, int max_value){ // find max value in array
	if (index == 0)
            return max_value;
 
        if (index > 0) 
        {
            if (arr[index] > max_value)
            {
                max_value = arr[index];
            }
            return find_max(arr, index - 1, max_value);
        }
}
int generate_hofstadters_sequence (int *arr, int n){ // calculate each generete holfsadters sequence number
 	int result=0,i=1;
 	arr[0]=1;
   if (n < 3) 
    	result = 1;
    else
     result=generate_hofstadters_sequence(arr,n-(generate_hofstadters_sequence(arr,n-1)))+generate_hofstadters_sequence(arr,n-(generate_hofstadters_sequence(arr,n-2)));

    arr[n-1] = result;
    return result;
}
 	

 	
 	
 	




