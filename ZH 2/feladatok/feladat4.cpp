#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class targy {
    string nev;
    int kredit;
    int jegy;
public:
    targy(string nev, int kredit, int jegy) : nev(nev), kredit(kredit), jegy(jegy) {}

    int getKredit() const { return kredit; }
    int getJegy() const { return jegy; }
    const string& getNev() const { return nev; }

    bool operator>(const targy& masik) {
        if (this->kredit == masik.kredit)
            return this->jegy > masik.jegy;
        return this->kredit > masik.kredit;
    }

    friend ostream& operator<<(ostream& os, const targy& ez) {
        os << ez.nev << ": " << ez.kredit << " kredit " << ez.jegy << " lett!";
        return os;
    }
};

stringstream konv;
const string fajlnev = "adat4.csv";
vector<targy> targyak;

int main() {
    ifstream fajl(fajlnev);
    if (!fajl.good()) {
        cout << "Nem sikerult a(z) " << fajlnev << " nevu fajlt megnyitni!" << endl;
        return -1;
    }

    string sor;
    while (!fajl.eof()) {
        getline(fajl, sor);

        // Rossz adatok kiszűrése
        int pontosvesszok = 0;
        for (int i = 0; i < sor.length(); i++)
            if (sor[i] == ';') pontosvesszok++;
        
        if (sor.empty() || pontosvesszok != 2) continue;
        
        // Sor tartalmának feldolgozása
        size_t vesszohely = sor.find(';');
        string nev = sor.substr(0, vesszohely);
        int kredit;
        int jegy;

        sor = sor.substr(vesszohely + 1);
        
        vesszohely = sor.find(';');
        konv << sor.substr(0, vesszohely) << endl;
        konv >> kredit;
        konv << sor.substr(vesszohely + 1) << endl;
        konv >> jegy;

        targyak.push_back(targy(nev, kredit, jegy));
    }

    // Rendezés lambdafüggvénnyel
    sort(targyak.begin(), targyak.end(), [](const targy& egyik, const targy& masik) {
        if (egyik.getKredit() == masik.getKredit())
            return egyik.getJegy() > masik.getJegy();
        return egyik.getKredit() > masik.getKredit();
    });

    // Kreditszámítás
    int szumma = 0;
    for (const auto& i : targyak)
        szumma += i.getJegy() * i.getKredit() * (i.getJegy() != 1);
        // (i.getJegy() != 1) 1-es szorzó, ha nem 1 a jegy, és 0, ha igen, tehát nem számít KKI-be
    
    double KKI = double(szumma) / 30.0;
    // 3 a pontosság, mert a jegy 3 numerikus karakterből áll (tudom, hogy kicsit hülye, de ilyen a C++)
    cout << "A feleves KKI " << setprecision(3) << KKI << " volt!" << endl;

    int bukottPontok = 0;
    string bukottTargy = "Nem buktal";
    for (const auto& i : targyak) {
        if (i.getJegy() == 1) continue;
        int bukva = (5 - i.getJegy()) * i.getKredit();
        if (bukva > bukottPontok) {
            bukottPontok = bukva;
            bukottTargy = i.getNev();
        }
    }
    cout << "A legtöbb KKI pont a " << bukottTargy << " nevu targynal " << bukottPontok << " KKI pont volt!" << endl;

    // Bukott tárgyak gyűjtése
    bool vanBukott = false;
    for (const auto& i : targyak) {
        if (i.getJegy() == 1) {
            cout << i.getNev() << " el lett bukva" << endl;
            vanBukott = true;
        }
    }
    if (!vanBukott)
        cout << "Minden targy meg van ebben a felevben!" << endl;

    cout << "Melyik targy adatait akarod megtalalni? " << endl;
    string targyNev;
    getline(cin, targyNev);
    bool megvan = false;

    for (const targy& i : targyak) {
        if (i.getNev() == targyNev) {
            cout << i << endl;
            megvan = true;
            break;
        }
    }

    if (!megvan)
        cout << "Nincs ilyen targy!" << endl;

    fajl.close();
}
