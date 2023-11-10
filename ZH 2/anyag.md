# 2. ZH anyaga

# Öröklés (inheritancia)

Az OOP-ban gyakran egy osztály más osztályokra épül. Ez azt jelenti, hogy az eredeti osztály tulajdonságaihoz, függvényeihez van hozzáférése, de ezeket módotíhatja, és adhat is hozzá.  

Vegyünk egy alapesetet: van egy négyzet osztályunk, amiből többfajta négyszöget akarunk csinálni (például most téglalapot).

Az alaposztályunk:

```C++
class negyzet {
public:
    double a;
    negyzet(double a) : a(a) {}
};
```

Ahhoz, hogy egy objektumból örököljünk, az osztályunk neve után rakunk egy kettőspontot, és felsoroljuk, hogy mi(k)-ből örököl.  
Itt fontos megemlíteni a harmadik láthatósági opciót: a `protected`-et. Azt csinálja ez, hogy privát, DE ha egy osztály egy protected tulajdonságot örököl, tudja módosítani, a `private`-ot nem.  
Az inherintancia esetében is vannak ilyen láthatósági beállítások, és így dönthető el, hogy milyenként kezelhető az osztály az örökölt tulajdonságot (ezt nem kell fejből tudni *még*):

| Osztály tulajdonsága \\ Öröklés típusa | public | protected | private |
| :-- | :-: | :-: | :-: |
| **public** | public | protected | private |
| **protected** | protected | protected | private |
| **private** | Rejtett | Rejtett | Rejtett |

Ez alapján a négyzetünkből `public` öröklés kell:

```C++
class teglalap : public negyzet {
public:
    double b;

    // a-hoz még mindig hozzá tudunk férni
    teglalap(double a, double b) : a(a), b(b) {}
};
```

# Virtuális függvények

Két fajta módon lehet egy osztálynak függvénye: későn és korán kötött. Az korai kötésnél a fordító magától helyezi el a függvényhívást fordításkor, és mindig ugyanazt hívja. A késői kötésnél az osztálynak van egy ú.n. VMT-je, ami tartalmazza a függvények helyét (más szóval: függvénypointerei vannak az osztálynak), és ezt hívja futáskor.  
Mikor van haszna a későn kötésnek? A legegyszerűbb példája az, hogy *mindig* a jó függvényt hívjuk, még ha ide-oda váltunk típusokat is:

```C++
class negyzet {
public:
    double a;
    negyzet(double a) : a(a) {}

    double terulet() { return a * a; }
    double kerulet() { return 4 * a; }
}

class teglalap : public negyzet {
public:
    double b;
    teglalap(double a, double b) : a(a), b(b) {}

    double terulet() { return a * b; }
    double kerulet() { return 2.0 * (a + b); }
}

teglalap valt(5.0, 2.0);
std::cout << negyzet(valt).terulet << std::endl; // Hibás, 5 * 5 = 25-öt ír, mert negyzet függvényét hívja
```

Ezt virtuális függvényekkel meg lehet oldani:

```C++
class negyzet {
    // ...
    virtual double kerulet() { return 4 * a; }
    virtual double terulet() { return a * a; }
}

class teglalap : public negyzet {
    // ...
    virtual double terulet() override { return a * b; }
    virtual double kerulet() override { return 2.0 * (a + b); }
}

teglalap valt(5.0, 2.0);
std::cout << negyzet(valt).terulet << std::endl; // Jó, 5 * 2 = 10
```

Ha van egy alap osztályunk, amiből több objektum örököl úgy, hogy nincsen rajta a virtuális függvény implementálva, akkor kiírjuk a prototípusát, és hogy `= 0;`

Például:

```C++
// Alap ember osztály
class ember {
    std::string nev; // std::stringről lesz majd később szó

public:
    ember(std::string nev_p) : nev(nev_p) {}

    virtual double berSzamitas() = 0; // Ezen az objektumon nem tudunk bért számítani, az örököltökön viszont igen
}

// Mérnök
class mernok : public ember {
public:
    ember(std::string nev_p) : nev(nev_p) {}

    virtual double berSzamitas() override {
        return 900000 * 12;
    }
}

// Bölcsész
class bolcsesz : public ember {
public:
    bolcsesz(std::string nev_p) : nev(nev_p) {}

    virtual double berSzamitas() override {
        return 0;
    }
}
```

Azért léteznek a virtuális függvények, mivel van, amikor az ősosztállyal akarunk dolgozni, de a leszármazott függvényét használva. Például ha van egy rendszerünk, ami egy ablak elemeivel (gomb, szövegdoboz, stb.) dolgozik, akkor ezek mind egy közös ősosztállyal rendelkeznek, és így vannak (a pointereik) eltárolva egy tömbben, de ha ki akarjuk rajzolni, akkor a leszármazott függvényét hívja, tehát jól rajzolja a komponenset

# Az STL tárolók

Az STL tárolók olyan beépített könyvtárak, amik az adatok tárolását helyettünk oldják meg úgy, hogy akármilyen típussal dolgozhatnak. Az IPA-ban tanult tárolók (lineáris tömb, veremtár, láncolt lista, stb.) mind jelen van, de ezeknek a többsége szerencsére nem ZH anyag. Az itt mutatott kettő sem biztos fordul elő, de ha eddig problémáid voltak a tömbökkel, akkor itt van a tökéletes alternatíva.

## array: statikus hosszú tömb

A C++ `array` könyvtára egyszerűvé teszi a tömbök használatát.
Autómatikusan lehet elemeken átmenni rajta for ciklusban, a méretét egyszerűbb nézni, és ha félsz a kicímzésektől, akkor úgy is lehet elemeket elérni vele, hogy ezeket megakadályozza (de throw-ol, tehát arra is potenciálisan figyelni kell). Végül még sorrendbe is lehet rakni az elemeit a `sort` függvénnyel

```C++
#include <array>
#include <algorithm> //sort függvény
#include <iostream>

using namespace std;

int main() {
    array<int, 6> teszt = {1, 2, 3, 4, 5, 6};

    teszt[4] = 2; // Ugyanolyan, mint sima tömbnél, kicímezhet!

    teszt.at(5) = 0; // Ha ez egy try-catch blokkban van (ami természetesen nem kötelező), akkor kicímzés és error nélkül működik a kód, különben ugyanaz, mint az első példa

    cout << "A tömbnek " << teszt.size() << " eleme van, az ertekek a következok:" << endl;

    for (auto i : teszt) { // i automatikusan teszt elemével egyenlő, nem kell indexelni
        cout << i << ", ";
    }

    cout << endl;
    sort(teszt.begin(), teszt.end());
    for (const auto& i : teszt) {
        cout << i << ", ";
    }
}
/* Konzol: 
A tömbnek 6 eleme van, az ertekek a következök:
1, 2, 3, 4, 2, 0
0, 1, 2, 2, 3, 4
*/
```

## vector: dinamikus, bővíthető tömb

A `vector` a C++ egyik leghasznosabb, és leggyakrabban használt könyvtára. Ez egy olyan dinamikus tömb, aminek a végére lehet rakni elemeket, és magától átméretezi magát, tehát utólag is bővíthető.

Működésben hasonlít az `array`-re, de itt lehet dinamikus értékeket is használni, és a `push_back()` függvénnyel lehet új elemeket is rakni a tömb végére:

```C++
/*Példa leírása:
Van egy szövegfájlunk, aminek ismeretlen számú eleme van. Az elemek soronként vannak, és ki kell írni őket növekvő sorrendben. Minden elem szám (double), de üres sorok is lehetnek!*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const string fajlnev = "adatok.txt";

int main() {
    vector<double> adatok;
    ifstream fajl(fajlnev);
    if (!fajl.good()) {
        cout << "Nem sikerült a(z) " << fajlnev << " nevü fajlt megnyitni" << endl;
        return -1;
    }

    string sor;
    stringstream konv;
    while (!fajl.eof()) {
        getline(fajl, sor);
        if (sor.empty()) continue;
        
        double temp;
        konv << sor << endl;
        konv >> temp;

        adatok.push_back(temp); // A végére rakjuk az értéket, nem fog kicímezni, újraméretezi magát
    }

    sort(adatok.begin(), adatok.end());

    cout << "A rendezett adatok:" << endl;

    for (const auto& i : adatok)
        cout << i << "; ";

    fajl.close();
}
```
