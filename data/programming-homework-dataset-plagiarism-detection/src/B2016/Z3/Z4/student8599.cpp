/B2016/2017: Zadaća 3, Zadatak 4
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>
#include <iterator>
#include <stdexcept>
std::vector<int> BrojDeceUTimovima(int Br_Dece, int Br_timova){
    int c;
    c=Br_Dece%Br_timova;
    std::vector<int> v(Br_timova);
    for(int i=0; i<Br_timova; i++){
      if(c>0){
       v[i]=(Br_Dece/Br_timova)+1;
      c--;
      }
     else v[i]=Br_Dece/Br_timova; 
    }
    return v;
}
int BrojSlova(std::string s){
    int brojac(0);
    for(int i=0; i<s.size(); i++){
        if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9'))
            brojac++;
    }
    return brojac;
}

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> v, int Br_Timova){
        if(Br_Timova<1 || Br_Timova>v.size()) throw std::logic_error("Razvrstavanje nemoguce");
     std::vector<int> x(BrojDeceUTimovima(v.size(), Br_Timova));
     std::vector<std::set<std::string>> Skupovi(Br_Timova);
     std::list<std::string> lista;
    for(int i=0; i<v.size(); i++)
    lista.push_back(v[i]);
    int brojac;
    auto it(lista.begin());
     for(int j=0; j<Br_Timova; j++){
         int m(x[j]);
         while(m!=0){
         brojac=BrojSlova(*it);
         Skupovi[j].insert(*it);
         it=lista.erase(it);
         it--;
            while(brojac!=0){
             brojac--;
             it++;
             if(it==lista.end()){
                it=lista.begin();
         }
            }
        
        if(it==lista.end()) it=lista.begin();
        m--;
            
    }
     }
    return Skupovi;
}

int main ()
{
    int n;
    std::cout << "Unesite broj djece: ";
    std::cin >> n;
    std::cout << "Unesite imena djece: ";
    std::cin.ignore(10000, '\n');
    std::vector<std::string> v(n);
    for(int i=0; i<n; i++)
        std::getline(std::cin, v[i]);
    std::cout <<std::endl <<  "Unesite broj timova: ";
    int timovi;
    std::cin >> timovi;
    try{
    auto skup(Razvrstavanje(v, timovi));
    for(int i=0; i<timovi; i++){
        std::cout << "Tim " << i+1 << ": ";
        for(auto x=skup[i].begin(); x!=skup[i].end(); x++){
            if(x!=--skup[i].end())
         std::cout << *x << ", ";
         else std::cout << *x; 
        }
        std::cout << std::endl; 
    }
    }
    catch(std::logic_error izuzetak){
        std::cout << "Izuzetak: " << izuzetak.what();
    }
	return 0;
}