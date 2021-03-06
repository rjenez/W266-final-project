#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <stdexcept>

using std::list;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

typedef vector<std::set<string>> VektTimova;
typedef vector<list<string>::iterator> VektIteratora;

bool JesteSlovo(char karakter){
     if(karakter<'A' or (karakter>'Z' and karakter<'a') or karakter>'z')
        return false;
    return true;
}

bool JesteBroj(char karakter) {
    if(karakter>='0' and karakter <='9')
        return true;
    return false;
}

int BrojSlova(string ime){
    int brojac(0);
    for(int i=0; i<ime.size(); i++){
        if(JesteBroj(ime.at(i)) or JesteSlovo(ime.at(i))) brojac++;
    }
    return brojac;
}


VektTimova Razvrstavanje (vector<string> imena, int broj_timova){
    if(broj_timova<1 or broj_timova>imena.size()) throw std::logic_error("Razvrstavanje nemoguce");
    VektTimova timovi(broj_timova);
    list<string> lista_imena;
    for(int i=0; i<imena.size(); i++){
        lista_imena.push_back(imena.at(i));
    }
    int min_broj_clanova=imena.size()/broj_timova;
    int broj_vecih=imena.size()%broj_timova;
    list<string>::iterator izbaceni=lista_imena.begin(),novi_poc=lista_imena.begin(),novi_kraj=--lista_imena.end();
    for(int i=0; i<broj_timova; i++){
        int brojac;
        if(i<broj_vecih) brojac = min_broj_clanova+1;
        else brojac=min_broj_clanova;
        std::set<string> tim;
        while(brojac>0){
            tim.insert(*izbaceni);
            int br_slova(BrojSlova(*izbaceni));
            
            if(izbaceni==novi_poc or izbaceni==novi_kraj){ //Begin ni End vise nisu validni
                if(izbaceni==novi_poc)novi_poc++;
                else if(izbaceni==novi_kraj) novi_kraj--;
                lista_imena.erase(izbaceni);
                izbaceni=novi_poc;
            }
            
            else if(izbaceni!=novi_kraj and izbaceni!=novi_poc)
                izbaceni=lista_imena.erase(izbaceni);
            br_slova--; 
            
            while(br_slova>0){
                if(izbaceni==novi_kraj)
                    izbaceni=novi_poc;
                else izbaceni++;
                br_slova--;
            }
            brojac--;
        }  
        timovi.at(i)=tim;
    }
    return timovi;
}

int main ()
{
    cout<<"Unesite broj djece: ";
    int n,br_timova;
    cin>>n;
    cin.ignore(10000,'\n');
    vector<string> imena;
    cout<<"Unesite imena djece: "<<endl;
    for(int i=0; i<n; i++){
        string ime;
        getline(cin,ime);
        imena.push_back(ime);
    }
    cout<<"Unesite broj timova: ";
    cin>>br_timova;
    int brojac(1);
    try{
        auto timovi(Razvrstavanje(imena,br_timova));
        for(auto skup: timovi){
            cout<<"Tim "<<brojac<<": ";
            for(auto ime:skup){
                if(ime==*--skup.end()) cout<<ime;
                else cout<<ime<<", ";
            }
            cout<<endl;
            brojac++;
        }
    }
    catch(std::logic_error e){
        cout<<"Izuzetak: "<<e.what()<<endl;
    }
	return 0;
}