#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class adatfeldolgozo {
    double bevetelek, kiadasok;
    unsigned int elemszam;
public:
    adatfeldolgozo(string fajlnev) : bevetelek(0), kiadasok(0), elemszam(0) {
        ifstream fajl(fajlnev);
        stringstream converter;
        string sor;
        if (!fajl.is_open()) {
            std::cout << "Nem sikerult a(z) \"" << fajlnev << "\" fajlt megnyitni!" << endl;
            exit(-1);
        }

        while (!fajl.eof()) {
            getline(fajl, sor);
            if (sor.length() == 0) continue;

            string bevs, kiads;
            size_t elvHely = sor.find(";");
            if (elvHely == string::npos) continue;
            bevs = sor.substr(0, elvHely);
            kiads = sor.substr(elvHely + 1);

            double tempBev, tempKiad;
            converter << bevs << endl;
            converter >> tempBev;

            converter << kiads << endl;
            converter >> tempKiad;

            elemszam++;
            bevetelek += tempBev;
            kiadasok += tempKiad;
        }

        fajl.close();
    }

    unsigned int elemek() { return elemszam; }

    double atlagprofit() {
        return (bevetelek - kiadasok) / elemszam;
    }

};

const string inputfajl = "ZH 1\\feladatok\\adat3.csv";

int main() {
    adatfeldolgozo adatok(inputfajl);
    
    cout << adatok.elemek() << " elembol " << adatok.atlagprofit() << " Ft atlag profit lett" << endl;
}