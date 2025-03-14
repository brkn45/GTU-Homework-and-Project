#include <stdio.h>
#include <math.h>

int number_length(int number); // find  number length
int find_digit(int number, int index); // find number digit

int main(){
	int number=0, digit=0 ,index=0 ;
	printf("Enter a number.(maximum 6 digits)\n");
	scanf("%d",&number);
	digit=number_length(number);
	printf("Your number has %d digits\n",digit);
	if(digit>6){
		printf("Your number larger than six digit\n");
		return 0;
	}
	
	printf("When your number is written 100 times next to each order,which digit of the this number would you like to see?:\n");
	scanf("%d",&index);
	digit=find_digit(number,index);
	printf("%d.th digit of the big numer sequence:%d\n",index,digit );

	return 0;
	
}

int number_length(int number){
	int digit=0;

	digit=(int)log10((double)number);
	return digit +1;
}
int find_digit(int number,int index){ // find digit
	int digit=0 , length=0;
	length=number_length(number);
	index=index+length; // if index is more than small to six , remeander equal 0. so add to number lenght
	index=index%length; //
	if(index !=0){ 
		index=length-index;
	}

	number=number/(int)pow(10.0,(double)index);
	digit=number%10;

	return digit;

}
