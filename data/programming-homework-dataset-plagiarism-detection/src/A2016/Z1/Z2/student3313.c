#include <stdio.h>

int main() 
{
	float a1, b1, a2, b2;
	printf("Unesite a1,b1,a2,b2: ");
	scanf("%f,%f,%f,%f",&a1,&b1,&a2,&b2);
	if(a1==a2 && b1==b2)
		printf("Poklapaju se");
	else if(a1==a2)
		printf("Paralelne su");
	else
	{
		printf("Prave se sijeku");
		float x, y;
		x=(b2-b1)/(a1-a2);
		y=a1*x+b1;
		printf (" u tacci (%.1f,%.1f)",x,y);
	}
	return 0;
}
