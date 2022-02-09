/B2017/2018: Zadaća 4, Zadatak 3
#include <iostream>
#include <tuple>
#include <stdexcept>
#include <iomanip>
#include <algorithm>

using namespace std;

class Datum
{
    int dan,mjesec,godina;

    static int BrojDana(int mjesec, int godina) {
        int broj_dana[] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if(godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0)
            broj_dana[1]++;
        return broj_dana[mjesec - 1];
    }

    static bool IspravanDatum(int dan, int mjesec, int godina) {
        if (dan<=0||dan>BrojDana(mjesec,godina) || mjesec<=0||mjesec>12 || godina<0)
            return false;

        return true;
    }

public:
    Datum(int dan, int mjesec, int godina) {
        Postavi(dan,mjesec,godina);
    }
    void Postavi(int dan, int mjesec, int godina) {
        if(!IspravanDatum(dan,mjesec,godina)) throw domain_error("Neispravan datum");
        this->dan = dan;
        this->mjesec = mjesec;
        this->godina = godina;
    }
    std::tuple<int, int, int> Ocitaj() const {
        return tuple<int,int,int>(dan,mjesec,godina);
    }
    void Ispisi() const {
        cout<<dan<<"/"<<mjesec<<"/"<<godina;
    }
};



class Vrijeme
{
    int sati, minute;

    static bool IspravnoVrijeme(int sati, int minute) {
        if(sati<0||sati>23||minute<0||minute>59) return false;

        return true;

    }
public:
    Vrijeme(int sati, int minute) {
        Postavi(sati,minute);
    }
    void Postavi(int sati, int minute) {
        if(!IspravnoVrijeme(sati,minute)) {
            throw domain_error("Neispravno vrijeme");
        }
        this->sati = sati;
        this->minute = minute;
    }
    std::pair<int, int> Ocitaj () const {
        return make_pair(sati,minute);
    }
    void Ispisi() const {
        cout<< (sati<10?"0":"")<<sati<<":"<< (minute<10?"0":"")<<minute;
    }
};


class Pregled
{
    string ime_pacijenta;
    Datum datum_pregleda;
    Vrijeme vrijeme_pregleda;
public:
    Pregled(const string &ime_pacijenta, const Datum& datum_pregleda, const Vrijeme& vrijeme_pregleda):
        datum_pregleda(datum_pregleda),vrijeme_pregleda(vrijeme_pregleda) {
        this->ime_pacijenta = ime_pacijenta;
    }
    Pregled(const string& ime_pacijenta, int dan_pregleda, int mjesec_pregleda,int godina_pregleda, int sati_pregleda, int minute_pregleda):
        datum_pregleda(dan_pregleda,mjesec_pregleda,godina_pregleda),vrijeme_pregleda(sati_pregleda,minute_pregleda) {
        this->ime_pacijenta = ime_pacijenta;
    }
    void PromijeniPacijenta(const string& ime_pacijenta) {
        this->ime_pacijenta = ime_pacijenta;
    }
    void PromijeniDatum(const Datum&novi_datum) {
        this->datum_pregleda = novi_datum;
    }
    void PromijeniVrijeme(const Vrijeme& novo_vrijeme) {
        this->vrijeme_pregleda = novo_vrijeme;
    }
    string DajImePacijenta()const {
        return ime_pacijenta;
    }
    Datum DajDatumPregleda()const {
        return datum_pregleda;
    }
    Vrijeme DajVrijemePregleda()const {
        return vrijeme_pregleda;
    }
    static bool DolaziPrije(const Pregled &p1, const Pregled&p2) {
        int dan1,mjesec1,godina1;
        tie(dan1,mjesec1,godina1) = p1.datum_pregleda.Ocitaj();
        int dan2,mjesec2,godina2;
        tie(dan2,mjesec2,godina2) = p2.datum_pregleda.Ocitaj();

        pair<int,int> v1 = p1.vrijeme_pregleda.Ocitaj();
        pair<int,int> v2 = p1.vrijeme_pregleda.Ocitaj();

        if(godina1<godina2)return true;
        else if(godina1==godina2) {
            if(mjesec1<mjesec2)return true;
            else if(mjesec1==mjesec2) {
                if(dan1<dan2)return true;
                else if(dan1==dan2) {
                    if(v1.first<v2.first)return true;
                    else if(v1.first==v2.first) {
                        if(v1.second == v2.second)return true;
                    }
                }
            }
        }

        return false;
    }
    void Ispisi()const {
        cout<<left<<setw(30)<<ime_pacijenta;
        datum_pregleda.Ispisi();
        cout<<" ";
        vrijeme_pregleda.Ispisi();
        cout<<endl;
    }
};

class Pregledi
{
    Pregled**pregledi;
    int kapacitet;
    int broj_pregleda;
public:
    explicit Pregledi(int max_broj_pregleda) {
        this->kapacitet = max_broj_pregleda;
        pregledi = new Pregled*[max_broj_pregleda];
        broj_pregleda = 0;
    }
    Pregledi(std::initializer_list<Pregled> spisak_pregleda) {
        pregledi = new Pregled*[spisak_pregleda.size()];
        kapacitet = spisak_pregleda.size();
        broj_pregleda = spisak_pregleda.size();
        int i=0;
        for (auto it = spisak_pregleda.begin(); it!=spisak_pregleda.end(); it++) {
            pregledi[i++] = new Pregled(*it);
        }
    }
    ~Pregledi() {
        for (int i = 0; i < broj_pregleda; i++) {
            delete pregledi[i];
        }
        delete[] pregledi;
    }
    Pregledi(const Pregledi &p) {
        try {
            kapacitet = p.kapacitet;
            broj_pregleda = p.broj_pregleda;
            pregledi = new Pregled*[kapacitet];
            for (int i = 0; i < broj_pregleda; i++) {
                pregledi[i] = nullptr;
            }
            try {
                for (int i = 0; i < broj_pregleda; i++) {
                    pregledi[i] = new Pregled(*p.pregledi[i]);
                }
            } catch(bad_alloc) {
                for (int i = 0; i < broj_pregleda; i++) {
                    delete pregledi[i];
                }
                delete[] pregledi;
            }
        } catch(bad_alloc) {
            throw;
        }
    }
    Pregledi(Pregledi &&p) {
        broj_pregleda = p.broj_pregleda;
        kapacitet = p.kapacitet;
        pregledi = p.pregledi;
        p.pregledi = nullptr;
        p.broj_pregleda = 0;
    }
    Pregledi &operator =(const Pregledi &p) {
        if(this==&p) return *this;
        for(int i=0; i<broj_pregleda; i++)delete pregledi[i];
        delete[] pregledi;

        broj_pregleda = p.broj_pregleda;
        kapacitet = p.kapacitet;
        for (int i = 0; i < broj_pregleda; i++) {
            pregledi[i] = new Pregled(*p.pregledi[i]);
        }

        return *this;
    }
    Pregledi &operator =(Pregledi &&p) {
        if(this==&p) return *this;
        for(int i=0; i<broj_pregleda; i++)delete pregledi[i];
        delete[] pregledi;

        broj_pregleda = p.broj_pregleda;
        kapacitet = p.kapacitet;
        pregledi = p.pregledi;
        p.pregledi = nullptr;
        p.broj_pregleda=0;

        return *this;
    }
    void RegistrirajPregled(const std::string &ime_pacijenta,
                            const Datum &datum_pregleda, const Vrijeme &vrijeme_pregleda) {
        if(broj_pregleda == kapacitet) {
            throw range_error("Dostignut maksimalni broj pregleda");
        }

        pregledi[broj_pregleda++]= new Pregled(ime_pacijenta,datum_pregleda,vrijeme_pregleda);
    }
    void RegistrirajPregled(const std::string &ime_pacijenta, int dan_pregleda,
                            int mjesec_pregleda, int godina_pregleda, int sati_pregleda,
                            int minute_pregleda) {
        if(broj_pregleda==kapacitet) {
            throw range_error("Dostignut maksimalni broj pregleda");
        }
        pregledi[broj_pregleda++]=new Pregled(ime_pacijenta,dan_pregleda,mjesec_pregleda,godina_pregleda,sati_pregleda,minute_pregleda);
    }
    void RegistrirajPregled(Pregled *pregled) {
        if(broj_pregleda==kapacitet) {
            throw range_error("Dostignut maksimalni broj pregleda");
        }
        pregledi[broj_pregleda++]=pregled;
    }
    int DajBrojPregleda() const {
        return broj_pregleda;
    }
    int DajBrojPregledaNaDatum(const Datum &datum) const {
        int d,m,g;
        tie(d,m,g) = datum.Ocitaj();
        return count_if(pregledi,pregledi+broj_pregleda,[d,m,g](Pregled*p) {
            int dan,mjesec,godina;
            tie(dan,mjesec,godina) = p->DajDatumPregleda().Ocitaj();
            return dan==d && mjesec ==m && godina==g;
        });
    }
    Pregled &DajNajranijiPregled() {
        if(broj_pregleda==0)throw domain_error("Nema registriranih pregleda");
        return **min_element(pregledi, pregledi+broj_pregleda,[](Pregled*a,Pregled*b) {
            return Pregled::DolaziPrije(*a,*b);
        });
    }
    Pregled DajNajranijiPregled() const {
        if(broj_pregleda==0)throw domain_error("Nema registriranih pregleda");
        return **min_element(pregledi, pregledi+broj_pregleda,[](Pregled*a,Pregled*b) {
            return Pregled::DolaziPrije(*a,*b);
        });
    }
    void IsprazniKolekciju() {
        for (int i = 0; i < broj_pregleda; i++) {
            delete pregledi[i];
        }
        broj_pregleda=0;
    }
    void ObrisiNajranijiPregled() {
        if(broj_pregleda==0)throw range_error("Prazna kolekcija");
        Pregled** najraniji= min_element(pregledi, pregledi+broj_pregleda,[](Pregled*a,Pregled*b) {
            return Pregled::DolaziPrije(*a,*b);
        });

        int indeks_najranijeg = najraniji - pregledi;
        delete pregledi[indeks_najranijeg];
        for (int i = indeks_najranijeg; i < broj_pregleda-1; i++) {
            pregledi[i] = pregledi[i+1];
        }
        pregledi[broj_pregleda-1] = nullptr;
        broj_pregleda--;
    }

    void ObrisiPregledePacijenta(const std::string &ime_pacijenta) {
        for (int i = 0; i < broj_pregleda; i++) {
            if(pregledi[i]->DajImePacijenta() == ime_pacijenta) {
                delete pregledi[i];
                for(int j=i; j<broj_pregleda-1; j++) {
                    pregledi[j]=pregledi[j+1];
                }
                pregledi[broj_pregleda-1]=nullptr;
                broj_pregleda--;
            }
        }
    }

    void IspisiPregledeNaDatum(const Datum &datum) const {
        Pregledi p(kapacitet);
        int d,m,g;
        tie(d,m,g) = datum.Ocitaj();
        for (int i = 0; i < broj_pregleda; i++) {
            int dan,mjesec,godina;
            tie(dan,mjesec,godina) = pregledi[i]->DajDatumPregleda().Ocitaj();
            if( dan==d && mjesec ==m && godina==g) {
                p.RegistrirajPregled(new Pregled(*pregledi[i]));
            }
        }
        p.IspisiSvePreglede();
    }


    void IspisiSvePreglede() const {
        sort(pregledi,pregledi+broj_pregleda,[](Pregled*a,Pregled*b) {
            return Pregled::DolaziPrije(*a,*b);
        });

        for (int i = 0; i < broj_pregleda; i++) {
            pregledi[i]->Ispisi();
        }
    }
};
int main ()
{

    try {
        int kapacitet;
        cout<<"Unesite maksimalan broj pregleda: ";
        cin>>kapacitet;
        cin.ignore(1000,'\n');
        Pregledi p(kapacitet);

        while(true) {
            if(p.DajBrojPregleda()==kapacitet)break;
            string ime;
            cout<<"Unesite ime novog pacijenta ili 'kraj' za zavrsetak unosa: ";
            getline(cin,ime);
            if(ime=="kraj")break;
            cout<<"Unesite dan mjesec i godinu pregleda: ";
            int dan,mjesec,godina;
            cin>>dan>>mjesec>>godina;
            cout<<"Unesite sate i minute pregleda: ";
            int sati, minute;
            cin>>sati>>minute;
            cin.ignore(1000,'\n');
            p.RegistrirajPregled(ime, dan, mjesec, godina, sati, minute);
        }

        cout<<"Trenutno su registrovani sljedeci pregledi"<<endl;
        p.IspisiSvePreglede();
        
        
        while(true){
            cout<<"Odaberite jednu od sljedecih opcija\n1 - Broj pregleda na datum\n2 - Najraniji pregled\n3 - Obrisi pregled pacijenta\n4 - Obrisi najraniji pregled\n5 - Ispisi sve pregleda na datum\n6 - Ispisi sve preglede\n7 - Kraj programa"<<endl;
            int izbor;
            cin>>izbor;
            
           if(izbor==1){
               int d,m,g;
               cout<<"Unesite dan mjesec i godinu : ";
               cin>>d>>m>>g;
               cout<<"Broj pregleda na datum "<<d<<" "<<m<<" "<<g<<" je: "<<p.DajBrojPregledaNaDatum(Datum(d,m,g))<<endl;
           }
           else if(izbor==2){
               cout<<"Najraniji pregled je:"<<endl;
               p.DajNajranijiPregled().Ispisi();
           }
           else if(izbor==3){
               string pomocno_ime;
               cout<<"Unesite ime pacijenta: ";
                        cin.ignore(1000,'\n');
               getline(cin,pomocno_ime);
               int prije = p.DajBrojPregleda();
               p.ObrisiPregledePacijenta(pomocno_ime);
               int poslije = p.DajBrojPregleda();
               cout<<"Uspjesno obrisano "<<prije-poslije<<" pregleda"<<endl;
           }
           else if(izbor==4){
               p.ObrisiNajranijiPregled();
               cout<<"Najraniji pregled uspjesno obrisan"<<endl;
           }
           else if(izbor==5){
               int d,m,g;
               cout<<"Unesite dan mjesec i godinu : ";
               cin>>d>>m>>g;
               cout<<"Pregledi na datum "<<d<<" "<<m<<" "<<g<<" su:"<<endl;
               p.IspisiPregledeNaDatum(Datum(d,m,g));
           }
           else if(izbor==6){
               p.IspisiSvePreglede();
           }
           else if(izbor==7){
               break;
           }
        }
    } catch(domain_error e) {
        cout<<e.what()<<endl;
    } catch(range_error e) {
        cout<<e.what()<<endl;
    }
    return 0;

}
