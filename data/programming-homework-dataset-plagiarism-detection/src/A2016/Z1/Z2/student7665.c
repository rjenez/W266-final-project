#include <stdio.h>
#include<math.h>
#define EPSILON 0.001


int main() {
	float a1,y1,x,b1,a2,b2;
	printf("Unesite a1,b1,a2,b2: "); scanf("%f,%f,%f,%f", &a1, &b1, &a2,&b2);
	if(fabs(a1-a2)<EPSILON && fabs(b1-b2)>EPSILON){
		printf("Paralelne su");
		return 0;
	}
	if(fabs(a1-a2)<EPSILON && fabs(b1-b2)<EPSILON){
		printf("Poklapaju se");
		return 0;
	}
	else{
		x=(b2-b1)/(a1-a2);
		y1=a1*x+b1;
		printf("Prave se sijeku u tacci (%2.1f,%2.1f)", x,y1);
		return 0;
	}
	
}
