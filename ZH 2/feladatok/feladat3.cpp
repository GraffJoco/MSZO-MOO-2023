#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

class GPU {
    string nev;
    double GHz, ar;
public:
    GPU(string nev, double GHz, double ar): nev(nev), GHz(GHz), ar(ar) {}

    double FtPerGHz() const {return ar/GHz;}

    friend ostream& operator<<(ostream& os, const GPU& ez) {
        os << ez.nev << ": " << ez.GHz << " GHz" << ", " << ez.ar << " Ft";
        return os;
    }
};

const string fajlnev = "adat3.csv";
stringstream konv;

int main() {
    ifstream fajl(fajlnev);
    if (!fajl.good()) {
        cout << "Nem sikerult a(z) " << fajlnev << " nevu fajlt megnyitni!" << endl;
        return -1;
    }

    vector<GPU> kartyak;
    string sor;
    while (!fajl.eof()) {
        getline(fajl, sor);
        if (sor.empty()) continue;

        double GHz, ar;
        string nev;
        konv << sor;
        konv >> nev >> ar >> GHz;

        kartyak.push_back(GPU(nev, GHz, ar));
    }

    sort(kartyak.begin(), kartyak.end(), [](const GPU& egyik, const GPU& masik) {
        return egyik.FtPerGHz() < masik.FtPerGHz();
    });

    for (const auto& i : kartyak) {
        cout << i << endl;
    }

    fajl.close();
}