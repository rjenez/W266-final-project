/B2017/2018: Zadaća 5, Zadatak 1
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>

class Student {
    int indeks;
    std::string godina_studija;
    std::string imeiprezime;
    std::string adresa;
    std::string br_telefona;
    
    static bool NeispravanIndeks(int ind) {
        return (ind<9999 || ind>99999);
    }
    
    static bool NeispravnaGodina(std::string god) {
        const char* niz[11]{ "1", "2", "3", "1/B", "2/B", "3/B", "1/M", "2/M", "1/D", "2/D", "3/D" };
        for (int i=0; i<11; i++) if (niz[i]==god) return false;
        return true;
    }
    
    static bool Broj (char znak) { return znak>='0' && znak<='9'; } 
    
    static bool NeispravanBroj(std::string broj) {
        if (broj.length()<5) return true;
        std::string::iterator it(broj.begin());
        
        if (!Broj(*it)) return true;
        while (Broj(*it)) it++;
        if (it==broj.end()) return true;
        if (*it++!='/') return true;
        if (it==broj.end()) return true;
        if (!Broj(*it)) return true;
        
        while (Broj(*it)) it++;
        if (it==broj.end()) return false;
        if (*it++!='-') return true;
        if (it==broj.end()) return true;
        if (!Broj(*it)) return true;
        
        while (Broj(*it)) it++;
        if (it==broj.end()) return false;
        return true;
    }
    
    
    void IzbaciRazmake (std::string &s) {
        std::string pomocni;
        bool razmak(true);
        
        for (int i=0; i<s.length(); i++) {
            if (s.at(i)==' ') razmak=true;
            else if (razmak) {
                
                do {
                    pomocni.push_back(s.at(i));
                    i++;
                    if (i==s.length()) { s=pomocni; return; }
                } while (s.at(i)!=' ');
                pomocni.push_back(s.at(i));
                i--;
                razmak=false;
            }
        }
        int vel(pomocni.length());
        if (vel) {
            do {
                std::string::iterator it(pomocni.end()-1);
                if (*it!=' ') { s=pomocni; return; }
                pomocni.resize(vel-1);
                vel--;
            } while (vel);
        }
        s=pomocni;
    }
    
    
  public:
    Student(int indeks, std::string godina_studija, std::string imeiprezime, std::string adresa, std::string br_telefona) {
        if (NeispravanIndeks(indeks) || NeispravnaGodina(godina_studija) || NeispravanBroj(br_telefona)) throw std::domain_error("Neispravni parametri");
        IzbaciRazmake(imeiprezime);
        IzbaciRazmake(adresa);
        
        if (imeiprezime.length()==0 || adresa.length()==0) throw std::domain_error("Neispravni parametri");
        
        
        Student::indeks=indeks;
        Student::godina_studija=godina_studija;
        Student::imeiprezime=imeiprezime;
        Student::adresa=adresa;
        Student::br_telefona=br_telefona;
    }
    
    int DajIndeks() const { return indeks; }
    
    
    std::string DajGodinuStudija() const {
        if (godina_studija=="1") return "1/B";
        else if (godina_studija=="2") return "2/B";
        else if (godina_studija=="3") return "3/B";
        return godina_studija; 
    } 
    std::string DajImePrezime() const { return imeiprezime; }
    std::string DajAdresu() const { return adresa; }
    std::string DajTelefon() const { return br_telefona; }
    
    void Ispisi() const {
        std::cout << "Broj indeksa: " << DajIndeks() << std::endl;
        std::cout << "Godina studija: " << DajGodinuStudija() << std::endl;
        std::cout << "Ime i prezime: " << DajImePrezime() << std::endl;
        std::cout << "Adresa: " << DajAdresu() << std::endl;
        std::cout << "Telefon: " << DajTelefon() << std::endl;
    }
};

class Laptop {
    int ev_broj;
    std::string naziv;
    std::string karakteristike;
    Student* kod_koga_je;
  public:
    Laptop (int ev_broj, std::string naziv, std::string karakteristike) {
        if (ev_broj<0) throw std::domain_error("Neispravni parametri");
        Laptop::ev_broj=ev_broj;
        Laptop::naziv=naziv;
        Laptop::karakteristike=karakteristike;
        kod_koga_je=nullptr;
    }
    int DajEvidencijskiBroj() const { return ev_broj; }
    std::string DajNaziv() const { return naziv; }
    std::string DajKarakteristike() const { return karakteristike; }
    
    void Zaduzi(Student* s) {
        if (kod_koga_je) throw std::domain_error("Laptop vec zaduzen");
        kod_koga_je=s;
    }
    
    void Razduzi() {
        kod_koga_je=nullptr;
    }
    
    bool DaLiJeZaduzen() const { return kod_koga_je!=nullptr; }
    
    Student &DajKodKogaJe() const {
        if (!kod_koga_je) throw std::domain_error("Laptop nije zaduzen");
        return *kod_koga_je; 
    }
    Student *DajPokKodKogaJe() { return kod_koga_je; }
    
    void Ispisi() const {
        std::cout << "Evidencijski broj: " << DajEvidencijskiBroj() << std::endl;
        std::cout << "Naziv: " << DajNaziv() << std::endl;
        std::cout << "Karakteristike: " << DajKarakteristike() << std::endl;
    }
};


class Administracija {
    std::map<int, Student*> studenti;
    std::map<int, Laptop*> laptopi;
  public:
    Administracija() {}
    ~Administracija() {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if ((*it).second!=nullptr) { delete (*it).second; (*it).second=nullptr; }
        }
        for (auto it=studenti.begin(); it!=studenti.end(); it++) {
            if ((*it).second!=nullptr) { delete (*it).second; (*it).second=nullptr; }
        }
        studenti.clear();
        laptopi.clear();
    }
    
    Administracija(const Administracija &adm) {
        for (auto it=adm.studenti.begin(); it!=adm.studenti.end(); it++) {
            studenti.insert({it->first, new Student(*(it->second))});
        }
        for (auto it=adm.laptopi.begin(); it!=adm.laptopi.end(); it++) {
            laptopi.insert({it->first, new Laptop(*(it->second))});
        }
    }
    Administracija(Administracija &&adm) {
        std::swap(studenti, adm.studenti);
        std::swap(laptopi, adm.laptopi);
    }
    
    Administracija &operator =(const Administracija &adm) {
        if (this!=&adm) {
            for (auto it=studenti.begin(); it!=studenti.end(); it++) {
                if ((*it).second!=nullptr) { delete (*it).second; (*it).second=nullptr; }
            }
            for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
                if ((*it).second!=nullptr) { delete (*it).second; (*it).second=nullptr; }
            }
            studenti.clear();
            laptopi.clear();
            
            for (auto it=adm.studenti.begin(); it!=adm.studenti.end(); it++) {
                studenti.insert({it->first, new Student(*(it->second))});
            }
            for (auto it=adm.laptopi.begin(); it!=adm.laptopi.end(); it++) {
                laptopi.insert({it->first, new Laptop(*(it->second))});
            }
        }
        return *this;
    }
    
    Administracija &operator =(Administracija &&adm) {
        if (this!=&adm) {
            for (auto it=studenti.begin(); it!=studenti.end(); it++) {
                if ((*it).second!=nullptr) { delete (*it).second; (*it).second=nullptr; }
            }
            for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
                if ((*it).second!=nullptr) { delete (*it).second; (*it).second=nullptr; }
            }
            studenti.clear();
            laptopi.clear();
            
            std::swap(studenti, adm.studenti);
            std::swap(laptopi, adm.laptopi);
        }
        return *this;
    }
    
    void RegistrirajNovogStudenta (int indeks, std::string godina_studija, std::string imeiprezime, std::string adresa, std::string br_telefona) {
        for (auto it=studenti.begin(); it!=studenti.end(); it++) {
            if (indeks==(*((*it).second)).DajIndeks()) throw std::domain_error("Student s tim indeksom vec postoji");
        }
        Student* p(new Student(indeks, godina_studija, imeiprezime, adresa, br_telefona));
        studenti.insert({indeks, p});
        
    }
    
    void RegistrirajNoviLaptop (int ev_broj, std::string naziv, std::string karakteristike) {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if (ev_broj==(*((*it).second)).DajEvidencijskiBroj()) throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
        }
        Laptop* p(new Laptop(ev_broj, naziv, karakteristike));
        laptopi.insert({ev_broj, p});
    }
    
    Student &NadjiStudenta(int indeks) {
        for (auto it=studenti.begin(); it!=studenti.end(); it++) {
            if (indeks==(*((*it).second)).DajIndeks()) return *((*it).second);
        }
        throw std::domain_error("Student nije nadjen");
    }
    
    Student NadjiStudenta (int indeks) const {
        for (auto it=studenti.begin(); it!=studenti.end(); it++) {
            if (indeks==(*((*it).second)).DajIndeks()) return *((*it).second);
        }
        throw std::domain_error("Student nije nadjen");
    }
    
    Laptop &NadjiLaptop(int ev_broj) {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if (ev_broj==(*((*it).second)).DajEvidencijskiBroj()) return *((*it).second);
        }
        throw std::domain_error("Laptop nije nadjen");
    }
    
    Laptop NadjiLaptop (int ev_broj) const {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if (ev_broj==(*((*it).second)).DajEvidencijskiBroj()) return *((*it).second);
        }
        throw std::domain_error("Laptop nije nadjen");
    }
    
    void IzlistajStudente() const {
        for (auto it=studenti.begin(); it!=studenti.end(); it++) {
            (*((*it).second)).Ispisi();
            std::cout << std::endl;
        }
    }
    
    void IzlistajLaptope() const {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            (*((*it).second)).Ispisi();
            if ((*((*it).second)).DaLiJeZaduzen()) std::cout << "Zaduzio(la): " << (*((*it).second)).DajKodKogaJe().DajImePrezime() << " (" << (*((*it).second)).DajKodKogaJe().DajIndeks() << ")" << std::endl;
            std::cout << std::endl;
        }
    }
    
    void ZaduziLaptop (int indeks, int ev_broj) {
        
        
        Student &student(NadjiStudenta(indeks));
        Laptop &laptop(NadjiLaptop(ev_broj));
        
        if (laptop.DaLiJeZaduzen()) throw std::domain_error("Laptop vec zaduzen");
        
        
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if ((*((*it).second)).DaLiJeZaduzen()) {if ((*((*it).second)).DajKodKogaJe().DajIndeks()==indeks) throw std::domain_error("Student je vec zaduzio laptop"); }
        }
        
        laptop.Zaduzi(&student);
    }
    
    int NadjiSlobodniLaptop() {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if (!(*((*it).second)).DaLiJeZaduzen()) {
                return (*((*it).second)).DajEvidencijskiBroj();
            }
        }
        throw std::domain_error("Nema slobodnih laptopa");
    }
    
    void RazduziLaptop(int ev_broj) {
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if (ev_broj==(*((*it).second)).DajEvidencijskiBroj()) {
                if (!((*((*it).second)).DaLiJeZaduzen())) throw std::domain_error("Laptop nije zaduzen"); 
                (*((*it).second)).Razduzi();
                return;
            }
        }
        throw std::domain_error("Laptop nije nadjen");
    }
    
    void PrikaziZaduzenja() const {
        bool ima(false);
        for (auto it=laptopi.begin(); it!=laptopi.end(); it++) {
            if ((*((*it).second)).DaLiJeZaduzen()) {
                std::cout << "Student " << (*((*it).second)).DajKodKogaJe().DajImePrezime() << " (" << (*((*it).second)).DajKodKogaJe().DajIndeks() << ") zaduzio/la laptop broj " << (*((*it).second)).DajEvidencijskiBroj() << std::endl; 
                ima=true;
            }
        }
        if (!ima) std::cout << "Nema zaduzenja";
    }
    
};




int main ()
{
    try {
        //AT41 - (javni) Test klase Administracija - IzlistajLaptope

     Administracija etf;

    etf.RegistrirajNoviLaptop(123, "Dell", "CPU 3.0 GHz, 4 GB RAM");
    etf.RegistrirajNoviLaptop(331, "ASUS", "CPU 3.5 GHz, 2 GB RAM");
    etf.RegistrirajNoviLaptop(122, "Dell 2", "CPU 3.2 GHz, 6 GB RAM");


    etf.RegistrirajNovogStudenta(14212, "1","Benjamin", "Francuska revolucija 23", "12/34-56");
    etf.RegistrirajNovogStudenta(17528, "2","Ivan", "Trg vjecnih studenata 12", "048/597-585");
    etf.RegistrirajNovogStudenta(17525, "3", "Ante" ,"Trg vjecnih studenata 11", "062/582-757");

    etf.ZaduziLaptop(14212, 122);
    etf.ZaduziLaptop(17525,331);
    
        
        
        
        Administracija pmf(etf);
        
        etf.RazduziLaptop(331);
        etf.IzlistajLaptope();
        pmf.IzlistajLaptope();
     
    }
    catch (std::exception &iz) {
        std::cout << iz.what();
    }
	return 0;
}
