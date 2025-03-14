#include <stdio.h>
#include <math.h>

int draw_triangle(int side1,int side2, int side3); // find can draw or cant draw
void type_triangle(int side1,int side2, int side3); // find a triangular type
int perimeter_triangle(int side1,int side2, int side3); // calculate perimeter
double area_triangle(int side1,int side2, int side3,int perimeter); // calculate area
int absulute_value(int num);


int main(){
	int side1, side2 ,side3 , flag, perim;
	double area;
	printf("The lenght of first side\n");
	scanf("%d",&side1);
	printf("The lenght of second side\n");
	scanf("%d",&side2);
	printf("The lenght of third side\n");
	scanf("%d",&side3);
	flag=draw_triangle(side1,side2,side3);
	
	if(flag==1){
		printf("According to the triangle inequality theorem, this triangle can be drawn.\n");
	}
	else{
		printf("According to the triangle inequality theorem, this triangle cannot be drawn.\n");
	}
	
	type_triangle(side1,side2,side3);
	perim=perimeter_triangle(side1,side2,side3);
	printf("The perimeter of triangle:%d\n",perim);
	area=area_triangle(side1,side2,side3,perim);
	printf("Area of triangle:%lf\n",area );
}

int draw_triangle(int side1,int side2, int side3){ 

	int flag=0; // flag is controll triangular  
	if(absulute_value(side1-side2)< side3 && (side1+side2) > side3){
		flag++;
	}
	if(absulute_value(side1-side3) < side2 && (side1 + side3) > side2){
		flag++;
	}
	if(absulute_value(side2-side3) < side1 && (side2 + side3) > side1){
		flag++;
	}

	return (flag==3);
}

int absulute_value(int num){ // 2 side diffrence between chance pozitif number
	if(num<0){
		return -num;
	}
	else
		return num;
}

void type_triangle(int side1,int side2, int side3){ // find triangular type 
	int flag=0;
	if(side1==side2)
		flag++;
	
	if(side1==side3)
		flag++;
	
	if(side2==side3)
		flag++;

	if(flag==3){
		printf("It is a equilateral triangle\n");
	}
	else if(flag==1){
		printf("It is a isosceles triangle\n");
	}
	else{
		printf("It is a scalene triangle\n");
	}
}
int perimeter_triangle(int side1,int side2, int side3){ // find perimeter
	int perim=0;
	perim=side1 + side2 +side3;
}
double area_triangle(int side1, int side2, int side3 ,int perimeter){ // find area triangular
	double area=0,half_perim=0;
	half_perim=perimeter/2;

	area=sqrt(half_perim*(half_perim-side1)*(half_perim-side2)*(half_perim-side3));
	return area;

}