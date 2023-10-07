#include <iostream>
#include <fstream>
#include <string>

using namespace std; // Ha túl lusta vagy std:: használatához

class GPU {
    string nev;
    unsigned int ar; // Nincs negatív ár (amúgy sima int/double elfogadható)
    double GHz;
public:
    // Ahhoz, hogy new-val lehessen tömböt csinálni, kell csinálni egy "default constructort", ergo, mi legyen, ha nincsenek alapértékek?
    GPU() : nev(""), ar(0), GHz(0.0) {}

    GPU(string nev, unsigned int ar, double GHz) : nev(nev), ar(ar), GHz(GHz) {}
    double FtperGHz() {
        return ar / GHz;
    }

    const string& getNev() { return nev; }
};

int main() {
    // Neked ide nem kell mappastruktúrát raknod majd, a makefile-ommal van csak baj
    const string fajlNev = "ZH 1\\feladatok\\adat2.csv";
    ifstream fajl(fajlNev);

    // Sikertelen fájlbeolvasás esetén
    if (!fajl.good()) {
        cout << "A \"" << fajlNev << "\" nevu fajlt nem sikerult megnyitni!" << endl;
        return -1;
    }

    unsigned int GPUSzam;
    fajl >> GPUSzam;
    GPU* kartyak = new GPU[GPUSzam];

    for (unsigned int i = 0; i < GPUSzam; i++) {
        string tempNev;
        unsigned int tempAr;
        double tempGHz;

        fajl >> tempNev;
        fajl >> tempAr;
        fajl >> tempGHz;
        kartyak[i] = GPU(tempNev, tempAr, tempGHz);
    }

    unsigned int legjobb = 0, legrosszabb = 0;
    for (unsigned int i = 0; i < GPUSzam; i++) {
        if (kartyak[i].FtperGHz() > kartyak[legrosszabb].FtperGHz()) legrosszabb = i;
        if (kartyak[i].FtperGHz() < kartyak[legjobb].FtperGHz()) legjobb = i;
    }

    cout << "A legjobb GPU az " << kartyak[legjobb].getNev() << ", ami " << kartyak[legjobb].FtperGHz() << " Ft/GHz-es!" << endl;
    cout << "A legrosszabb GPU az " << kartyak[legrosszabb].getNev() << ", ami " << kartyak[legrosszabb].FtperGHz() << " Ft/GHz-es!" << endl;

    // Fájl bezárásáról ne feledkezz meg!
    fajl.close();
}