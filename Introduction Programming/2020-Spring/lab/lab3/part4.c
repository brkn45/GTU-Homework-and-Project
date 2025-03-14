#include <stdio.h>
int check_prime(int a);

int main(){
	char choice=0;
	int number=0,flag=0 ,i=2 ,counter=0;
	printf("a. Is ,t prime or not\nb. Nth prime Number");
	printf("please select the option from menu:\n");
	scanf("%c",&choice);
	printf("Enter a positive number");
	scanf("%d",&number);

	switch (choice) {
		case 'a':
		flag=check_prime(number);
		if(flag==0){
			printf("%d is not prime number\n",number );
		}
		else{
			printf("%d i prime number \n",number);
		}
		break;
		case 'b':
		while(number!=counter){
			flag=check_prime(i);
			if(flag==1){
				printf("%d\n",i );
				counter++;
			}
			i++;
		}
	}


}
int check_prime(int number){
	int i=0, j=0 ,flag=1;
	for(i=2;i<number;i++){
		if(number%i==0){
			flag=0;
		}
	}
	return flag;
}