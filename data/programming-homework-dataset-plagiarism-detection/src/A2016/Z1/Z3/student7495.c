#include <stdio.h>

int main(){
    char n;
    int b, br,brc,brb,brs,brv,brp;
    float pc,pb,ps,pv,pp;
    brc=0;
    brs=0;
    brb=0;
    brp=0;
    brv=0;
    printf ("Unesite vozila: ");
    do{
        scanf ("%d", &n);
        if (n=='c' || n=='C'){
            brc++;
        }
        else if (n=='s' || n=='S'){
            brs++;
        }
        else if (n=='v' || n=='V'){
            brv++;
        }
        else if (b=='p' || n=='P'){
            brp++;
        }
        else if (n=='k' || n=='K'){
            break;
        }
        else printf ("\n Neispravan unos");
        
        
        
    }
    while (1) ;
    br=brc+brb+brs+brv+brp;
    pc=((float) brc/br)*100;
    pb=((float) brb/br)*100;
    ps=((float) brs/br)*100;
    pv=((float) brv/br)*100;
    pp=((float) brp/br)*100;
    
    printf ("Ukupno evidentiranih %d vozila \n ", br);
    if(brc>brb && brc>=brs && brc>=brv && brc>=brp && br!=0){
        printf ("Najpopularnija boja je crna (%.2f%%).", ps);
    }
    else if (brv>brc && brv>=brs && brv>=brb && brv>=brp){
        printf("Najpopularnija boja je crvena (%.2f%%).",pb);
    } 
    else if (brb>brc && brb>=brs && brb>=brv && brb>=brp){
        printf ("Najpopularnija boja je bijela (%.2f%%).", pb);
    }
    else if (brb>brc && brb>=brs && brb>=brv && brb>=brp){
        printf("Najpopularnija boja je siva (%.2f%%).",ps);
    }
    else if (br==0){
        printf ("Najpopularnija boja je crna (0.00%%).");
    }
    
    return 0;
}