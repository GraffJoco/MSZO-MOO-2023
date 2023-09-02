#include <iostream>
#include <stdlib.h>

template <typename T>
class matrix {
private: // class eleve privát, nem kell ezt kiírni
    unsigned int x, y;
    T** adatok;

public:
    matrix(unsigned int sorok, unsigned int oszlopok)
        : x(sorok), y(oszlopok), adatok(new T*[sorok]) {
        if (sorok == 0 || oszlopok == 0) {
            std::cout << "Error! Rossz érték van megadva a mátrix létrehozásakor! A kapott paraméterek: " << x << "; " << y << std::endl;
            exit(EXIT_FAILURE);
        }
        for (unsigned int i = 0; i < x; i++)
            adatok[i] = new T[oszlopok];
    }

    // Fel kell szabadítani a memóriát
    ~matrix() {
        // Sorrend fontos!
        for (unsigned int i = 0; i < x; i++)
            delete[] adatok[i];
        delete[] adatok;
    }

    T* operator[](unsigned int sor) {
        return adatok[sor];
    }

    matrix<T> operator+(matrix<T>& masik) {
        // "this" nem kötelező, de ajánlom, így egyértelmű, hogy melyik elem melyik mátrixhoz tartozik
        if (this->x != masik.x || this->y != masik.y) {
            std::cout << "Error! A két mátrix méretei nem azonosak!" << std::endl;
            exit(EXIT_FAILURE);
        }

        matrix<T> retMat(x, y);

        for (unsigned int i = 0; i < x; i++)
            for (unsigned int j = 0; j < y; j++)
                retMat[i][j] = this->adatok[i][j] + masik[i][j];
        
        return retMat;
    }

    void print() {
        std::cout << std::endl;
        for (unsigned int i = 0; i < x; i++) {
            for (unsigned int j = 0; j < y; j++)
                std::cout << adatok[i][j] << ',';
            
            std::cout << std::endl;
            }
    }
};

int main() {
    matrix<int> mat1(2, 3), mat2(2, 3);

    // feltöltjük elemekkel
    // erre gyorsabb megoldást írni, de ez most elég
    mat1[0][0] = 1; mat1[0][1] = 2; mat1[0][2] = 3;
    mat1[1][0] = 4; mat1[1][1] = 5; mat1[1][2] = 6;
    
    mat2[0][0] = 9; mat2[0][1] = 8; mat2[0][2] = 7;
    mat2[1][0] = 6; mat2[1][1] = 5; mat2[1][2] = 4;


    matrix<int> eredmeny = mat1 + mat2;
    eredmeny.print();
}