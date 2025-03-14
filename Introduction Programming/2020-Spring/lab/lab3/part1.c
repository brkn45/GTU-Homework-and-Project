#include <stdio.h>

int main(){
	int num1=0, num2=0, i=0;
	printf("Enter first number\n");
	scanf("%d",&num1);
	printf("Enter second number\n");
	scanf("%d",&num2);

	for(i=1;i<=num2;i++){
		printf("%d*%d =%d\n",num1,i,num1*i );
	}
}