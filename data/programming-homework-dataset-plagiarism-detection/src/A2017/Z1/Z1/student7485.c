#include <stdio.h>

int main() {
	float pr=6.80,pf=8.00,pb=5.30,hr=3.30,hf=3.00,hb=5.00,cr=5.00,cf=3.90,cb=6.00,sumaR=0,sumaR2=0,sumaF=0,sumaB=0,nova_cijena=0;
	char tarik,bojan,mirza,novi_red,novo_jelo='\0';
	printf("Unesite jelo za Tarika: ");
	scanf("%c",&tarik);
	scanf("%c",&novi_red);
	printf("Unesite jelo za Bojana: ");
	scanf("%c",&bojan);
	scanf("%c",&novi_red);
	printf("Unesite jelo za Mirzu: ");
	scanf("%c",&mirza);
	
	
	if ((tarik=='P' && bojan=='P') || (tarik=='P' && mirza=='P') || (bojan=='P' && mirza=='P') || (tarik!=bojan && tarik!=mirza && bojan!=mirza))
		{
		nova_cijena=pr-pr*0.1;
		novo_jelo='P';
		}
	else if ((tarik=='H' && bojan=='H') || (tarik=='H' && mirza=='H') || (bojan=='H' && mirza=='H'))
			
	{
		nova_cijena=hr-hr*0.1;
		novo_jelo='H';
	}	
	else if ((tarik=='C' && bojan=='C') || (tarik=='C' && mirza=='C') || (bojan=='C' && mirza=='C'))
	{
		nova_cijena=cr-cr*0.1;
		novo_jelo='C';
	}
	if (tarik=='P')
	{
		sumaR+=pr;
		sumaF+=pf;
		sumaB+=pb;
		if (novo_jelo=='P')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=pr;
	}
	else if (tarik=='H')
	{
		sumaR+=hr;
		sumaF+=hf;
		sumaB+=hb;
		if (novo_jelo=='H')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=hr;	
	}
	else if (tarik=='C')
	{
		sumaR+=cr;
		sumaF+=cf;
		sumaB+=cb;
		if (novo_jelo=='C')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=cr;	
	}
	
	if (bojan=='P')
	{
		sumaR+=pr;
		sumaF+=pf;
		sumaB+=pb;
		if (novo_jelo=='P')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=pr;
	}
	else if (bojan=='H')
	{
		sumaR+=hr;
		sumaF+=hf;
		sumaB+=hb;
		if (novo_jelo=='H')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=hr;
	}
	else if (bojan=='C')
	{
		sumaR+=cr;
		sumaF+=cf;
		sumaB+=cb;
		if (novo_jelo=='C')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=cr;
	}

	if (mirza=='P')
	{
		sumaR+=pr;
		sumaF+=pf;
		sumaB+=pb;
		if (novo_jelo=='P')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=pr;
	}
	else if (mirza=='H')
	{
		sumaR+=hr;
		sumaF+=hf;
		sumaB+=hb;
		if (novo_jelo=='H')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=hr;
	}
	else if (mirza=='C')
	{
		sumaR+=cr;
		sumaF+=cf;
		sumaB+=cb;
		if (novo_jelo=='C')
			sumaR2+=nova_cijena;
		else 
			sumaR2+=cr;
	}
	if (sumaR<sumaF && sumaR<sumaB)
		printf("Najjeftiniji je Restoran \"Kod konja i konjusara\" (%.2f KM).",sumaR);
	else if (sumaF<sumaR && sumaF<sumaB)
		printf("Najjeftiniji je Fast-food \"Trovac\" (%.2f KM).",sumaF);
	else if (sumaB<sumaR && sumaB<sumaF)
		printf("Najjeftiniji je Bistro \"Lorelei\" (%.2f KM).",sumaB);
		
	if (sumaR>sumaF || sumaR>sumaB)
	{
		if (sumaR2<sumaF && sumaR2<sumaB)
			printf("\nSa popustom bi Restoran bio jeftiniji (%.2f KM).",sumaR2);
	}
	return 0;
}
