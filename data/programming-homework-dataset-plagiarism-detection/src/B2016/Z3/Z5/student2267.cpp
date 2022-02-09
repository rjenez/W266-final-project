#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>

struct Dijete{
    std::string ime;
    Dijete *sljedeci;
};

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> v_string,int k){
    
    if(k==0 || k>v_string.size()) throw std::logic_error("Razvrstavanje nemoguce");
    
    std::vector<std::set<std::string>> v_skup;
    std::vector<int> br_clanova;
    int d_liste(v_string.size());
    int n=v_string.size();
    int temp=(int)(n%k);
    int poc=(int)((n/k)+1);
    int ostatak=n/k;
    int brojac(0);
    if(temp!=0){
        while(brojac<temp){
            
            br_clanova.push_back(poc);
            brojac++;
        }
        while(brojac<k){
            
            br_clanova.push_back(ostatak);
            brojac++;
        }
}
    
    else if(temp==0){
        
        while(brojac<k){
            br_clanova.push_back(ostatak);
            brojac++;
            
        }    
    }
    

 Dijete *pocetak,*prethodni;
 
 int br(0),p(0);
 for(;;){
     if(br==0)   {
         pocetak=nullptr;
         prethodni=nullptr;}
     if(br==v_string.size()){
         prethodni->sljedeci=pocetak;
         break;
     }
    Dijete *novi;
    novi=new Dijete;
    novi->ime=v_string[br]; novi->sljedeci=nullptr;
    if(!pocetak)    {
        pocetak=novi;
       }
    else    prethodni->sljedeci=novi;
    prethodni=novi;
    br++;

 }

 
 int i(0),idi_dalje(0);


     while(idi_dalje<k){
          int keep_going(0);  
          std::set<std::string> skup;
      while(keep_going<br_clanova[i]){
         std::string rijec;
         rijec=pocetak->ime;
          
         int br(0),duzina(0),o(0);
         //Brojimo slova
        while(o<rijec.size()){
            if((rijec[o]>='A' && rijec[o]<='Z') || (rijec[o]>='a' && rijec[o]<='z') || (rijec[o]>='0' && rijec[o]<='9'))
                duzina++;
            o++;
        } 
    skup.insert(rijec);
     
    //brisanje
    Dijete* brisi_dijete;
    brisi_dijete=pocetak;
    pocetak=pocetak->sljedeci;
    prethodni->sljedeci=pocetak;
    delete brisi_dijete;
    d_liste--;
  
     if(d_liste==0) break;
         int pomjeri;
         pomjeri=duzina;
         pomjeri--;
         int m(0);
         auto pom=pocetak;
         while(m<pomjeri){
             prethodni=pom;
             pom=pom->sljedeci;
             m++;
         }
         pocetak=pom;
         keep_going++;
     

     }
     idi_dalje++;
     v_skup.push_back(skup);
     i++;
     
     }
 

    return v_skup;

}

int main ()
{
   
   int br_djece;
   std::cout<<"Unesite broj djece: ";
   std::cin>>br_djece;
   std::vector<std::string> v_djeca;
   std::cout<<"Unesite imena djece: ";
   std::cout<<std::endl;
   std::cin.ignore(1000,'\n');
   int i(0);
   while(i<br_djece){
       std::string rijec;
       std::getline(std::cin,rijec);
       v_djeca.push_back(rijec);
       i++;
   }
   int br_timova;
   std::cout<<"Unesite broj timova: ";
   std::cin>>br_timova;
   try{
   std::vector<std::set<std::string>> v(Razvrstavanje(v_djeca,br_timova));
   }
   
   catch(std::logic_error poruka){
       std::cout<<"Izuzetak: "<<poruka.what();
       return 0;
   }

      for(int i=0;i<br_timova;i++){
          std::set<std::string> skup;
          std::vector<std::set<std::string>> v(Razvrstavanje(v_djeca,br_timova));
          skup=v[i];
          std::cout<<"Tim "<<i+1<<": ";
          std::set<std::string>::iterator it;
         it=skup.begin();
          int brojac(0);
          while(it!=skup.end()){
              if(brojac==skup.size()-1){
                  std::cout<<*it;
                  break;
              }
              std::cout<<*it<<", ";
              it++;
              brojac++;
          }
          std::cout<<std::endl;
  
      }
   
	return 0;
}