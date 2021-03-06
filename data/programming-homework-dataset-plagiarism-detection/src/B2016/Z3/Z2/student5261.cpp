/B2016/2017: Zadaća 3, Zadatak 2
// Brz nastanak koda obasnjavam tako sto sam pogrijesio i ovaj zadatak uradio u folderu za zadatak 1 
// i onda sam samo prekopirao zadatak u ovaj folder!!


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

std::map<std::string, std::set<int>> KreirajIndeksPojmova (std::string s)
{
    std::map<std::string, std::set<int>> m;
    std::vector<std::string> dio;
    for(int i=0; i<s.length(); i++)
    {
        if(s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] = s[i] - 32;
        }
    }
    int pomocni(0);
    for(int i=0; i<s.length(); i++)
    {
        if(!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')))
        {
            dio.push_back(s.substr(pomocni, i-pomocni));
            pomocni = i+1;
        }
    }
    //dio.push_back(s.substr(pomocni, s.length()-pomocni));
    
    for(int i=0; i<dio.size(); i++)
    {
        std::set<int> par;
        for(int j=0; j<s.length(); j++)
        {
            if(dio[i] == s.substr(j, dio[i].size()))   par.insert(j);
            if(j>0 && dio[i] == s.substr(j, dio[i].size())) par.insert(j);
        }
        m.insert(std::make_pair(dio[i], par));
    }
    return m;
}

std::set<int> PretraziIndeksPojmova (std::string s, std::map<std::string, std::set<int>> mapa)
{
    std::set<int> par;
    auto pretraga(mapa.find(s));
    if(pretraga == mapa.end())
    {
        throw std::logic_error ("Pojam nije nadjen");
    }

        for(auto i : (*pretraga).second)
        par.insert(i);
        
    
    
    return par;
}

void IspisiIndeksPojmova (std::map<std::string, std::set<int>> m)
{
    for(auto it = m.begin(); it != m.end(); it++)
    {
        std::cout << (*it).first << ": ";
        int brojac1(0);
        for(int i : (*it).second)
        {
            if(i != 0)
                brojac1 += i/i;
            if(i == 0)
                brojac1++;
        }
        int brojac2(0);
        for(int i : (*it).second)
        {
            brojac2++;
            if(brojac1 > brojac2)
                std::cout << i << ",";
            else 
                std::cout << i;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::string unesi;
    std::cout << "Unesite tekst: ";
    std::getline(std::cin, unesi);
    std::map<std::string, std::set<int>> a = KreirajIndeksPojmova(unesi);
    IspisiIndeksPojmova(a);
    while(true)
    {
        std::string str;
        std::cout << "Unesite rijec: ";
        std::getline(std::cin, str);
        if(str == ".") 
            break;
        try
        {
            std::set<int> b = PretraziIndeksPojmova(str, a);
            for(int x : b)
                std::cout << x << " ";
        }
        catch(std::logic_error)
        {
            std::cout << "Unesena rijec nije nadjena!";
        }
        std::cout<<std::endl;
    }
 /*   auto p = KreirajIndeksPojmova(unesi);
    for(int i=0; i<p.size(); i++)
    std::cout<<p[i]<<std::endl;*/
    return 0;
}