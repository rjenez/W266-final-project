/B16/17 (Zadaća 5, Zadatak 2)
//Autotestovi by Eldar Kurtic (mail: ekurtic3@etf.unsa.ba)
//Za autotestove se obracati *iskljucivo* osobi koja ih pise
#include <iostream>
#include<string>
#include<utility>
#include<map>
#include<stdexcept>
#include<memory>
struct Korisnik{
    std::string ime;
    std::string prezime;
    std::string adresa;
    std::string telefon;
};
class Knjiga{
    std::string naslov;
    std::string autor;
    std::string zanr;
    int godina_izdavanja;
    Korisnik *kod_koga_je;
    public:
    Knjiga (const std::string &naslov, const std::string &autor, const std::string &zanr, const int &godina_izdavanja);
    std::string DajNaslov() const{return naslov;};
    std::string DajAutora() const{return autor;};
    std::string DajZanr() const{return zanr;};
    int DajGodinuIzdavanja() const{ return godina_izdavanja;};
    Korisnik* DajKodKogaJe() const{return kod_koga_je;};
    void ZaduziKnjigu(Korisnik &korisnik) {kod_koga_je=&korisnik;};
    void RazduziKnjigu(){kod_koga_je=nullptr;};
    bool DaLiJeZaduzena() const{ if(kod_koga_je==nullptr) return false ; else return true;};
    
};

Knjiga::Knjiga(const std::string &naslov, const std::string &autor, const std::string &zanr, const int &godina_izdavanja):
naslov(naslov),autor(autor),zanr(zanr),godina_izdavanja(godina_izdavanja){
    kod_koga_je=nullptr;
}
class Biblioteka{
    std::map<int,std::shared_ptr<Korisnik>> korisnici;
    std::map<int,std::shared_ptr<Knjiga>> knjige;
    public:
    Biblioteka(){};
   void RegistrirajNovogKorisnika(int clanski_broj,const std::string &ime,const std::string &prezime,const std::string &adresa,const std::string &telefon);
   void RegistrirajNovuKnjigu(int evidencijski_broj,const std::string &naslov,const std::string &autor, const std::string &zanr, int godina_izdavanja);
   Korisnik &NadjiKorisnika(int clanski_broj);
   Knjiga &NadjiKnjigu(int evidencijski_broj);
   void IzlistajKorisnike() const;
   void IzlistajKnjige() const;
   void ZaduziKnjigu(int evidencijski_broj,int clanski_broj);
   void RazduziKnjigu(int evidencijski_broj);
   void PrikaziZaduzenja(int clanski_broj) const;
};
void Biblioteka:: RegistrirajNovogKorisnika(int clanski_broj,const std::string &ime,const std::string &prezime,const std::string &adresa,const std::string &telefon){
    auto it(korisnici.find(clanski_broj));
    if(clanski_broj==it->first) throw std::logic_error("Korisnik vec postoji");
    Korisnik k;
    k.ime=ime; k.prezime=prezime;k.adresa=adresa;k.telefon=telefon;
    auto pok=std::make_shared<Korisnik>(k);
    korisnici.insert(std::make_pair(clanski_broj,pok));
    
}
void Biblioteka::RegistrirajNovuKnjigu(int evidencijski_broj,const std::string &naslov,const std::string &autor, const std::string &zanr, int godina_izdavanja){
    
    auto it(knjige.find(evidencijski_broj));
    if(evidencijski_broj==it->first) throw std::logic_error("Knjiga vec postoji");
    auto pok=std::make_shared<Knjiga>(naslov,autor,zanr,godina_izdavanja);
    knjige.insert(std::make_pair(evidencijski_broj,pok));
}
Korisnik &Biblioteka::NadjiKorisnika(int clanski_broj){
    auto p(korisnici.find(clanski_broj));
    if(p==korisnici.end()) throw std::logic_error("Korisnik nije nadjen");
    return *p->second;
}
Knjiga &Biblioteka::NadjiKnjigu(int evidencijski_broj){
    auto p(knjige.find(evidencijski_broj));
    if(p==knjige.end()) throw std::logic_error("Knjiga nije nadjena");
    return *p->second;
}
void Biblioteka::IzlistajKorisnike() const{
    for(auto it=korisnici.begin();it!=korisnici.end();it++){
        std::cout<<"Clanski broj: "<<it->first<<std::endl
        <<"Ime i prezime: "<<(*it->second).ime<<" "<<(*it->second).prezime<<std::endl
        <<"Adresa: "<<(*it->second).adresa<<std::endl
        <<"Broj telefona: "<<(*it->second).telefon<<std::endl;
    }
}
void Biblioteka::IzlistajKnjige() const{
    for(auto it=knjige.begin();it!=knjige.end();it++){
        std::cout<<"Evidencijski broj: "<<it->first<<std::endl
        <<"Naslov: "<<(*it->second).DajNaslov()<<std::endl
        <<"Pisac: "<<(*it->second).DajAutora()<<std::endl
        <<"Zanr: "<<(*it->second).DajZanr()<<std::endl
        <<"Godina izdavanja: "<<(*it->second).DajGodinuIzdavanja()<<std::endl;
        
        if((*it->second).DajKodKogaJe()!=nullptr){
            std::cout<<"Zaduzena kod korisnika: "<<(*(*it->second).DajKodKogaJe()).ime<<" "<<(*(*it->second).DajKodKogaJe()).prezime<<std::endl;
        }
    }
}
void Biblioteka::ZaduziKnjigu(int evidencijski_broj, int clanski_broj){
    auto p(knjige.find(evidencijski_broj));
    if(p==knjige.end()) throw std::logic_error("Knjiga nije nadjena");
    auto k(korisnici.find(clanski_broj));
    if(k==korisnici.end()) throw std::logic_error("Korisnik nije nadjen");
    if(knjige[evidencijski_broj]->DajKodKogaJe()!=nullptr) throw std::logic_error("Knjiga vec zaduzena");
    
    knjige[evidencijski_broj]->Knjiga::ZaduziKnjigu(*korisnici[clanski_broj]);
}
void Biblioteka::RazduziKnjigu(int evidencijski_broj){
    auto p(knjige.find(evidencijski_broj));
    if(p==knjige.end()) throw std::logic_error("Knjiga nije nadjena");
    if(knjige[evidencijski_broj]->DajKodKogaJe()==nullptr) throw std::logic_error("Knjiga nije zaduzena");
    knjige[evidencijski_broj]->Knjiga::RazduziKnjigu();
}
void Biblioteka::PrikaziZaduzenja(int clanski_broj) const{
    auto p(korisnici.find(clanski_broj));
    if(p==korisnici.end()) throw std::domain_error("Korisnik nije nadjen");
    bool provjera(false);
    
    for(auto it=knjige.begin();it!=knjige.end();it++){
        if(static_cast<const std::shared_ptr<Korisnik>>(it->second->DajKodKogaJe())==p->second){
            if(provjera) std::cout<<std::endl;
            
            provjera=true;
        std::cout<<"Evidencijski broj: "<<it->first<<std::endl
        <<"Naslov: "<<it->second->DajNaslov()<<std::endl
        <<"Pisac: "<<it->second->DajAutora()<<std::endl
        <<"Zanr: "<<it->second->DajZanr()<<std::endl
        <<"Godina izdavanja: "<<it->second->DajGodinuIzdavanja()<<std::endl;
        }
    }
    if(!provjera) std::cout<<"Nema zaduzenja za tog korisnika!";
}

int main ()
{




	return 0;
}