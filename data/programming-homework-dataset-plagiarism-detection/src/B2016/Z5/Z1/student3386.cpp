/B16/17 (Zadaća 5, Zadatak 1)
//Autotestovi by Eldar Kurtic (mail: ekurtic3@etf.unsa.ba)
//Za autotestove se obracati *iskljucivo* osobi koja ih pise
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>


using std::map;
using std::string;
using std::cout;

struct Korisnik
{
    string ime,prezime,adresa,telefon;
    //Korisnik(string ime,string prezime,string adresa,string telefon):ime(ime),prezime(prezime),adresa(adresa),telefon(telefon){}
};
class Knjiga
{
    string naslov,ime_pisca,zanr;
    int godina;
    Korisnik *pok;
    public:
    Knjiga(string n,string i_p,string z,int godina):naslov(n),ime_pisca(i_p),zanr(z),godina(godina),pok(nullptr){}
    string DajNaslov(){return naslov;}
    string DajAutora(){return ime_pisca;}
    string DajZanr(){return zanr;}
    int DajGodinuIzdavanja(){return godina;}
    Korisnik *DajKodKogaJe(){return pok;}
    void ZaduziKnjigu(Korisnik &ja_sam){pok=&ja_sam;}
    void RazduziKnjigu(){pok=nullptr;}
    bool DaLiJeZaduzena(){return pok!=nullptr;}
};
class Biblioteka
{
    map<int,Korisnik*> korisnici;
    map<int,Knjiga*> knjige;
    void Imal_knjige(int br)
    {
        if(!knjige.count(br))
            throw std::logic_error("Knjiga nije nadjena");
    }
    void Imal_korisnika(int br)
    {
        if(!korisnici.count(br))
            throw std::logic_error("Korisnik nije nadjen");
    }
    public:
    Biblioteka(){}
    void RegistrirajNovogKorisnika(int cl_br,string ime,string prezime,string adresa,string broj_tel)
    {
        if(korisnici.count(cl_br))
            throw std::logic_error("Korisnik vec postoji");
        korisnici[cl_br]=new Korisnik{ime,prezime,adresa,broj_tel};
    }
    void RegistrirajNovuKnjigu(int br_knj,string n,string i_p,string z,int god)
    {
        if(knjige.count(br_knj))
            throw std::logic_error("Knjiga vec postoji");
        knjige[br_knj]=new Knjiga(n,i_p,z,god);
    }
    ~Biblioteka()
    {
        for(auto a:korisnici)
            delete a.second;
        korisnici.clear();
        for(auto a:knjige)
            delete a.second;
        knjige.clear();
    }
    Korisnik &NadjiKorisnika(int cl_br)
    {
        Imal_korisnika(cl_br);
        return *korisnici[cl_br];
    }
    Knjiga &NadjiKnjigu(int br_knj)
    {
        Imal_knjige(br_knj);
        return *knjige[br_knj];
    }
    void IzlistajKorisnike()const
    {
        for(auto a:korisnici)
        {
            auto b=*(a.second);
            cout<<"Clanski broj: "<<a.first<<"\n";
            cout<<"Ime i prezime: "<<b.ime<<" "<<b.prezime<<"\n";
            cout<<"Adresa: "<<b.adresa<<"\n";
            cout<<"Broj telefona: "<<b.telefon<<"\n";
            cout<<"\n";
        }
    }
    void IzlistajKnjige()const
    {
        for(auto a:knjige)
        {
            auto b=*(a.second);
            cout<<"Evidencijski broj: "<<a.first<<"\n";
            cout<<"Naslov: "<<b.DajNaslov()<<"\n";
            cout<<"Pisac: "<<b.DajAutora()<<"\n";
            cout<<"Zanr: "<<b.DajZanr()<<"\n";
            cout<<"Godina izdavanja: "<<b.DajGodinuIzdavanja()<<"\n";
            if(b.DaLiJeZaduzena())
            {
                auto c=*(b.DajKodKogaJe());
                cout<<"Zaduzena kod korisnika: "<<c.ime<<" "<<c.prezime<<"\n";
            }
            cout<<"\n";
        }
    }
    void ZaduziKnjigu(int br_knj,int cl_br)
    {
        Imal_knjige(br_knj);
        Imal_korisnika(cl_br);
        if(knjige[br_knj]->DaLiJeZaduzena())
            throw std::logic_error("Knjiga je vec zaduzena");
        knjige[br_knj]->ZaduziKnjigu(*(korisnici[cl_br]));
    }
    void RazduziKnjigu(int br_knj)
    {
        Imal_knjige(br_knj);
        if(!knjige[br_knj]->DaLiJeZaduzena())
            throw std::logic_error("Knjiga nije zaduzena");
        knjige[br_knj]->RazduziKnjigu();
    }
    void PrikaziZaduzenja(int cl_br)
    {
        auto korisnik(NadjiKorisnika(cl_br));
        bool bio=false;
        for(auto a:knjige)
        {
            auto knjiga=(*(a.second));
            if(knjiga.DaLiJeZaduzena())
            {    
                auto provjera=*(knjiga.DajKodKogaJe());
                if(provjera.ime == korisnik.ime and provjera.prezime == korisnik.prezime and provjera.adresa == korisnik.adresa and provjera.telefon == korisnik.telefon)
                {
                    bio=true;
                    cout<<"Evidencijski broj: "<<a.first<<"\n";
                    cout<<"Naslov: "<<knjiga.DajNaslov()<<"\n";
                    cout<<"Pisac: "<<knjiga.DajAutora()<<"\n";
                    cout<<"Zanr: "<<knjiga.DajZanr()<<"\n";
                    cout<<"Godina izdavanja: "<<knjiga.DajGodinuIzdavanja()<<"\n\n";
                }
            }
        }
        if(!bio)
            cout<<"Nema zaduzenja za tog korisnika!";
    }
    Biblioteka(const Biblioteka &b)
    {
        for(auto it=b.korisnici.begin();it!=b.korisnici.end();it++)
            korisnici[it->first]=new Korisnik(*(it->second));
        for(auto it=b.knjige.begin();it!=b.knjige.end();it++)
            knjige[it->first] = new Knjiga(*(it->second));
        for(auto a:knjige)
        {
            auto &knjiga=*(a.second);
            if(knjiga.DaLiJeZaduzena())
            {
                auto b=*(knjiga.DajKodKogaJe());
                auto korisnik=std::find_if(korisnici.begin(),korisnici.end(),[b](std::pair<int,Korisnik*> d)
                {
                    auto novi=*(d.second);
                    return novi.ime==b.ime and novi.prezime==b.prezime and novi.adresa==b.adresa and novi.telefon==b.telefon;
                });
                if(korisnik!=korisnici.end())
                    knjiga.ZaduziKnjigu((*(*korisnik).second));
            }
        }
    }
    Biblioteka(Biblioteka &&b)
    {
        korisnici=b.korisnici;
        knjige=b.knjige;
    }
    Biblioteka &operator=(const Biblioteka &b)
    {
        if(this!=&b)
        {
            for(auto a:korisnici)
                delete a.second;
            korisnici.clear();
            for(auto it=b.korisnici.begin();it!=b.korisnici.end();it++)
                korisnici[it->first]=new Korisnik(*(it->second));
            for(auto a:knjige)
                delete a.second;
            knjige.clear();
            for(auto it=b.knjige.begin();it!=b.knjige.end();it++)
                knjige[it->first]=new Knjiga(*(it->second));
            for(auto a:knjige)
            {
                auto &knjiga=*(a.second);
                if(knjiga.DaLiJeZaduzena())
                {
                    auto b=*(knjiga.DajKodKogaJe());
                    auto korisnik=std::find_if(korisnici.begin(),korisnici.end(),[b](std::pair<int,Korisnik*> d)
                    {
                        auto novi=*(d.second);
                        return novi.ime==b.ime and novi.prezime==b.prezime and novi.adresa==b.adresa and novi.telefon==b.telefon;
                    });
                    if(korisnik!=korisnici.end())
                        knjiga.ZaduziKnjigu((*(*korisnik).second));
                }
            }
            
        }
        return *this;
    }
    Biblioteka &operator =(Biblioteka &&b)
    {
        if(this!=&b)
        {
            for(auto a:korisnici)
                delete a.second;
            korisnici.clear();
            korisnici=std::move(b.korisnici);
            for(auto a:knjige)
                delete a.second;
            knjige.clear();
            knjige=std::move(b.knjige);
        }
        return *this;
    }

};
int main ()
{
    /*
    Biblioteka c;
    c.RegistrirajNovogKorisnika(4,"Nejla","Nanic","Kosevo?","062490222");
    c.RegistrirajNovuKnjigu(1,"40 pravila ljubavi","Elif Safak","Vjerska?",2009);
    c.RegistrirajNovuKnjigu(2,"Alhemicar","Paulo Coelho","Drama",1988);
    c.RegistrirajNovuKnjigu(3,"11 minutes","Paulo Coelho","Romansa",2003);
    c.ZaduziKnjigu(1,4);
    c.ZaduziKnjigu(2,4);
    c.ZaduziKnjigu(3,4);
    c.IzlistajKnjige();
    c.IzlistajKorisnike();*/
    using std::cin;
    Biblioteka c;
    int i=0;
    int j=0;
    for(;;)
    {
        cout<<"\nGlavni meni, izaberite neku od sljedecih opcija:\n"
        << "1 za dodavanje novog korisnika\n2 za dodavanje nove knjige\n3 za izlistavanje svih korisnika\n"
        << "4 za izlistavanje svih knjiga\n5 za zaduzivanje knjige\n6 za razduzivanje knjige\n0 za kraj\n";
        int n;
        cin>>n;
        if(n==1)
        {
            i++;
            cin.ignore(1000,'\n');
            cout<<"Unesite ime: ";
            string s;
            getline(cin,s);
            cout<<"Unesite prezime: ";
            string p;
            getline(cin,p);
            cout<<"Unesite adresu: ";
            string a;
            getline(cin,a);
            cout<<"Unesite broj telefona: ";
            string b;
            getline(cin,b);
            c.RegistrirajNovogKorisnika(i,s,p,a,b);
        }
        else if(n==2)
        {
            j++;
            cin.ignore(10000,'\n');
            string s;
            cout<<"Unesite ime knjige: ";
            getline(cin,s);
            cout<<"Unesite ime i prezime autora: ";
            string a;
            getline(cin,a);
            cout<<"Unesite zanr: ";
            string z;
            getline(cin,z);
            cout<<"Unesite godinu izdavanja: ";
            int god;
            cin>>god;
            c.RegistrirajNovuKnjigu(j,s,a,z,god);
        }
        else if(n==3)
            c.IzlistajKorisnike();
        else if(n==4)
            c.IzlistajKnjige();
        else if(n==5)
        {
            try{
            cout<<"Unesite evidencijski broj knjige koju zelite zaduziti: ";
            int a;
            cin>>a;
            auto knjiga=c.NadjiKnjigu(a);
            cout<<"Unesite clanski broj osobe koja zaduzuje knjigu: ";
            int b;
            cin>>b;
            auto osoba=c.NadjiKorisnika(b);
            c.ZaduziKnjigu(a,b);
            }
            catch(std::logic_error e)
            {
                cout<<e.what()<<"\nPokusajte ponovno\n";
            }
        }
        else if(n==6)
        {
            cout<<"Unesite evidencijski broj knjige koju zelite razduziti: ";
            int a;
            cin>>a;
            c.RazduziKnjigu(a);
        }
        else if(n==0)
            break;
    }
    
	return 0;
}