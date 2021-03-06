/B2016/2017: Zadaća 3, Zadatak 3
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
    struct Matrica {
        int br_redova, br_kolona;
        TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
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
                std::cout << ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
                std::cin >> mat.elementi[i][j];
            }
    }
template <typename TipElemenata>
    void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost = 6, bool treba_brisati = false) {
        for(int i = 0; i < mat.br_redova; i++) {
            for(int j = 0; j < mat.br_kolona; j++)
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
            std::cout << std::endl;
        }
        if(treba_brisati) UnistiMatricu(mat);
    }

template <typename TipElemenata>
    Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
        if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
        auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona));
        for(int i = 0; i < m1.br_redova; i++)
            for(int j = 0; j < m1.br_kolona; j++)
                m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        return m3;
    }
    
template <typename TipElemenata>
    Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
        if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
        try {
            auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona));
            for(int i(0); i < m1.br_redova; i++)
                for(int j(0); j < m2.br_kolona; j++) {
                    TipElemenata suma(0);
                    for(int k(0); k < m1.br_kolona; k++)
                        suma += m1.elementi[i][k] * m2.elementi[k][j];
                    m3.elementi[i][j] = suma;
                }
            return m3;
        }
        catch(...) { throw; }
    }
    
template <typename TipElemenata>
    Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &m, std::vector<double> v) {
        if(m.br_redova != m.br_kolona) throw std::domain_error("Matrica mora biti kvadratna");
        Matrica<TipElemenata> p;
        if(v.size() == 0) {
            try {
                p = StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona);
            }
            catch(...) { throw; }
            for(int i(0); i < p.br_redova; i++)
                for(int j(0); j < p.br_kolona; j++)
                    p.elementi[i][j] = 0;
            return p;
        }
        for(int i(0); i < v.size(); i++) {
            if(i == 0) {
                try {
                    auto jedinicna(StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona));
                        for(int j(0); j < m.br_redova; j++)
                            for(int k(0); k < m.br_kolona; k++) {
                                jedinicna.elementi[j][k] = 0;
                                if(j == k) jedinicna.elementi[j][k] = v[0];
                            }
                    p = jedinicna;
                }
                catch(...) { throw; }
            }
            else if(i == 1) {
                try {
                    auto pomocna(StvoriMatricu<TipElemenata>(m.br_redova, m.br_kolona));
                    for(int j(0); j < m.br_redova; j++)
                            for(int k(0); k < m.br_kolona; k++)
                                pomocna.elementi[j][k] = v[1] * m.elementi[j][k];
                    auto pomocna1(ZbirMatrica(p, pomocna));
                    UnistiMatricu(p);
                    p = pomocna1;
                    UnistiMatricu(pomocna);
                }
                catch(...) { throw; }
            }
            else {
                try {
                    auto pomocna(ProduktMatrica(m, m));
                    for(int j(i); j > 2; j--) {
                        auto pomocna1(ProduktMatrica(pomocna, m));
                        UnistiMatricu(pomocna);
                        pomocna = pomocna1;
                    }
                    for(int j(0); j < pomocna.br_redova; j++)
                        for(int k(0); k < pomocna.br_kolona; k++)
                            pomocna.elementi[j][k] *= v[i];
                    auto pomocna1(ZbirMatrica(p, pomocna));
                    UnistiMatricu(p);
                    p = pomocna1;
                    UnistiMatricu(pomocna);
                }
                catch(...) { throw; }
            }
        }
        return p;
    }

int main() {
    Matrica<double> a; // AUTOMATSKA INICIJALIZACIJA!!!
    int m;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> m;
    try {
        a = StvoriMatricu<double>(m, m);
        std::cout << "Unesite elemente matrice A:\n";
           UnesiMatricu('A', a);
        std::cout << "Unesite red polinoma: ";
        int p;
        std::cin >> p;
        std::vector<double> v(p + 1);
        std::cout << "Unesite koeficijente polinoma: ";
        for(int i(0); i < p + 1; i++)
            std::cin >> v[i];
        Matrica<double> b(MatricniPolinom(a,v));
        IspisiMatricu(b, 10);
        UnistiMatricu(a);
        UnistiMatricu(b);
    }
    catch(...) {}
    
    return 0;
}