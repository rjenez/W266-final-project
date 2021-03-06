/B2016/2017: Zadaća 3, Zadatak 5
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>

struct Dijete{
    std::string ime;
    Dijete *sljedeci;
};

Dijete *KopirajUKruznuListu(std::vector<std::string> &imena, Dijete *&cvor){
        Dijete *pocetak(nullptr), *prethodni;
        for(int i(0); i<int(imena.size()); i++){
            Dijete *novi(new Dijete);
            novi->ime=imena.at(i); novi->sljedeci=nullptr;
            if(!pocetak) pocetak=novi;
            else prethodni->sljedeci=novi;
            prethodni=novi;
            if(i==int(imena.size())-1){ novi->sljedeci=pocetak;}
        }
        cvor=pocetak;
        
        return prethodni;
}

int PomjeriZa(std::string &ime){
    int b(0);
    for(int i(0); i<int(ime.size()); i++){
        if(( ime.at(i)>='a' && ime.at(i)<='z' ) || (ime.at(i)>='A' && ime.at(i)<='Z') || (ime.at(i)>='0' && ime.at(i)<='9') ) b++;
    }
    return b;
}

std::set<std::string>JedanTim(Dijete *&trenutno, Dijete *&prethodni, int br_igraca){
    std::set<std::string>tim; 
    while(br_igraca!=0){
        tim.insert(trenutno->ime);
        std::string ime=trenutno->ime;
        int br_koraka(PomjeriZa(ime));
        if( prethodni==trenutno){
            delete trenutno; trenutno=nullptr;
            prethodni=nullptr;
            break;
        }
         Dijete *temp(trenutno);
        
         prethodni->sljedeci=trenutno->sljedeci;
         trenutno=trenutno->sljedeci;
         delete temp;
        
        for(int i(0); i<br_koraka-1; i++){
            prethodni=prethodni->sljedeci; trenutno=trenutno->sljedeci;
        }
        br_igraca--;
    }
    return tim;
}

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> &imena, int br_timova){
    if(br_timova<1 || br_timova>int(imena.size())) throw std::logic_error("Razvrstavanje nemoguce");
    
    Dijete *cvor, *prethodni;
    prethodni=KopirajUKruznuListu(imena,cvor);
    std::vector<std::set<std::string>> timovi;
    int mod(int(imena.size())%br_timova);
    
    for(int i(1); i<=br_timova; i++){
        if(i<=mod) timovi.push_back(JedanTim(cvor, prethodni,(int(imena.size())/br_timova)+1));
        else timovi.push_back(JedanTim(cvor,prethodni,int(imena.size())/br_timova));
    }
    
    return timovi;
}

void IspisiTimove(std::vector<std::set<std::string>> timovi, int br_timova){
    for(int i(0); i<br_timova; i++){
        std::cout<<"Tim "<<i+1<<": ";
        std::set<std::string> pomocni(timovi.at(i));
        for(auto it=pomocni.begin(); it!=pomocni.end(); it++){
            auto p=pomocni.end(); p--;
            if(it==p) std::cout<<*it;
            else std::cout<<*it<<", ";
        }
        std::cout<<std::endl;
    }
}

int main ()
{
    int n;
    std::cout<<"Unesite broj djece: ";
    std::cin>>n;
    
    std::cin.ignore(1000,'\n');
    
    std::vector<std::string> imena;
    std::cout<<"Unesite imena djece: "<<std::endl;
    for(int i(0); i<n; i++){
        std::string s;
        std::getline(std::cin, s);
        imena.push_back(s);
    }
    
    std::cout<<"Unesite broj timova: ";
    int br_timova;
    try{
        std::cin>>br_timova;
        std::vector<std::set<std::string>> timovi(Razvrstavanje(imena, br_timova));
        IspisiTimove(timovi, br_timova);
    }
    catch(std::logic_error izuzetak){
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
    
	return 0;
}