//by Denis..
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define EPS 0.001
enum TipOblika {TACKA,KRUZNICA,PRAVOUGAONIK,TROUGAO};
struct Tacka {
	float x;
	float y;
};
struct Kruznica {
	struct Tacka centar;
	float radijus;
};
struct Pravougaonik {
	struct Tacka donji_lijevi;
	float sirina,visina;
};
struct Trougao {
	struct Tacka prvi_vrh,drugi_vrh,treci_vrh;
};
struct Tacka unesi_tacku()
{
	struct Tacka t;
	printf ("koordinate x,y: ");
	scanf ("%f,%f", &t.x, &t.y);
	return t;
}
struct Kruznica unesi_kruznicu ()
{
	struct Kruznica k;
	printf ("Unesite centar kruznice: ");
	k.centar=unesi_tacku();
	printf ("Unesite poluprecnik kruznice: ");
	scanf ("%f",&k.radijus);
	return k;
}
struct Pravougaonik unesi_pravougaonik()
{
	struct Pravougaonik p;
	printf ("Unesite donji lijevi ugao: ");
	p.donji_lijevi=unesi_tacku();
	printf ("Unesite sirinu: ");
	scanf ("%f",&p.sirina);
	printf ("Unesite visinu: ");
	scanf ("%f",&p.visina);
	return p;
}
struct Trougao unesi_trougao ()
{
	struct Trougao tr;
	printf ("Unesite prvi vrh: ");
	tr.prvi_vrh=unesi_tacku();
	printf ("Unesite drugi vrh: ");
	tr.drugi_vrh=unesi_tacku();
	printf ("Unesite treci vrh: ");
	tr.treci_vrh=unesi_tacku();
	return tr;
}
float udaljenost (struct Tacka t1,struct Tacka t2)
{
	return sqrt (((t1.x-t2.x)*(t1.x-t2.x)) + ((t1.y-t2.y)*(t1.y-t2.y)));
}
float povrsina (struct Tacka t1,struct Tacka t2,struct Tacka t3)
{
	float pov;
	pov=(t1.x*(t2.y-t3.y)+t2.x*(t3.y-t1.y)+t3.x*(t1.y-t2.y))/2;
	if (pov<0)
		pov=-pov;
	return pov;
}
int tacka_u_kruznici (struct Kruznica* k, struct Tacka t)
{
	if (udaljenost(k->centar,t)<=k->radijus)
		return 1;
	return 0;
}
int tacka_u_pravougaoniku (struct Pravougaonik* p,struct Tacka t)
{
	/*Funkcija prima pravougaonik, i formira uz pomoc visine i sirine i jedne tacke, i one ostale tri*/
	/*Provjeravamo da li se neka tacka,nalazi unutar pravougaonika omedjenog sa ove cetiri tacke*/
	struct Tacka tp;
	tp.x=p->donji_lijevi.x+p->sirina;
	tp.y=p->donji_lijevi.y+p->visina;
	if (t.x>=p->donji_lijevi.x && t.x<=tp.x && t.y>=p->donji_lijevi.y && t.y<=tp.y)
		return 1;
	return 0;

}
int tacka_u_trouglu (struct Trougao* tr,struct Tacka t)
{
	/*Formiramo tri trougla,od kojih svaki sadrzi neku tacku za koju zelimo da provjerimo je li u trouglu*/
	/*Racunamo povrsine trouglova koji sadrze ovu tacku,i dva tjemena trougla,uvijek razlicita*/
	/*Ako je zbir tih povrsina jednak povrsini trougla,tacka je u trouglu*/
	float A1,A2,A3,Au,At;
	A1=povrsina(tr->prvi_vrh,tr->drugi_vrh,t);
	A2=povrsina(tr->prvi_vrh,tr->treci_vrh,t);
	A3=povrsina(tr->drugi_vrh,tr->treci_vrh,t);
	Au=A1+A2+A3;
	At=povrsina(tr->prvi_vrh,tr->drugi_vrh,tr->treci_vrh);
	if (abs(At-Au)<EPS)
		return 1;
	return 0;

}
int tangenta_na_kruznicu (struct Tacka t1,struct Tacka t2,struct Kruznica k)
{
	/*Da bismo znali da se kruznica sigurno nalazi u trouglu, niti jedna prava formirana od svaka dva tjemena trougla, ne smije dodirivati kruznicu u vise od jedne tacke*/
	/*Iz uslova dodira,mozemo znati kakav ce biti polozaj kruznice u trouglu*/
	float r=k.radijus;
	float p=k.centar.x,q=k.centar.y;
	float m,n;
	float v;
	/*Za slucaj da je neka tangenta vertikalna,imamo posebni uslov,da ne bismo dosli u situaciju da dijelimo s nulom*/
	if (abs(t1.x-t2.x)<=EPS) {
		v=t1.x;
		if (v<k.centar.x) {
			if (k.centar.x-v>k.radijus)
				return 1;
			return 0;
		} else {
			if (v-k.centar.x>k.radijus)
				return 1;
			return 0;
		}
	}
	m=(t1.y-t2.y)/(t1.x-t2.x);
	n=t1.y-m*t1.x;
	if (r*r*(m*m+1)-(-(m*p)+q-n)*(-(m*p)+q-n)<=0)
		return 1;
	return 0;
}

int  obuhvata (void* oblik1, enum TipOblika to1, void* oblik2, enum TipOblika to2)
{
	struct Tacka* t1;
	struct Tacka* t2;
	struct Kruznica* k1;
	struct Kruznica* k2;
	struct Pravougaonik* p1;
	struct Pravougaonik* p2;
	struct Trougao* tr1;
	struct Trougao* tr2;
	if (to1==TACKA)
		t1=(struct Tacka*)oblik1;
	else if (to1==KRUZNICA)
		k1=(struct Kruznica*)oblik1;
	else if (to1==PRAVOUGAONIK)
		p1=(struct Pravougaonik*)oblik1;
	else if (to1==TROUGAO)
		tr1=(struct Trougao*)oblik1;
	if (to2==TACKA)
		t2=(struct Tacka*)oblik2;
	else if (to2==KRUZNICA)
		k2=(struct Kruznica*)oblik2;
	else if (to2==PRAVOUGAONIK)
		p2=(struct Pravougaonik*)oblik2;
	else if (to2==TROUGAO)
		tr2=(struct Trougao*)oblik2;
	if (to1==KRUZNICA) {
		if (to2==PRAVOUGAONIK) {
			/*Formiramo sva 4 tjemena pravougonika,i ako se oni nalaze u kruznici,znaci da je i pravougaonik u njoj*/
			struct Tacka pr1,pr2,pr3;
			pr1.x=p2->donji_lijevi.x;
			pr1.y=p2->donji_lijevi.y+p2->visina;
			pr2.x=p2->donji_lijevi.x+p2->sirina;
			pr2.y=p2->donji_lijevi.y;
			pr3.x=p2->donji_lijevi.x+p2->sirina;
			pr3.y=p2->donji_lijevi.y+p2->visina;
			if (tacka_u_kruznici(k1,pr1) && tacka_u_kruznici(k1,pr2) && tacka_u_kruznici(k1,pr3) && tacka_u_kruznici(k1,p2->donji_lijevi))
				return 1;
			return 0;
		} else if (to2==TACKA) {
			if (tacka_u_kruznici(k1,*t2))
				return 1;
			return 0;
		} else if (to2==TROUGAO) {
			if (tacka_u_kruznici(k1,tr2->prvi_vrh) && tacka_u_kruznici(k1,tr2->drugi_vrh) && tacka_u_kruznici(k1,tr2->treci_vrh))
				return 1;
			return 0;
		} else if (to2==KRUZNICA) {
			if (tacka_u_kruznici(k1,k2->centar) && k2->radijus<=k1->radijus-udaljenost(k1->centar,k2->centar))
				return 1;
			return 0;
		}
	} else if (to1==TROUGAO) {
		if (to2==TACKA) {
			if (tacka_u_trouglu(tr1,*t2))
				return 1;
			return 0;
		} else if (to2==PRAVOUGAONIK) {
			/*Na isti nacin,formiramo sva tjemna pravougaonika i koristimo pomocnu funckiju*/
			struct Tacka pr1,pr2,pr3;
			pr1.x=p2->donji_lijevi.x;
			pr1.y=p2->donji_lijevi.y+p2->visina;
			pr2.x=p2->donji_lijevi.x+p2->sirina;
			pr2.y=p2->donji_lijevi.y;
			pr3.x=p2->donji_lijevi.x+p2->sirina;
			pr3.y=p2->donji_lijevi.y+p2->visina;
			if (tacka_u_trouglu(tr1,pr1) && tacka_u_trouglu(tr1,pr2) && tacka_u_trouglu(tr1,pr3) && tacka_u_trouglu(tr1,p2->donji_lijevi))
				return 1;
			return 0;
		} else if (to2==KRUZNICA) {
			if (tacka_u_trouglu(tr1,k2->centar) && tangenta_na_kruznicu(tr1->prvi_vrh,tr1->drugi_vrh,*k2) &&
			tangenta_na_kruznicu(tr1->prvi_vrh,tr1->treci_vrh,*k2) && tangenta_na_kruznicu(tr1->drugi_vrh,tr1->treci_vrh,*k2))
				return 1;
			return 0;
		} else if (to2==TROUGAO) {
			if (tacka_u_trouglu(tr1,tr2->prvi_vrh) && tacka_u_trouglu(tr1,tr2->drugi_vrh) && tacka_u_trouglu(tr1,tr2->drugi_vrh))
				return 1;
			return 0;
		}
	}
	if (to1==PRAVOUGAONIK) {
		if (to2==TACKA) {
			if (tacka_u_pravougaoniku(p1,*t2))
				return 1;
			return 0;
		} else if (to2==TROUGAO) {
			if (tacka_u_pravougaoniku(p1,tr2->prvi_vrh) && tacka_u_pravougaoniku(p1,tr2->drugi_vrh)
			&& tacka_u_pravougaoniku(p1,tr2->treci_vrh))
				return 1;
			return 0;
		} else if (to2==KRUZNICA) {
			struct Tacka tk1,tk2,tk3,tk4;
			tk1.x=k2->centar.x;
			tk1.y=k2->centar.y+k2->radijus;
			tk2.x=k2->centar.x;
			tk2.y=k2->centar.y-k2->radijus;
			tk3.x=k2->centar.x+k2->radijus;
			tk3.y=k2->centar.y;
			tk4.x=k2->centar.x-k2->radijus;
			tk4.y=k2->centar.y;
			if (tacka_u_pravougaoniku(p1,k2->centar) && tacka_u_pravougaoniku(p1,tk1) && tacka_u_pravougaoniku(p1,tk2)
			&& tacka_u_pravougaoniku(p1,tk3) && tacka_u_pravougaoniku(p1,tk4))
				return 1;
			return 0;
		} else if (to2==PRAVOUGAONIK) {
			struct Tacka pp1,pp2,pp3;
			pp1.x=p2->donji_lijevi.x;
			pp1.y=p2->donji_lijevi.y+p2->visina;
			pp2.x=p2->donji_lijevi.x+p2->sirina;
			pp2.y=p2->donji_lijevi.y;
			pp3.x=p2->donji_lijevi.x+p2->sirina;
			pp3.y=p2->donji_lijevi.y+p2->visina;
			if (tacka_u_pravougaoniku(p1,pp1) && tacka_u_pravougaoniku(p1,pp2) && tacka_u_pravougaoniku(p1,pp3)
			&& tacka_u_pravougaoniku(p1,p2->donji_lijevi))
				return 1;
			return 0;
		}
	} else if (to1==TACKA) {
		if (to2==TACKA) {
			if (abs(t1->x-t2->x)<=EPS && abs(t1->y-t2->y)<=EPS)
				return 1;
			return 0;
		} else if (to2==KRUZNICA) {
			if (k2->radijus<EPS && abs(t1->x-k2->centar.x)<=EPS && abs(t1->y-k2->centar.y)<=EPS)
				return 1;
			return 0;
		} else if (to2==TROUGAO) {
			if (abs(tr2->prvi_vrh.x-tr2->drugi_vrh.x)<=EPS && abs(tr2->prvi_vrh.y-tr2->drugi_vrh.y)<=EPS
			&& abs(tr2->prvi_vrh.x-tr2->treci_vrh.x)<=EPS && abs(tr2->prvi_vrh.y-tr2->treci_vrh.y)<=EPS &&
			abs(tr2->prvi_vrh.x-t1->x)<=EPS && abs(tr2->prvi_vrh.y-t1->y)<=EPS)
				return 1;
			return 0;
		} else if (to2==PRAVOUGAONIK) {
			if (p2->visina<EPS && p2->sirina<EPS && abs(p2->donji_lijevi.x-t1->x)<=EPS && abs(p2->donji_lijevi.y-t1->y)<=EPS)
				return 1;
			return 0;
		}
	}
	return 2;
}


int main()
{
	int broj_oblika,i,tip_oblika,j;
	struct Tacka tacke[50];
	struct Trougao niz_trouglova[50];
	struct Pravougaonik niz_pravougaonika[50];
	struct Kruznica niz_kruznica[50];
	int brojac_t=0,brojac_tr=0,brojac_p=0,brojac_k=0,br=0,niz[50],brojac_t1=0,brojac_p1=0,brojac_tr1=0,brojac_k1=0;
	struct Tacka* t;
	struct Trougao* tr;
	struct Kruznica* k;
	struct Pravougaonik* p;
	struct Tacka* t1;
	struct Trougao* tr1;
	struct Kruznica* k1;
	struct Pravougaonik* p1;
	printf ("Unesite broj oblika: ");
	scanf ("%d",&broj_oblika);
	for (i=0; i<broj_oblika; i++) {
		printf ("Odaberite tip %d. oblika (1 - tacka, 2 - kruznica, 3 - pravougaonik, 4 - trougao): ",i+1);
		scanf ("%d",&tip_oblika);

		if (tip_oblika==1) {
			printf ("Unesite tacku: ");
			tacke[brojac_t]=unesi_tacku();
			brojac_t++;
			niz[br]=1;
		} else if (tip_oblika==2) {
			niz_kruznica[brojac_k]=unesi_kruznicu();
			brojac_k++;
			niz[br]=2;
		} else if (tip_oblika==3) {
			niz_pravougaonika[brojac_p]=unesi_pravougaonik();
			brojac_p++;
			niz[br]=3;
		} else if (tip_oblika==4) {
			niz_trouglova[brojac_tr]=unesi_trougao();
			brojac_tr++;
			niz[br]=4;
		} else {
			printf("Nepoznat tip oblika %d!\n",tip_oblika);
			i--;
			br--;
		}
		br++;
	}
	printf ("\n");
	brojac_tr=0;
	brojac_p=0;
	brojac_t=0;
	brojac_k=0;
	/*Nakon sto smo smjestili sve oblike u razlicite nizove,prolazimo dvostrukom petljom i uporedjujemo ih*/
	/*Uz pomoc brojaca,uvijek smo u opsegu tih nizova,i sprijeceno je ponavljanje tj.uporedjivanje istih oblika*/
	for (i=0; i<broj_oblika; i++) {
		if (niz[i]==1) {
			t1=&tacke[brojac_t1];
			brojac_t1++;
			for (j=0; j<broj_oblika; j++) {

				if (niz[j]==1) {
					t=&tacke[brojac_t];
					brojac_t++;
					if (obuhvata(t1,TACKA,t,TACKA) && j!=i)
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==2) {
					k=&niz_kruznica[brojac_k];
					brojac_k++;
					if (obuhvata(t1,TACKA,k,KRUZNICA) )
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==3) {
					p=&niz_pravougaonika[brojac_p];
					brojac_p++;
					if (obuhvata(t1,TACKA,p,PRAVOUGAONIK))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==4) {
					tr=&niz_trouglova[brojac_tr];
					brojac_tr++;
					if (obuhvata(t1,TACKA,tr,TROUGAO))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				}
			}
		} else if (niz[i]==2) {
			k1=&niz_kruznica[brojac_k1];
			brojac_k1++;
			for (j=0; j<broj_oblika; j++) {
				if (niz[j]==1) {
					t=&tacke[brojac_t];
					brojac_t++;
					if (obuhvata(k1,KRUZNICA,t,TACKA))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==3) {
					p=&niz_pravougaonika[brojac_p];
					brojac_p++;
					if (obuhvata(k1,KRUZNICA,p,PRAVOUGAONIK))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==2) {
					k=&niz_kruznica[brojac_k];
					brojac_k++;
					if (obuhvata(k1,KRUZNICA,k,KRUZNICA) && j!=i)
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==4) {
					tr=&niz_trouglova[brojac_tr];
					brojac_tr++;
					if (obuhvata(k1,KRUZNICA,tr,TROUGAO))
						printf ("Oblik %d obuhvata oblike %d.\n",i+1,j+1);

				}
			}
		} else if (niz[i]==3) {
			p1=&niz_pravougaonika[brojac_p1];
			brojac_p1++;
			for (j=0; j<broj_oblika; j++) {
				if (niz[j]==1) {
					t=&tacke[brojac_t];
					brojac_t++;
					if (obuhvata(p1,PRAVOUGAONIK,t,TACKA))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==2) {
					k=&niz_kruznica[brojac_k];
					brojac_k++;
					if (obuhvata(p1,PRAVOUGAONIK,k,KRUZNICA))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==3) {
					p=&niz_pravougaonika[brojac_p];
					brojac_p++;
					if (obuhvata(p1,PRAVOUGAONIK,p,PRAVOUGAONIK) && j!=i)
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==4) {
					tr=&niz_trouglova[brojac_tr];
					brojac_tr++;
					if (obuhvata(p1,PRAVOUGAONIK,tr,TROUGAO))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				}
			}
		} else if (niz[i]==4) {
			tr1=&niz_trouglova[brojac_tr1];
			brojac_tr1++;
			for (j=0; j<broj_oblika; j++) {
				if (niz[j]==1) {
					t=&tacke[brojac_t];
					brojac_t++;
					if (obuhvata(tr1,TROUGAO,t,TACKA))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==2) {
					k=&niz_kruznica[brojac_k];
					brojac_k++;
					if (obuhvata(tr1,TROUGAO,k,KRUZNICA))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==3) {
					p=&niz_pravougaonika[brojac_p];
					brojac_p++;
					if (obuhvata(tr1,TROUGAO,p,PRAVOUGAONIK))
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				} else if (niz[j]==4) {
					tr=&niz_trouglova[brojac_tr];
					brojac_tr++;
					if (obuhvata(tr1,TROUGAO,tr,TROUGAO) && j!=i)
						printf ("Oblik %d obuhvata oblik %d.\n",i+1,j+1);
				}
			}
		}
		brojac_tr=0;
		brojac_p=0;
		brojac_k=0;
		brojac_t=0;
	}
	return 0;
}


/*moje ne??to..
#include <stdio.h>
#include <math.h>
#define EPS 0.001

enum TipOblika{	TACKA=1, KRUZNICA, PRAVOUGAONIK, TROUGAO} tip;

struct Tacka {float x,y; };
struct Kruznica {
	struct Tacka centar;
	float poluprecnik;
};
struct Pravougaonik {
	struct Tacka dole_lijevo;
	float visina, sirina;
};
struct Trougao {struct Tacka vrh1, vrh2, vrh3; };

//fje za unos geom. oblika
struct Tacka unos_xy(){
	struct Tacka t;
	printf("koordinate x,y: ");
	scanf("%f,%f", &t.x, &t.y);
	return t;
}
struct Tacka unos_tacke(){
	struct Tacka t;
	printf("Unesite tacku: ");
	t=unos_xy();
	return t;
}
struct Kruznica unos_kruznice(){
	struct Kruznica k;
	printf("Unesite centar kruznice: ");
	k.centar=unos_xy();
	printf("Unesite poluprecnik kruznice: ");
	scanf("%f", &k.poluprecnik);
	return k;
}
struct Pravougaonik unos_pravougaonika(){
	struct Pravougaonik p;
	printf("Unesite donji lijevi ugao: ");
	p.dole_lijevo=unos_xy();
	printf("Unesite sirinu: ");
	scanf("%f", &p.sirina);
	printf("Unesite visinu: ");
	scanf("%f", &p.visina);
	return p;
}
struct Trougao unos_trougla(){
	struct Trougao tr;
	printf("Unesite prvi vrh: ");
	tr.vrh1=unos_xy();
	printf("Unesite drugi vrh: ");
	tr.vrh2=unos_xy();
	printf("Unesite treci vrh: ");
	tr.vrh3=unos_xy();
	return tr;
}

float udaljenost(struct Tacka t1, struct Tacka t2){
	return sqrt( (t1.x-t2.x)*(t1.x-t2.x) + (t1.y-t2.y)*(t1.y-t2.y) );
}
float PovrsinaTrougla(struct Trougao tr){ //koristeci Heronov obrazac
	struct Tacka A=tr.vrh1,B=tr.vrh2, C=tr.vrh3;
	float s, a, b, c; //s je poluobim
	a=udaljenost(B, C);
	b=udaljenost(A, C);
	c=udaljenost(A, B);
	s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
int DaLiSuTackeIdenticne(struct Tacka t1, struct Tacka t2){
	if (udaljenost(t1, t2) < EPS) return 1;
	return 0;
}
int DaLiJeTackaUnutarKruznice(struct Tacka t, struct Kruznica k){
	if (udaljenost(t, k.centar) - k.poluprecnik <= EPS) return 1;
	return 0;
}
int DaLiJeTackaUnutarPravougaonika(struct Tacka t, struct Pravougaonik p){
	if (t.y > p.dole_lijevo.y + p.visina || t.y < p.dole_lijevo.y) return 0;
	if (t.x > p.dole_lijevo.x + p.sirina || t.x < p.dole_lijevo.x) return 0;
	return 1;
}
int DaLiJeTackaUnutarTrougla(struct Tacka D, struct Trougao tr){
	struct Trougao pom1, pom2, pom3;
	//ABC je sam tr
	pom2=tr; pom2.vrh3=D; //ABD
	pom3.vrh1=tr.vrh1; pom3.vrh2=tr.vrh3; pom3.vrh3=D; //ACD
	pom1=pom3; pom1.vrh1=tr.vrh2; //BCD
	// ta??ka je spolja??nja ako je zbir povr??ina trouglova ABC, ABD i ACD ve??i od povr??ine trougla BCD
	if (PovrsinaTrougla(tr)+PovrsinaTrougla(pom2)+PovrsinaTrougla(pom3) > PovrsinaTrougla(pom1)) return 0;
	return 1;
}

//int DaLiJe...UnutarTacke //samo ako je velicina jednak nuli DOPUNITI!!!
//....

int DaLiJeKruznicaUnutarKruznice(struct Kruznica k1, struct Kruznica k2){
								//k1 unutar k2	
	if (DaLiSuTackeIdenticne(k1.centar, k2.centar) && k1.poluprecnik<=k2.poluprecnik ) return 1;
	//if() return 1 ??
	return 0;
}
int DaLiJeTrougaoUnutarKruznice(struct Trougao tr, struct Kruznica k){
	if (DaLiJeTackaUnutarKruznice(tr.vrh1, k) && DaLiJeTackaUnutarKruznice(tr.vrh2, k) && DaLiJeTackaUnutarKruznice(tr.vrh3, k)) return 1;
	return 0;
}
int DaLiJePravougaonikUnutarKruznice(struct Pravougaonik p, struct Kruznica k){
	struct Tacka gore_desno=p.dole_lijevo;
	gore_desno.x+=p.sirina;
	gore_desno.y+=p.visina;
	return (DaLiJeTackaUnutarKruznice(p.dole_lijevo, k) && DaLiJeTackaUnutarKruznice(gore_desno, k));
}

int DaLiJePravougaonikUnutarPravougaonika(struct Pravougaonik p1, struct Pravougaonik p2){
										// p1 unutar p2
	if (p1.dole_lijevo.x < p2.dole_lijevo.x || p1.dole_lijevo.y < p2.dole_lijevo.y) return 0;
	if (p1.dole_lijevo.x+p1.sirina > p2.dole_lijevo.x+p2.sirina) return 0;
	if (p1.dole_lijevo.y+p1.visina > p2.dole_lijevo.y+p2.visina) return 0;
	return 1;
}

int DaLiJeTrougaoUnutarTrougla(struct Trougao t1, struct Trougao t2){ //...
								//t1 unutar t2
	if (DaLiSuTackeIdenticne(t1.vrh1, t2.vrh1) && DaLiSuTackeIdenticne(t1.vrh2, t2.vrh2) && DaLiSuTackeIdenticne(t1.vrh3, t2.vrh3)) return 1;
	return 0;	
}

int obuhvata (void *oblik1, enum TipOblika to1, void *oblik2, enum TipOblika to2){
	struct Kruznica* k, *k2;
	struct Tacka *tac, *tac2;
	struct Pravougaonik *p, *p2;
	struct Trougao *tro, *tro2;
	
	if (to1==KRUZNICA) k=(struct Kruznica*) oblik1;
	else if (to1==TACKA) tac=(struct Tacka*) oblik1;
	else if (to1==PRAVOUGAONIK)	p=(struct Pravougaonik*) oblik1;
	else if (to1==TROUGAO)	tro=(struct Trougao*) oblik1;
	
	if (to2==KRUZNICA) k2=(struct Kruznica*) oblik2;
	else if (to2==TACKA) tac2=(struct Tacka*) oblik2;
	else if (to2==PRAVOUGAONIK) p2=(struct Pravougaonik*) oblik2;
	else if (to2==TROUGAO) tro2=(struct Trougao*) oblik2;
	
	if (to2==TACKA){
		if (to1==TACKA) return (DaLiSuTackeIdenticne(*tac, *tac2));
		else if (to1==KRUZNICA) return (DaLiJeTackaUnutarKruznice(*tac2, *k));
		else if (to1==PRAVOUGAONIK) return (DaLiJeTackaUnutarPravougaonika(*tac2, *p));
		else if (to1==TROUGAO) return (DaLiJeTackaUnutarTrougla(*tac2, *tro));
	}
	else if (to2==KRUZNICA){
		if (to1==KRUZNICA) return DaLiJeKruznicaUnutarKruznice(*k2, *k);
		else if (to1==TROUGAO) return DaLiJeTrougaoUnutarKruznice(*tro, *k2);
		else if (to1==PRAVOUGAONIK) return DaLiJePravougaonikUnutarKruznice(*p, *k2);
		
	}
	else if (to2==PRAVOUGAONIK){
		if (to1==PRAVOUGAONIK) return DaLiJePravougaonikUnutarPravougaonika(*p2, *p);
	}
	
	else if (to2==TROUGAO){
		if (to1==TROUGAO) DaLiJeTrougaoUnutarTrougla(*tro2, *tro);
	}
	
	return 0;
}

int main() {
	int broj_oblika, i=0, tip[50];
	enum TipOblika oblici[50];
	
	printf("Unesite broj oblika: ");
	scanf("%d", &broj_oblika);
	
	while(i<broj_oblika){
		printf("Odaberite tip %d. oblika (1 - tacka, 2 - kruznica, 3 - pravougaonik, 4 - trougao): ", i+1);
		scanf("%d", &tip[i]);
		if (tip[i] < 1 || tip[i] > 4){
			printf("Nepoznat tip oblika %d!\n", tip[i]);
		}
		else if (tip[i]==1){
			oblici[i]=TACKA;
			unos_tacke();
		}
		else if (tip[i]==2){
			oblici[i]=KRUZNICA;
			unos_kruznice();
		}
		else if (tip[i]==3){
			oblici[i]=PRAVOUGAONIK;
			unos_pravougaonika();
		}
		else if (tip[i]==4){
			oblici[i]=TROUGAO;
			unos_trougla();
		}
		
		i++;
	}
	
//	i=0;
//	while(i<broj_oblika){
//		if (obuhvata(&oblici[i]))
//	}


	printf("%d", obuhvata(&oblici[0], TROUGAO, &oblici[1], TROUGAO));
	
	return 0;
}
*/


