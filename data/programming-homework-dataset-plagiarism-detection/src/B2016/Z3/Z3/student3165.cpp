/B2016/2017: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>
template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr;
};
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat) {
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona) {
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova; mat.br_kolona = br_kolona;
    mat.elementi = new TipElemenata*[br_redova];
    for(int i = 0; i < br_redova; i++) mat.elementi[i] = nullptr;
    try {
        for(int i = 0; i < br_redova; i++)
        mat.elementi[i] = new TipElemenata[br_kolona];
    }
    catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}
template <typename TipElemenata>
void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat) {
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << ime_matrice<< "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}
template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost=6, bool treba_brisati=false) {
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa)<<std::setprecision(preciznost) << mat.elementi[i][j];
        std::cout << std::endl;
    }
    if(treba_brisati) UnistiMatricu(mat);
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona));
    for(int i = 0; i < m1.br_redova; i++)
        for(int j = 0; j < m1.br_kolona; j++)
        m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
    return m3;
}
template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona));
    for(int i(0); i<m1.br_redova; i++) {
        for(int j(0); j<m2.br_kolona; j++) {
            m3.elementi[i][j]=0;
            for(int k(0); k<m1.br_kolona; k++)
                m3.elementi[i][j]+=m1.elementi[i][k]*m2.elementi[k][j];
        }
    }
    return m3;
}
template<typename TipElemenata>
void MnozenjeSkalarom(Matrica<TipElemenata> m, double a) {
    for(int i(0); i<m.br_redova; i++)
        for(int j(0); j<m.br_kolona; j++)
            m.elementi[i][j]*=a;
}
template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom (const Matrica<TipElemenata> &m, std::vector<double> vektor) {
    if(m.br_redova!=m.br_kolona) throw std::domain_error("Matrica mora biti kvadratna");
    auto polinom(StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona));
    for(int i(0); i<polinom.br_redova; i++)
        for(int j(0); j<polinom.br_kolona; j++)
            polinom.elementi[i][j]=0;
    if(vektor.size()!=0) {
        for(int i(0); i<polinom.br_kolona; i++)
            for(int j(0); j<polinom.br_kolona; j++)
                if(i==j) polinom.elementi[i][j]=1;
        MnozenjeSkalarom(polinom, vektor[0]);
        auto pom(StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona));
        auto pom3(StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona));
        for(int i(0); i<pom.br_redova; i++)
            for(int j(0); j<pom.br_kolona; j++)
                pom.elementi[i][j]=m.elementi[i][j];
        for(int i(1); i<vektor.size(); i++){
            for(int i(0); i<pom3.br_redova; i++)
                for(int j(0); j<pom3.br_kolona; j++)
                    pom3.elementi[i][j]=pom.elementi[i][j];
            MnozenjeSkalarom(pom, vektor[i]);
            auto pom2=polinom;
            polinom=ZbirMatrica(polinom, pom);
            UnistiMatricu(pom2);
            if(vektor.size()>1 && i+1<vektor.size()) {
                auto pom4=pom;
                pom=ProduktMatrica(pom3, m);
                UnistiMatricu(pom4);
            }
        }
        UnistiMatricu(pom); UnistiMatricu(pom3);
    }
    return polinom;
}
int main() {
    Matrica<double> a;
    int m, n;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> m;
    try {
        a = StvoriMatricu<double>(m, m);
        std::cout << "Unesite elemente matrice A: \n";
        UnesiMatricu('A', a);
        std::cout<<"Unesite red polinoma: ";
        std::cin>>n;
        std::vector<double> v(n+1);
        std::cout<<"Unesite koeficijente polinoma: ";
        for(int i(0); i<v.size(); i++)
            std::cin>>v[i];
        IspisiMatricu(MatricniPolinom(a, v), 10, 6, true);
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!\n";
    }
    catch(std::domain_error poruka) {
        std::cout<<poruka.what()<<std::endl;
    }
    UnistiMatricu(a);
    return 0;
}