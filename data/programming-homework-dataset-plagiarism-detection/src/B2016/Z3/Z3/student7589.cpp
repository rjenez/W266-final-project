#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template<typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr;
};
template<typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> mat) {
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}

template<typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona) {
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
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

template<typename TipElemenata>
void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat) {
    for(int i = 0; i < mat.br_redova; i++) 
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << ime_matrice << "(" << i+1 << "," << j+1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}

template<typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost = 6, bool treba_brisati = false) {
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << std::setprecision(preciznost)<<std::setw(sirina_ispisa) << mat.elementi[i][j];
        }
        std::cout << std::endl;
    }
    
    if(treba_brisati) UnistiMatricu(mat);
}

template<typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) 
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova,m1.br_kolona));
    for(int i = 0; i < m1.br_redova; i++) {
        for(int j = 0; j < m1.br_kolona; j++) {
            m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
        }
    }
    return m3;
    
}

template<typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2) {
    if(m1.br_kolona != m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
    try {
        auto m3(StvoriMatricu<TipElemenata>(m1.br_redova, m2.br_kolona));
        int p,d;
        for(int i = 0; i < m3.br_redova; i++)
            for(int j = 0; j < m3.br_kolona; j++) m3.elementi[i][j] = {} ;
    
        for(int i = 0; i < m1.br_redova; i++) {
            for(int j = 0; j < m2.br_kolona; j++) {
                for(int k = 0; k < m1.br_kolona; k++){
                    p = m1.elementi[i][k];
                    d = m2.elementi[k][j];
                    m3.elementi[i][j] += p*d;
                    
                }
            }
        }
        return m3;
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije" << std::endl;

    }
}

template<typename TipElemenata>
void MnozenjeSkalarom(Matrica<TipElemenata> &pomocna,const Matrica<TipElemenata> &m, double skalar) {
    for(int i = 0; i < pomocna.br_redova; i++) {
        for(int j = 0; j < pomocna.br_kolona; j++){
            pomocna.elementi[i][j] = m.elementi[i][j] * skalar;
        }
    }
}

template<typename TipElemenata>
void Zbir(const Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2){
    for(int i=0;i<m1.br_redova;i++){
        for(int j=0;j<m1.br_kolona;j++){
            m1.elementi[i][j]+=m2.elementi[i][j];
        }
    }
}

template<typename TipElemenata>
void Produkt(Matrica<TipElemenata> &m1,const Matrica<TipElemenata> &m2){
    auto m3(StvoriMatricu<TipElemenata>(m1.br_redova,m1.br_kolona));
    for(int i=0;i<m3.br_redova;i++){
        for(int j=0;j<m3.br_kolona;j++){
            m3.elementi[i][j]={};
        }
    }
    for(int i=0;i<m1.br_redova;i++){
        for(int j=0;j<m2.br_kolona;j++){
            for(int k=0;k<m1.br_kolona;k++){
                m3.elementi[i][j] += m1.elementi[i][k]*m2.elementi[k][j];
            }
        }
    }
    for(int i=0;i<m1.br_redova;i++){
        for(int j=0;j<m1.br_kolona;j++){
            m1.elementi[i][j]=m3.elementi[i][j];
        }
    }
    UnistiMatricu(m3);
}
template<typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &A, std::vector<double> koeficijenti) {
    if(A.br_redova != A.br_kolona) throw std::domain_error("Matrica mora biti kvadratna");
    try{
    auto I(StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona));
    for(int i = 0; i < I.br_redova; i++) {
        for(int j = 0; j < I.br_kolona; j++) {
            if(i == j) I.elementi[i][j] = 1;
            else I.elementi[i][j] = 0;
        }
    }
    
    auto polinom(StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona));
    for(int i = 0; i < polinom.br_redova; i++) {
        for(int j = 0; j < polinom.br_kolona; j++) {
            polinom.elementi[i][j] = 0;
        }
    }
    
    if(koeficijenti.size() == 0) { UnistiMatricu(I); return polinom; }
    
    auto pomocna(StvoriMatricu<TipElemenata>(A.br_redova, A.br_kolona));
    for(int i = 0; i < pomocna.br_redova; i++) {
        for(int j = 0; j < pomocna.br_kolona; j++)
            pomocna.elementi[i][j] = A.elementi[i][j];
    }
    auto pomocna2(StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona));
    //auto pomocna3(StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona));
    
    for(int i = 0; i < koeficijenti.size(); i++) {
        if(i == 0) {
            MnozenjeSkalarom(pomocna2,I,koeficijenti[i]);//
            //pomocna2 = 
            Zbir(polinom,pomocna2);
            UnistiMatricu(pomocna2);
        }
        else{
            auto pomocna3(StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona));
            MnozenjeSkalarom(pomocna3,pomocna,koeficijenti[i]);//(StvoriMatricu<TipElemenata>(A.br_redova,A.br_kolona));
            //pomocna2 = 
            Zbir(polinom,pomocna3);
            UnistiMatricu(pomocna3);
            Produkt(pomocna,A);
        }
    }
    
    UnistiMatricu(I);
    UnistiMatricu(pomocna);
    return polinom;
    }
    catch(std::bad_alloc){
        std::cout << "Nema dovoljno memorije" << std::endl;
    }
}

int main ()
{
    Matrica<double> a, b, c;
    int m;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> m;
    try {
        a = StvoriMatricu<double>(m,m);
      //  b = StvoriMatricu<double>(m,m);
        std::cout << "Unesite elemente matrice A: "<<std::endl;
        UnesiMatricu('A', a);
     
        std::vector<double> koeficijenti;
        int red;
        std::cout << "Unesite red polinoma: ";
        std::cin >> red;
        std::cout << "Unesite koeficijente polinoma: ";
        double k;
        for(int i = 0; i <= red; i++) {
            std::cin >> k;
            koeficijenti.push_back(k);
        }
        IspisiMatricu<double>(c = MatricniPolinom<double>(a, koeficijenti), 10, 6, false);
    }
    catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!";
    }
    UnistiMatricu(a);
    UnistiMatricu(b);
    UnistiMatricu(c);
	return 0;
}