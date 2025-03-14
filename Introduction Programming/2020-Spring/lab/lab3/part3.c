#include <stdio.h>
int fact(int num);
int combination(int m, int n);
int permutation(int m,int n);
int main(){
	int num1=0, num2=0 ,result_c=0, result_p=0;
	printf("Enter a Number\n");
	scanf("%d",&num1);
	printf("Enter a Secoun number\n");
	scanf("%d",&num2);
	result_c=combination(num1,num2);
	result_p=permutation(num1,num2);
	printf("C(%d,%d)=%d\n",num1,num2,result_c );
	printf("P(%d,%d)=%d\n",num1,num2,result_p );
}

int fact(int num){
	int i=0,result=1;
	for(i=1;i<=num;i++){
		result=result*i;
	}
	return result;

}

int combination(int m,int n){
	int result=0;

	result=fact(m)/(fact(m-n)*fact(n));
	return result;

}
int permutation(int m,int n){
	int result=0;

	result=fact(m)/fact(m-n);
	return result;
}