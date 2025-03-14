#include <stdio.h>
int is_perfect(int number);

int main(){
	int number=0,flag=0;
	printf("Enter the number\n");
	scanf("%d",&number);
	flag=is_perfect(number);
	if(flag==1)
		printf("%d is perfect number\n",number);
	else
		printf("%d is not perfect number\n",number );
}
int is_perfect(int number){
	int i=0, flag=0,sum=0;

	for(i=1;i<number;i++){
		if(number%i==0){
			sum=sum+i;
		}
	}
	return (sum==number);
}