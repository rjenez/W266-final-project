 printf (" Unesite a, dimenzijun \n" );#include <stdio.h>#include <stdio.h>
#include <math.h>
int main() {
	float a1,a2,b1,b2,x,y;
	printf("Unesite a1,b1,a2,b2: ");
	scanf("%f,%f,%f,%f",&a1,&b1,&a2,&b2);
	if(a1==a2 && b1!=b2) {printf("Paralelne su"); return 0;}
	else if(a1==a2 && b1==b2) {printf("Poklapaju se"); return 0;}
	x=(b2-b1)/(a1-a2);
	y=a1*x+b1;
	printf("Prave se sijeku u tacci (%.1f,%.1f)",x,y);
	return 0;
}