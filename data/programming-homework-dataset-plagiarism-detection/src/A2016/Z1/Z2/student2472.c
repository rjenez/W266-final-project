#include <stdio.h>
#define E 0.0001
#include <math.h>

int main() {
	float a1, a2, b1, b2, y, x;
	printf("Unesite a1,b1,a2,b2: ");
	scanf("%f, %f, %f, %f", &a1, &b1, &a2, &b2);
	if (fabs(a1-a2)<E && fabs(b1-b2)<E){
		printf("Poklapaju se");
		return 0;
	}else if (fabs(a1-a2)<E && fabs(b1-b2)>E){
		printf("Paralelne su");
		return 0;
		
	}
	x=(b2-b1)/(a1-a2);
	y=a1*(b2-b1)/(a1-a2)+b1;
	printf("Prave se sijeku u tacci (%.1f,%.1f)", x, y);
	
	return 0;
}
