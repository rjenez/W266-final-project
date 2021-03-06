/B2016/2017: Zadaća 3, Zadatak 5

#include <iostream>
#include <string>
#include <set>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <list>
using std::string;
using std::cout;
using std::set;
using std::vector;
using std::list;

struct Dijete {
    string ime;
    Dijete *sljedeci;
};
int DuzinaStringa(string s)
{
    int br(0);
    for(int i = 0 ; i < s.size() ; i++ ) {
        if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') || (s[i]>='0' && s[i]<='9'))
            br++;
    }
    return br;
}

vector<set<string>> Razvrstavanje(vector<string> v , int k)
{
    vector<set<string>> vs;
    int n(int( v.size()));
    if(k<1 || k>n) throw std::logic_error ("Razvrstavanje nemoguce");
    int s(n/k);
    int ostatak(n%k);


    vector<int> br_clanova(k);
    for(int i=0 ; i<k ; i++) {
        br_clanova[i]=s;
        if(ostatak!=0 ) {
            br_clanova[i]++;
            ostatak--;
        }

    }


    Dijete *pocetak(nullptr), *prethodni(nullptr);
    for(int i = 0 ; i < v.size() ; i++ ) {
        Dijete *novi(new Dijete);
        novi->ime=v[i];
        novi->sljedeci = pocetak;
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni = novi ;
       
    }

    try{


    Dijete *pocetak(nullptr), *prethodni(nullptr), *novi(nullptr), *izbrisi(nullptr);
    for(int i = 0 ; i < v.size() ; i++ ){
        novi = new Dijete;
        novi->ime=v[i];
        novi->sljedeci = nullptr;
        if(!pocetak) pocetak=novi;
        else prethodni->sljedeci=novi;
        prethodni = novi ;
    }
    prethodni->sljedeci=pocetak;
    int i(0);

    n = int(v.size());
         while(pocetak!=prethodni){
         while(i<k){
             set<string> skup;

             for(int j=0; j<br_clanova[i] ;  j++){
                 if(pocetak==prethodni->sljedeci) izbrisi = pocetak;
                 else izbrisi = pocetak->sljedeci;
                 if(pocetak==prethodni->sljedeci) skup.insert(pocetak->ime);
                 else skup.insert(pocetak->sljedeci->ime);
                 int m(0);
                 if (pocetak==prethodni->sljedeci) m=DuzinaStringa(pocetak->ime);
                 else m=DuzinaStringa(pocetak->sljedeci->ime);
                 m--;
                 if (pocetak==prethodni->sljedeci) {
                    prethodni->sljedeci=pocetak->sljedeci;
                    pocetak=pocetak->sljedeci;
                }
                 if(pocetak->sljedeci==prethodni) pocetak=prethodni->sljedeci;
                 delete izbrisi;
                while(m>0){
                    pocetak = pocetak->sljedeci;
                    if(pocetak == prethodni) pocetak = prethodni->sljedeci;
                    m--;

                }

             }

            vs.push_back(skup);

            i++;
        }

         }
    }
    catch (std::bad_alloc){

    }



   




    return vs;
}
void IspisiSkupImena(set<string> skup)
{
    auto it(skup.begin());
    for(int i = 0; i < skup.size()-1 ; i++)
        std::cout << *it++ << ", ";
    std::cout << *it  ;
}
int main ()
{

    int n;
    cout<<"Unesite broj djece: ";
    std::cin>>n;
    std::cin.ignore(10000, '\n');
    cout<<"Unesite imena djece: ";

    vector<string> v;
    for(int i= 0 ; i<n ; i++) {
        string rijec;
        std::getline(std::cin, rijec);
        v.push_back(rijec);


    }
    cout<<std::endl;
    int k;
    cout<<"Unesite broj timova: ";
    std::cin>>k;
    try {
        vector<set<string>> vs;
        vs.resize(k);
        vs=Razvrstavanje(v,k);
        for(int i = 0 ; i < k ; i++ ) {
            cout<<"Tim "<<i+1<<": ";
            IspisiSkupImena(vs[i]);
            cout<<std::endl;
        }
    } catch(std::logic_error a) {
        cout<<a.what()<<std::endl;
    }

    return 0;
}







 
   