#include <stdio.h>

int main() {
	int i,j,n;
	
	do {
	printf("Unesite broj N: ");
	scanf("%d",&n);
	if (n%4!=0 || n<8) {
		printf("Neispravno N!\n");
	}
		
	} while (n%4!=0 || n<8);
	
	printf("\n");
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j && j<n/2) {
				printf("\\");
			}
			else if (i==n/2-j-1) {
				printf("/");
			}
			else if((i==n/2 && j==0) || (i==n/2 && j==n/2-1) || (i==n-1 && j==0) || (i==n-1 && j==n/2-1)) {
		printf("+");
		}
		else if((i==n/2 || i==n-1) && (j>0 && j<n/2)) {
			printf("-");
		}
		else if((j==0 || j==n/2-1) && (i>n/2 && i<n-1)) {
			printf("|");
		}
	    else if((i==0 && j==n/2) || (i==0 && j==n-1) || (i==n/2-1 && j==n/2) || (i==n/2-1 && j==n-1)) {
		printf("+");
		}
		else if((i==0 || i==n/2-1) && (j>n/2 && j<n-1)) {
			printf("-");
		}
		else if((j==n/2 || j==n-1) && (i>0 && i<n/2-1)) {
			printf("|");
		}
		
		else if(((i>=n/2 && i<3*n/4-1) || (i>3*n/4 && i<n)) && (j==3*n/4 || j==3*n/4-1)) {
			printf("|");
		}
		else if(((j>=n/2 && j<3*n/4-1) || (j>3*n/4 && j<n)) && (i==3*n/4 || i==3*n/4-1)) {
			printf("-");
		}
		else if((i==3*n/4 && j==3*n/4) || (i==3*n/4 && j==3*n/4-1) || (i==3*n/4-1 && j==3*n/4) || (i==3*n/4-1 && j==3*n/4-1)) {
			printf("+");
		}
	
			else {
				printf(" ");
			}
		}
		
		
		printf("\n");
	}
	


	return 0;
}
