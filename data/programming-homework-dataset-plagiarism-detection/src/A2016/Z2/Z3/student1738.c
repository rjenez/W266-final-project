#include <stdio.h>
#define a 20

int main() 
{
	int k,x,y,bt,j,i;
	char matrix[a][a]={    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}, {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},      {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},                {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}                         };
	int redovi[21],kolone[21];
	n1:printf ("Unesite broj tacaka: ");
	scanf ("%i",&bt);
	
	if (bt>10 || bt<=0)
	{
		printf ("Pogresan unos\n");
		goto n1;
	}
	
	for (i=0;i<bt;i++)
	{
		n2:printf ("Unesite %i. tacku: ",i+1);
		scanf ("%i",&x);
		scanf ("%i",&y);
		if (x<0 || y<0 || x>19 || y>19)
		{
			printf ("Pogresan unos\n");
			goto n2;
		}
		else 
		{
			redovi[i]=y;
			kolone[i]=x;
		}
		
	}
	
	for (k=0;k<bt;k++)
	{
		for (i=0;i<20;i++)
		{
			for (j=0;j<20;j++)
			{
				if (redovi[k]==i && kolone[k]==j)
				{
					matrix [i][j]='*';
				}
			}
		}
		
	}
	
	for (i=0;i<20;i++)
	{
		for (j=0;j<20;j++)
		{
			printf ("%c",matrix[i][j]);
		}
		printf ("\n");
	}
	
	return 0;
}
