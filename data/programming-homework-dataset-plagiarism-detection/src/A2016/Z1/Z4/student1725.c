#include <stdio.h>

int main() {
    int i,j,n;
    
    printf("Unesite broj n: ");
    scanf("%d", &n);
    
    while((n<1) || (n>50)) {
    	printf("Pogresan unos\n");
    	printf("Unesite broj n: ");
    	scanf("%d", &n); }
    	
    	if(n==1) printf("***"); 
    	
    	else {  
    	    for(i=1;i<=n;i++) {
    	        for(j=1;j<=(4*n-3);j++) {
    	            if((i==j) || (j-i==2*n-2) || (i+j==2*n) || (i+j==4*n-2)) printf("*");
    	            else printf(" "); 
    	        }
    	        printf("\n");
    	    } }
    	
    	
    	
	return 0;
}
