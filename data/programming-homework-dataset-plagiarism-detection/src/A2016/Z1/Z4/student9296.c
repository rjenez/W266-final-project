#include <stdio.h>

int main() {
	
	int i, j, n;
	
	printf("Unesite broj n: ");
	scanf("%i", &n);
	
	
	while(n<=0 || n>50)
	{
		printf("Pogresan unos\n");
		
		printf("Unesite broj n: ");
		scanf("%i", &n);
		
	}
	
	if(n==1)
	{
		printf("***");
		return 0;
	}
	
	for(i=0; i<n; i++)
	{
		
		for(j=0; j<4*n-3; j++)
		{
			if(i==j || i+j==(4*n-3)/2 || j-i==(4*n-3)/2 || i+j==4*n-4)
			
			{
				printf("*");
			}
			else printf(" ");
		}
		
		printf("\n");
	}
	
	return 0;
}
