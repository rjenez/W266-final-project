#include <stdio.h>

int main() {

int n,i,j;

do {
    
	printf("Unesite broj N: ");

	scanf("%d", &n);
	if(n<0 || n%4!=0 || n<8 )
	printf("Neispravno N!\n");
	
} while ( n%4!=0 || n<8 );

printf("\n");
/*prvikv*/
for(i=0; i<n/2; i++)
{
for(j=0; j<n; j++)
{
    
if(i==j)
printf("\\");

else if (j==n/2-1-i)
printf("/");


else if(i==n/2-1 && (j==n-1 || j==(n/2)) )
printf("+");

else if(i==0 && (j==n-1 || j==(n/2)) )
printf("+");

else if ( (i==n/2-1 || i==0) && j>n/2 )
printf("-");

else if( j==n-1 || j==n/2 )
printf("|");

else
printf(" ");


}
printf("\n");
}



/*treci i 4*/

for(i=n/2; i<n; i++)
{
for(j=0; j<n; j++)
{
    
if(i==n/2 && (j==0 || j==(n/2)-1) )
printf("+");

else if(i==n-1 && (j==0 || j==(n/2)-1) )
printf("+");

else if ((i==n/2 || i==n-1) && j<n/2 )
printf("-");

else if( j==0 || j==n/2 -1)
printf("|");

else if( (i==(3*n)/4 && j==(3*n)/4) || (i==((3*n)/4-1) && j==((3*n)/4-1) )  || (i==((3*n)/4)-1 && j==(3*n)/4) || (i==(3*n)/4 && j==(3*n)/4-1))
printf("+");


else if( (i!=(3*n)/4 && j==(3*n)/4) || (i!=((3*n)/4-1) && j==((3*n)/4-1) ) )
printf("|");

 else if ( ((i==((3*n)/4)-1 && j!=(3*n)/4) || (i==(3*n)/4 && j!=(3*n)/4-1) ) && j>=n/2)
printf("-");

else
printf(" ");


}
printf("\n");
}














	return 0;
        }
