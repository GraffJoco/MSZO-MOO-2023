#include <iostream>
#include <fstream>

class adatfeldolgozo {
    double* bevetelek;
    double* kiadasok;
    int elemszam;

public:
    adatfeldolgozo(const char* fajl) {
        std::ifstream input(fajl);
        if (!input.good()) {
            std::cout << "Nem sikerult az " << fajl << " fajlt megnyitni!";
            exit(-1);
        }

        input >> elemszam;

        if (elemszam < 1) {
            std::cout << "Rossz elemszam lett kiolvasva!";
            input.close();
            exit(-1);
        }

        bevetelek = new double[elemszam];
        kiadasok = new double[elemszam];
        char buff; // Ez azért van itt, mert a ;-t is valamibe be kell olvasni
        // Értelmesebb lenne fscanf-et használni, de a C++ konziban nem lehet C kód :(

        for (int i = 0; i < elemszam; i++)
            input >> bevetelek[i] >> buff >> kiadasok[i];

        input.close();
    }

    ~adatfeldolgozo() {
        delete[] kiadasok;
        delete[] bevetelek;
    }

    inline int getElemSzam() { return elemszam; }
    
    double osszBevetelek() {
        double sum = 0;
        for (int i = 0; i < elemszam; i++)
            sum += bevetelek[i];
        return sum;
    }

    double atlagProfit() {
        double profit = 0;
        for (int i = 0; i < elemszam; i++)
            profit += bevetelek[i] - kiadasok[i];
        
        return profit / elemszam;
    }
};

int main() {
    adatfeldolgozo adatok("ZH 1\\feladatok\\adat3.csv");

    std::cout << adatok.getElemSzam() << " elembol osszesen " <<
        adatok.osszBevetelek() << " bevetel, atlag " <<
        adatok.atlagProfit() << " profit elemenkent" << std::endl; 
}