#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <stdexcept>

int VelicinaImena(std::string ime){
    int sajz=ime.length();
    int brojitelj=ime.length();
    for(int i(0);i<sajz;i++){
        if(!((ime[i]>='A' && ime[i]<='Z') || (ime[i]>='a' && ime[i]<='z') || (ime[i]>='0' && ime[i]<='9'))){
            brojitelj--;
        }
    }
    return brojitelj;
}

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> vektorstringova, int broj_timova){
    std::list<std::string> lista;
    std::set<std::string> set;
    int brojac(0);
    int clanovi=vektorstringova.size();
    std::vector<std::set<std::string>> vektorsetovskistringova;
    vektorsetovskistringova.resize(broj_timova);
    std::vector<int> vektor;
    vektor.resize(broj_timova);
    for(auto it=vektorstringova.begin();it!=vektorstringova.end();it++){
        lista.push_back(*it);
    }
    auto it2=lista.begin();
    if(broj_timova<1 || broj_timova>clanovi) throw std::logic_error ("Razvrstavanje nemoguce");
     for(int i(0);i<vektor.size();i++){
        vektor[i]=clanovi/broj_timova;}
        int preostali=clanovi-(clanovi/broj_timova)*broj_timova;
        int k(0);
        while(preostali!=0){
            vektor[k]++;
            preostali--;
            k++;
        }
    for(int i(0);i<vektorsetovskistringova.size();i++){
        while(brojac!=vektor[i]){
            int velicina=VelicinaImena(*it2);
            vektorsetovskistringova[i].insert(*it2);
            it2=lista.erase(it2);
              brojac++;
            for(int j(0);j<velicina-1;j++){
                if(it2==lista.end()) it2=lista.begin(); 
                it2++;
            }
            if(it2==lista.end()) it2=lista.begin();
            }
            brojac=0;
        }
    return vektorsetovskistringova;    
}

int main ()
{
    int br_djece;
    int br_timova;
    std::vector<std::string> imena_djecurlije;
    std::cout<<"Unesite broj djece: ";
    std::cin>>br_djece;
    std::cout<<"Unesite imena djece: "<<std::endl;
    
    for(int i(0);i<br_djece;i++){
        std::string dijete;
        std::cin>>std::ws;
        std::getline(std::cin,dijete);
        imena_djecurlije.push_back(dijete);
    }
    std::cout<<"Unesite broj timova: ";
    std::cin>>br_timova;
    std::vector<std::set<std::string>> finalni;
    try{
    finalni=Razvrstavanje(imena_djecurlije,br_timova);
    for(int i(0);i<finalni.size();i++){
        auto it=finalni[i].begin();
        auto it2=finalni[i].end();
        std::cout<<"Tim "<<i+1<<": ";
        int brojac(0);
        while(it!=it2){
            brojac++;
            if(brojac==finalni[i].size()) std::cout<<*it;
            else std::cout<<*it<<", ";
            it++;
        }
        std::cout<<std::endl;
    }
    }
    catch(std::logic_error e){
        std::cout<<"Izuzetak: "<<e.what()<<std::endl;
    }
    
	return 0;
}