/B 2016/2017, Zadaća 4, Zadatak 4
//Napomena: testovi ce biti dostupni dan pred rok!
#include <iostream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<stdexcept>
#include<cstring>
using namespace std;
class Datum
{
 int d, m, g;
   public:
   Datum(int dan, int mjesec, int godina);
   
   void Postavi(int dan, int mjesec, int godina);
   int DajDan() const { return d;}
   int DajMjesec() const { return m;}
   int DajGodinu() const { return g;}
   void Ispisi() const { cout<<d<<"/"<<m<<"/"<<g;}
};

Datum::Datum(int dan, int mjesec, int godina)
{
    if(dan<1 || dan>31 || mjesec<1 ||mjesec>12 || godina>2017 || godina<0) throw domain_error("Neispravan datum");
    int broj_dana[] { 31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};
    if((godina%4==0 && godina %100!=0) || godina%400==0) broj_dana[1]++;
    if(dan>broj_dana[mjesec-1]) throw domain_error("Neispravan datum");
    Datum::d=dan;
    Datum::m=mjesec;
    Datum::g=godina;
}
void Datum::Postavi(int dan, int mjesec, int godina)
{
    if(dan<1 ||dan>31 ||mjesec<1 || mjesec>12 ||godina>2017 ||godina<0) throw domain_error("Neispravan datum");
  int broj_dana [] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if((godina%4==0 && godina%100!=0) || godina%400==0) broj_dana[1]++;
  if(dan>broj_dana[mjesec-1]) throw domain_error("Neispravan datum");
  Datum::d=dan;
  Datum::m=mjesec;
  Datum::g=godina;
    
}

class Kupac
{ string ime_kupca;
Datum dat_rodjenja;
  public:
    Kupac( const string &ime_i_prezime, const Datum &datum_rodjenja):dat_rodjenja(datum_rodjenja) { ime_kupca=ime_i_prezime;}
    void Postavi( const string &ime_i_prezime, const Datum &datum_rodjenja);
    string DajImeIPrezime() const { return ime_kupca;}
    Datum DajDatumRodjenja() const { return dat_rodjenja;}
  //  void Ispisi() const {  cout<<ime_kupca<<" ("<<dat_rodjenja->Ispisi()<<")"; }
    void Ispisi() const;
};

void Kupac::Postavi(const string &ime_i_prezime, const Datum &datum_rodjenja)
{
    dat_rodjenja=datum_rodjenja;
    ime_kupca=ime_i_prezime;
}
void Kupac::Ispisi() const
{
    Datum novi=DajDatumRodjenja();
    cout<<ime_kupca<<" (";
    novi.Ispisi();
    cout<<")";
}


class Stan
{

    string adresa;
    int sprat, broj_soba;
    bool namjesten;
    double kvadratura;
    public:
    Stan(const string &adresa, int sprat, int broj_soba,bool namjesten, double kvadratura);
    void Postavi(const string &adresa, int sprat, int broj_soba, bool namjesten, double kvadratura);
    string DajAdresu() const { return adresa;}
    int DajSprat() const { return sprat;}
    int DajBrojSoba() const { return broj_soba;}
    bool DajNamjesten() const { return namjesten;}
    double DajKvadraturu() const { return kvadratura;}
    void Ispisi() const;
};
Stan::Stan(const string &adresa, int sprat, int broj_soba, bool namjesten, double kvadratura)
{
    if(sprat<0 || broj_soba<0 || kvadratura<0) throw domain_error("Neispravan unos podataka");
    Stan::adresa=adresa;
    Stan::sprat=sprat;
    Stan::broj_soba=broj_soba;
    Stan::namjesten=namjesten;
    Stan::kvadratura=kvadratura;
    
}
void Stan::Postavi(const string &adresa, int sprat, int broj_soba, bool namjesten, double kvadratura)
{
    if(sprat<0 ||broj_soba<0 ||kvadratura<0) throw domain_error("Neispravan unos podataka");
    Stan::adresa=adresa;
    Stan::sprat=sprat;
    Stan::broj_soba=broj_soba;
    Stan::namjesten=namjesten;
    Stan::kvadratura=kvadratura;
}
void Stan::Ispisi() const
{
    if(broj_soba%10==1)
    {
        cout<<"Stan se nalazi na adresi "<<adresa<<" na "<<sprat<<". spratu i ima "<< broj_soba<<" sobu."<<endl;
        cout<<"Kvadratura stana je "<<kvadratura<<" (m^2) i stan ";
        if(namjesten) cout<<"je namjesten.";
        else if(!namjesten) cout<<"nije namjesten";
    }
    else if(broj_soba%10==2 ||broj_soba%10==3 || broj_soba%10==4)
    {
        cout<<"Stan se nalazi na adresi "<<adresa<<" na "<<sprat<<". spratu i ima "<< broj_soba<<" sobe."<<endl;
        cout<<"Kvadratura stana je "<<kvadratura<<" (m^2) i stan ";
        if(namjesten) cout<<"je namjesten.";
        else if(!namjesten) cout<<"nije namjesten";
    }
    else
    {
        cout<<"Stan se nalazi na adresi "<<adresa<<" na "<<sprat<<". spratu i ima "<< broj_soba<<" soba."<<endl;
        cout<<"Kvadratura stana je "<<kvadratura<<" (m^2) i stan ";
        if(namjesten) cout<<"je namjesten.";
        else if(!namjesten) cout<<"nije namjesten";
    }
}

class Prodaja
{
  string ime_agenta;
    double cijena;
    Datum dat_prodaje;
    Kupac kupac_objekta;
    Stan prodani_stan;
    public:
    Prodaja(const string &ime_agenta_prodaje, double cijena_stana, const Datum &datum_prodaje, const Kupac &kupac_stana, const Stan &kupljeni_stan);
    Prodaja(const string &ime_agenta_prodaje, double cijena_stana, int dan_prodaje, int mjesec_prodaje, int godina_prodaje, string &ime_kupca, const Datum &datum_rodjenja_kupca, const string &adresa_stana, int sprat_stana, int broj_soba, bool namjesten_stan, double broj_kvadrata );
    void PromijeniKupca(const Kupac &novi_kupac) { kupac_objekta=novi_kupac;}
    void PromijeniStan(const Stan &novi_stan) { prodani_stan=novi_stan;}
    void PromijeniDatumKupovine(const Datum &novi_datum) { dat_prodaje=novi_datum;}
    void PromijeniCijenuProdaje(const double &nova_cijena) { cijena=nova_cijena;}
    void PomjeriDanUnaprijed();
    void PomjeriDanUnazad();
    Datum DajDatumProdaje() const { return dat_prodaje;}
    string DajImeAgenta() const { return ime_agenta;}
    string DajImeKupca() const { return kupac_objekta.DajImeIPrezime();}
    double DajCijenuStana() const { return cijena;}
   friend bool ProdatPrije(const Prodaja &p1, const Prodaja &p2);
    friend bool SkupljiStan(const Prodaja &p1, const Prodaja &p2);
    void Ispisi() const;
    
};
 bool ProdatPrije(const Prodaja &p1, const Prodaja &p2)
 {
     Datum dat1(p1.DajDatumProdaje()), dat2(p2.DajDatumProdaje());
     int dan1(dat1.DajDan()), mjesec1(dat1.DajMjesec()), god1(dat1.DajGodinu());
     int dan2(dat2.DajDan()), mjesec2(dat2.DajMjesec()), god2(dat2.DajGodinu());
     if(god1<god2) return true;
     else if(god1>god2) return false;
     else if(god1==god2 && mjesec1<mjesec2) return true;
     else if(god1==god2 && mjesec1>mjesec2) return false;
     else if(god1==god2 && mjesec1==mjesec2 && dan1<dan2) return true;
     else return false;
 }
Prodaja::Prodaja(const string &ime_agenta_prodaje, double cijena_stana, const Datum &datum_prodaje, const Kupac &kupac_stana, const Stan &kupljeni_stan):dat_prodaje(datum_prodaje),kupac_objekta(kupac_stana), prodani_stan(kupljeni_stan)
{
    ime_agenta=ime_agenta_prodaje;
    cijena=cijena_stana;
    
}
Prodaja::Prodaja(const string &ime_agenta_prodaje, double cijena_stana, int dan_prodaje, int mjesec_prodaje, int godina_prodaje, string &ime_kupca, const Datum &datum_rodjenja_kupca, const string &adresa_stana, int sprat_stana, int broj_soba, bool namjesten_stan, double broj_kvadrata ):dat_prodaje(dan_prodaje,mjesec_prodaje, godina_prodaje), kupac_objekta(ime_kupca, datum_rodjenja_kupca), prodani_stan(adresa_stana, sprat_stana, broj_soba, namjesten_stan, broj_kvadrata)
{
   ime_agenta=ime_agenta_prodaje;
    cijena=cijena_stana;
}
void Prodaja::PomjeriDanUnaprijed()
{
    int test_godine=dat_prodaje.DajGodinu();
    int test_mjeseci=dat_prodaje.DajMjesec();
    int test_dana=dat_prodaje.DajDan();
    int broj_dana[] { 31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};
    if((test_godine%4==0 && test_godine%100!=0) || (test_godine%400==0)) broj_dana[1]++;
    if(test_dana==broj_dana[test_mjeseci-1] && test_mjeseci==12)
    {
        int dan=1, mjesec=1, godina=test_godine+1;
        Datum novi(dan, mjesec, godina);
        PromijeniDatumKupovine(novi);
    }
else    if(test_dana==broj_dana[test_mjeseci-1] && test_mjeseci!=12)
    {
         int dan=1; int mjesec=test_mjeseci+1; int godina=test_godine;
        Datum novi(dan, mjesec, godina);
        PromijeniDatumKupovine(novi);
     
    }
     else 
     {
         int dan=test_dana+1; int mjesec=test_mjeseci; int godina=test_godine;
         Datum novi(dan, mjesec, godina);
         PromijeniDatumKupovine(novi);
     }
}
void Prodaja::PomjeriDanUnazad()
{
int test_godine=dat_prodaje.DajGodinu();
    int test_mjeseci=dat_prodaje.DajMjesec();
    int test_dana=dat_prodaje.DajDan();
    int broj_dana[] { 31, 28, 31, 30, 31, 30, 31, 31,30, 31, 30, 31};
    if((test_godine%4==0 && test_godine%100!=0) || (test_godine%400==0)) broj_dana[1]++;
    if(test_dana==1 && test_mjeseci==1)
    {
        int mjesec=12; int dan=31; int godina=test_godine-1;
        Datum novi(dan, mjesec, godina);
        PromijeniDatumKupovine(novi);
    }
    else if(test_dana==1 && test_mjeseci!=1)
    {
        int mjesec=test_mjeseci-1; int dan=broj_dana[mjesec-1]; int godina=test_godine;
      Datum novi(dan, mjesec, godina);
     PromijeniDatumKupovine(novi);
        
    }
    else {
        int dan=test_dana-1; int mjesec=test_mjeseci; int godina=test_godine;
   Datum novi(dan, mjesec, godina);
  PromijeniDatumKupovine(novi);
           
    }
}






bool SkupljiStan(const Prodaja &p1, const Prodaja &p2)
{
    return p1.cijena>p2.cijena;
}
void Prodaja::Ispisi() const
{
    cout<<"Ime agenta: "<<setw(30)<<ime_agenta<<endl;
    cout<<"Ime kupca: "<<setw(32);kupac_objekta.Ispisi();
    cout<<endl;
    cout<<"Zakazani datum prodaje: "<<setw(7);dat_prodaje.Ispisi();
    cout<<right;
    cout<<endl<<"Cijena stana: "<<setw(21)<<cijena<<endl;
    cout<<"Informacije o stanu: "<<endl;
    prodani_stan.Ispisi();
}