#include <stdio.h>

int main() {
	int n,j,i,tacno=0;
	do{
		printf("Unesite broj N: ");
		scanf("%d",&n);
		if(n%4==0 && n>=8)
		{
			tacno=1;
		}else printf("Neispravno N!\n");
		printf("\n");
		
	}while(tacno!=1);
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i<n/2 && j<n/2)
			{
				if(i==j)
				{
					printf("\\");
				}
				else if(i+j==((n-2)/2))
				{
					printf("/");
				}
				else printf(" ");
			}
			if(i<n/2 && j>=n/2)
			{
				if((j==n/2 || j==n-1) && (i==0 || i==((n/2)-1)))
				{
					printf("+");
				}
				else if(i==0 || i==((n/2)-1))
				{
					printf("-");
				}
				else if(j==n/2 || j==n-1)
				{
					printf("|");
				}
				else printf(" ");
			}
			if(i>=n/2 && j<n/2)
			{
				if((j==0 || j==((n/2)-1)) && (i==n/2 || i==n-1))
				{
					printf("+");
				}
				else if(i==n/2 || i==n-1)
				{
					printf("-");
				}
				else if(j==0 || j==((n/2)-1))
				{
					printf("|");
				}
				else printf(" ");
			}
			if(i>=n/2 && j>=n/2)
			{
				if((i==(n-n/4) && j==(n-n/4)) || (i==(n-1-n/4) && j==(n-1-n/4)) || (i==(n-1-n/4) && j==(n-n/4)) || (i==(n-n/4) && j==(n-1-n/4)))
				{
					printf("+");
				}
				else if((i==(n-n/4) || i==n/4-1) || (i==(n-1-n/4) || i==n/4-1))
				{
					printf("-");
				}
				else if((j==(n-n/4) || j==n/4-1) || (j==(n-1-n/4) || j==n/4-1))
				{
					printf("|");
				}
				else printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}