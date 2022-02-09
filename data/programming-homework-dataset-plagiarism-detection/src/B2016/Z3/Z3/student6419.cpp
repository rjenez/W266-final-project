/B2016/2017: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <new>
template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr;
};
template<typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona);       // dodao prototip
template<typename TipElemenata>
void UbaciUMatricu(const Matrica<TipElemenata> &mat, TipElemenata **Elementi) {
    for(int i(0); i<mat.br_redova; i++) {
        for(int j(0); j<mat.br_kolona; j++) {
            Elementi[i][j]=mat.elementi[i][j];
        }
    }
}
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat) {
    if(!mat.elementi) return;
    for(int i=0; i<mat.br_redova; i++) 
    delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> JedinicnaMatrica(const Matrica<TipElemenata> &a) {
    Matrica<TipElemenata> jedinicna(StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona));
    for(int i(0); i<a.br_redova; i++) {
        for(int j(0); j<a.br_kolona; j++) {
            if(i==j) jedinicna.elementi[i][j]=1;
            else jedinicna.elementi[i][j]=0;
        }
    }
    return jedinicna;
}
template<typename TipElemenata>
Matrica<TipElemenata> PomnoziKoeficijentom(const Matrica<TipElemenata> &a, double k) {
    Matrica<TipElemenata> rez(StvoriMatricu<TipElemenata> (a.br_redova, a.br_kolona));            
    for(int i(0); i<rez.br_redova; i++) {
        for(int j(0); j<rez.br_kolona; j++) {
            rez.elementi[i][j]=k*a.elementi[i][j];
        }
    }
    return rez;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona) {
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.elementi = new TipElemenata*[br_redova];
    for(int i=0; i<br_redova; i++) mat.elementi[i]=nullptr;
    try{
        for(int i=0; i<br_redova; i++)
            mat.elementi[i]=new TipElemenata[br_kolona];
    }
    catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &a, const Matrica<TipElemenata> &b) {
    if(a.br_kolona!=b.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica<TipElemenata> mat(StvoriMatricu<TipElemenata> (a.br_redova, b.br_kolona)); 
    for(int red(0); red<a.br_redova; red++) {
        for(int kolona(0); kolona<b.br_kolona; kolona++) {
            TipElemenata zbir(0);
            for(int i(0); i<a.br_kolona; i++) {
                zbir+=a.elementi[red][i]*b.elementi[i][kolona];
            }
            mat.elementi[red][kolona]=zbir;
        }
    }
    return mat;
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &a, std::vector<double> koeficijenti) {
    Matrica<TipElemenata> polinom;
    Matrica<TipElemenata> jedinicna;
    Matrica<TipElemenata> rezultat;
    Matrica<TipElemenata> b,c;
    if(a.br_kolona!=a.br_redova) throw std::domain_error("Matrica mora biti kvadratna");
    try {
        rezultat=StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona);
        polinom=StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona);
        jedinicna=StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona);
        UbaciUMatricu(b=JedinicnaMatrica(a), jedinicna.elementi);
        UnistiMatricu(b);
        UbaciUMatricu(a,polinom.elementi);
        if(koeficijenti.size()==0) {
            for(int i(0); i<polinom.br_redova; i++) {
                for(int j(0); j<polinom.br_kolona; j++) {
                    polinom.elementi[i][j]=0;
                }
            }
            UnistiMatricu(rezultat);
            UnistiMatricu(jedinicna);
            return polinom;
        }
        UbaciUMatricu(b=PomnoziKoeficijentom(jedinicna, koeficijenti[0]), rezultat.elementi);
        UnistiMatricu(b);
        for(int i(1); i<koeficijenti.size(); i++) {
            UbaciUMatricu(b=ZbirMatrica(rezultat,c=PomnoziKoeficijentom(polinom, koeficijenti[i])), rezultat.elementi);
            UnistiMatricu(b);
            UnistiMatricu(c);
            UbaciUMatricu(b=ProduktMatrica(polinom,a), polinom.elementi);
            UnistiMatricu(b);
        }
    }
    catch(...) {
        UnistiMatricu(rezultat);
        UnistiMatricu(polinom);
        UnistiMatricu(jedinicna);
        throw;
    }
    UnistiMatricu(jedinicna);
    UnistiMatricu(polinom);
    return rezultat;
}
template <typename TipElemenata>
void UnesiMatricu (char ime_matrice, Matrica<TipElemenata> &mat) {
    for(int i=0; i<mat.br_redova; i++) 
        for(int j=0; j<mat.br_kolona; j++) {
            std::cout << ime_matrice << "(" << i+1 << "," << j+1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}
template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false) {
    for(int i=0; i<mat.br_redova; i++) {
        for(int j=0; j<mat.br_kolona; j++) {
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
        }
        std::cout << std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije");
    Matrica<TipElemenata> m3(StvoriMatricu<TipElemenata> (m1.br_redova, m1.br_kolona));
    for(int i=0; i<m1.br_redova; i++)
        for(int j=0; j<m1.br_kolona; j++) 
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        return m3;
}
int main() {
    Matrica<double> a,c;
    int m, n;
    std::vector<double> koeficijenti;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> m;
    try {
        a = StvoriMatricu<double>(m, m);
        std::cout << "Unesite elemente matrice A: \n";
        UnesiMatricu('A', a);
        std::cout << "Unesite red polinoma: ";
        std::cin >> n;
        std::cout << "Unesite koeficijente polinoma: ";
        if(n>0) {
            for(int i(0); i<=n; i++) {
                double p;
                std::cin >> p;
                koeficijenti.push_back(p);
            }
        }
        if(n==0) std::cout << std::endl;
        IspisiMatricu(c=MatricniPolinom(a, koeficijenti), 10);
        UnistiMatricu(c);
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
    }
    UnistiMatricu(a);
    return 0;
}