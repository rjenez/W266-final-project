#include <iostream>
#include <vector>
#include <cmath>
typedef std::vector <int> vektor;
vektor IzdvojiGadne(vektor a,bool par) {
        vektor opaki;
        vektor odvratni;
        int i;
        for(int i=0;i<a.size();i++) {
                int k;
                int s=fabs(a[i]);
                vektor d;
                while(s!=0) {
                        k=s%3;
                        d.push_back(k);
                        s=s/3;
                        
                }
                vektor dobri;
                vektor losi;
                int br(0);
                int z;
                for(int f=0;f<3;f++) {
                        for(z=0;z<d.size();z++) {
                                if(d[z]==f) br++;
                        }
                        if(br==0) continue;
                        else if(br%2==0) dobri.push_back(d[z]);
                        else if(br%2!=0) losi.push_back(d[z]);
                        br=0;
                }
                if(dobri.size()!=0 && losi.size()==0) opaki.push_back(a[i]);
                if(dobri.size()==0 &&losi.size()!=0) odvratni.push_back(a[i]);
                br=0;
                for(int h=opaki.size()-1;h>=0;h--) {
                        for(int r=0;r<opaki.size();r++) {
                                if(opaki[r]==opaki[h]) br++;
                        }
                        if(br>1) opaki.erase(opaki.begin()+h);
                        br=0;
                }
                for(int m=odvratni.size()-1;m>=0;m--) {
                        for(int n=0;n<odvratni.size();n++) {
                                if(odvratni[n]==odvratni[m]) br++;
                        }
                        if(br>1) odvratni.erase(odvratni.begin()+m);
                        br=0;
                }
        }
        if(par==true) return opaki;
        else if(par==false) return odvratni;
}
int main ()
{
        int broj;
        std::cout<<"Unesite brojeve (0 za prekid unosa): ";
        vektor v;
        do{
                std::cin>>broj;
                if(broj==0) break;
                v.push_back(broj);
        } while(broj!=0);
        vektor opaki=std::move(IzdvojiGadne(v,true));
        vektor odvratni=std::move(IzdvojiGadne(v,false));
        std::cout<<"Opaki: ";
        for(int i=0;i<opaki.size();i++) {
                std::cout<<opaki[i]<<" ";
        }
        std::cout<<std::endl;
        std::cout<<"Odvratni: ";
        for(int i=0;i<odvratni.size();i++) {
                std::cout<<odvratni[i]<<" ";
        }
        
        return 0;
}