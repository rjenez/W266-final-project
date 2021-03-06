/B2016/2017: Zadaća 3, Zadatak 4
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <stdexcept>
#include <iterator>
#include <set>
bool slovo(char c){if(c>='A'&&c<='Z'||c>='a'&&c<='z'||c>='0'&&c<='9') return true;
return false;}
std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> imena,int br){
    if(br>imena.size()||br<1) throw std::logic_error("Razvrstavanje nemoguce");
    std::list<std::string> lista;
    int vel=imena.size(),brojac=0,z=0;
    std::vector<std::set<std::string>>final(br);
    for(int i=0;i<imena.size();i++) lista.push_back(imena[i]);
    auto it=lista.begin();
    while(lista.size()!=0){
        int vel1;
        if(vel%br!=0){
            vel1=vel/br +1; vel-=vel1;
        }
        else{
            vel1=vel/br; vel-=vel1;
        }
        br--;
        for(int i=0;i<vel1;i++){
            int brojacitpomjeranja=0;
            while(brojacitpomjeranja!=brojac){
                brojacitpomjeranja++;
                if(brojacitpomjeranja==brojac) break;
                it++;
                if(it==lista.end()) it=lista.begin();
            }
            final[z].insert(*it);
            brojac=0;
            for(int i=0;i<(*it).size();i++) if(slovo((*it)[i])) brojac++;
            it=lista.erase(it);
             if(it==lista.end()) it=lista.begin();
        }
        z++;
    }
    return final;
} 
int main ()
{
    std::cout<<"Unesite broj djece: ";
    int n; std::cin>>n;
    std::cout<<"Unesite imena djece: "<<std::endl;
    std::vector<std::string> imena(n);
    std::cin.ignore(1000,'\n'); std::cin.clear();
    for(int i=0;i<n;i++)  std::getline(std::cin,imena[i]);
    std::cout<<"Unesite broj timova: ";
    int br; std::cin>>br;
    try{
    auto kek=Razvrstavanje(imena,br);
     for(int i=0;i<kek.size();i++){
        auto it=kek[i].begin(); int brojac=0;
        std::cout<<"Tim "<<i+1<<": ";
        while(brojac!=kek[i].size()-1){std::cout<<*it++<<", "; brojac++;}
        std::cout<<*it<<std::endl;
    }
    }catch(std::logic_error e){
        std::cout<<"Izuzetak: "<<e.what();
    }
	return 0;
} 
