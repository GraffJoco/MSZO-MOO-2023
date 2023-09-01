# 1. ZH: Bevezetés

Az előző félévben a C nevű programnyelvet tanultuk. Ez a nyelv jó alapokat adott a programozáshoz (főleg az alacsony nyelvű programozáshoz), de nagyon hiányos, legalábbis a modern alternatívákhoz képest. Emiatt hozta létre Bjarne Stroustrup a C++-t, amit a C modernizált verziójának szánt. **Szinte minden C program C++-ban is működik módosítások nélkül, tehát ha valamit C-vel meg tudsz oldani, akkor C++-al is!**  
Ellentétben a C-vel, ami csak minimálisan fejlődött 1972 óta, a C++ gyakran új funkciókat kap, például a legujjabb verzió (C++23) 9 különböző könyvtárral bővítette a nyelvet. A C++ alapja viszont ugyanaz maradt a mai napig: C, de osztályokkal, és objektum orientált funkciókkal.  
Az osztályok elődjét már C-ben használtuk, ezek voltak a `struct`-ok, de az egyértelmű, hogy nagyon hiányosak, valójában csak több változót lehet egybe kombinálni velük. Az osztályok jóval több funkcióval rendelkeznek: például lehet külön függvénye az osztálynak (pl.: `obj.fv(param)`), konstruktora és destrukora (függvények, amiket létrehozáskor hívunk, pl.: `objektum szal(konstruktor_parameter)`), műveletek felülírása (pl.: egy vektor objektumnál a `vec1 + vec2` egy külön függvényt hív, ami elmondja a nyelvnek, hogy mit csináljon)

# Pár nem-objektum funkció

## Referenciak

Ha írsz egy függvényt, ami módosítja az egyik paraméterét, akkor C-ben pointerrel kell dolgozni, ami csúnya és veszélyes tud lenni. C++-ban referenciával meg lehet oldani anélkül, hogy pointerezzünk.

C-ben megoldás:

```C
// Kicímez, ha parameter NULL
void duplaz(double* parameter) {
    *parameter *= 2.0;
}

double ertek = 21.0;
duplaz(&ertek);
printf("%lf", ertek); // 42.0
```

C++-ban egyszerűbb:

```C++
// Nincs NULL referenciáknál, sosem címez ki
// & * helyett
void duplaz(double& parameter) {
    // Nem kell parameter előtt *
    parameter *= 2.0;
}

double ertek = 21.0;
duplaz(ertek); // Nincs &
printf("%lf", ertek);
```

## Az \<iostream\> és \<fstream\> könyvtár

C-ben a printf-et kezelni nem mindig egyszerű, ezért C++-ban az \<iostream\> könyvtár ezen javít. Itt egyszerűen `std::cout`-nak kell adni egymás után felsorolva a kiírandó dolgokat a `<<` művelettel (kicsit csúnyán néz ki, de szimpla)

C-ben:

```C
#include <stdio.h>

int main() {
    int elsoValt = 123;
    double masikValt = 89;

    printf("1. valtozo: %d, 2. valtozo: %lf\n", elsoValt, masikValt);
}
```

```C++
#include <iostream>

int main() {
    int elsoValt = 123;
    double masikValt = 89;

    std::cout << "1. valtozo: " << elsoValt << ", 2. valtozo: " << masikValt << std::endl; // std::endl helyett "\n" is lehet sorvége
}
```

## Namespace

Az előző példában biztos észrevettétek ezt a furcsa `::` műveletet, mi ez? Ez egy namespace, egy egyszerű módja annak, hogy kódot kategorizálj.  
Egy namespace nem csinál semmit sem egymagában, a benne lévő kódot viszont kívülről `Namespace::Elem` módon lehet hívni, tehát nem lesz olyan, hogy két különböző, de azonos nevű objektum/változó/függvény miatt nem működik a program.
Egy egyszerű példa az, ha egy `vector` nevű struktúrát akarunk létrehozni, akkor meg lehet baj nélkül csinálni, mert habár van a C++-ban `vector` objektum, a `std::` namespace elemeként külön azonosítója van, a fordító tudja, hogy melyik melyik

```C++
#include <vector>

namespace matek {
    struct vector {
        double x, y, z;
    };
}

int main() {
    // Nincs probléma, egyértelmű, hogy melyik melyik
    std::vector<int> egyikValt;
    matek::vector masikValt = { 0, 0, -9.81 };
}
```

## Túlterhelés és alapértékek

A függvénytúlterhelés, amit a C nem tud, azt jelenti, hogy ugyanolyan nevű függvényből lehet több különböző példány, *ha a paraméterlistájuk nem azonos*. A létező függvényeknek meg lehet megadni alapértékeket, amiket nem kell minden beíráskor megadni, ha nem különbözik ettől.

Példakód:

```C++
int szoroz(int a, int b) {
    return a * b;
}

// Nincs baj, mások a paraméterek
// b beírása nem szükséges, ha az alapértéket (2.0-t) akarjuk
double szoroz(double a, double b = 2.0) {
    return a * b;
}

int main() {
    int elso = szoroz(2, 5); // Első függvényt hívja
    double masodik = szoroz(3.0, 4.5); // Második függvényt hívja
    double harmadik = szoroz(5.0); // b helyett alapértéket használunk, tehát 5.0 * 2.0 = 10.0
}
```

## *new* és *delete*

C++-ban nem kell a malloc-kal szenvedni, helyette a `new` kulcsszó fog rémálmokat adni neked!
A mallochoz képest triviális ezt használni:

```C++
int* valtozo = new int;
int* ujTomb = new int[10];

// ...

delete valtozo;
delete[] ujTomb; // Tömböknél szögletes zárójel!
```

# Az osztályok alapjai

## *struct* függvényekkel

A C++ eredeti beceneve *"C osztályokkal"* volt, tehát természetesen ezen lesz a fókusz ebben a tárgyban.
A `struct` és `class` kulcsszó is használható létrehozásukra, csak egy alap különbség van közöttük, amiről kicsit később lesz szó. A legegyszerűbb különbség egy C és C++ `struct` között az, hogy lehet függvényeket belerakni, az elemeket a nevükkel, van `this->nev`-el lehet elérni:

```C++
struct Tanulo {
    char nev[64];
    int kor;
    double atlag;

    // Belső függvény:
    void print() {
        // this-> elhagyható
        std::cout << "Nev: " << nev << ", kor: "<< this->kor << ", atlag: " << this->atlag << std::endl;
    }
};

Tanulo Janos = { "Janos", 21, 4.59 };
Janos.print(); // Nev: Janos, kor: 21, atlag: 4.59
```

Azért, hogy az egyes funkciók értelme látható legyen, szépen lassan összerakunk egy komplex objektumot, ami tartalmaz minden szükségeset. Ez lesz a `vektor`:

```C++
struct vektor {
    double x, y, z;

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }
};
```

## Konstruktor és destruktor

A konstruktor és destruktor ugyanolyan, mint egy sima függvény, egy különbséggel: konstruktor objektum létrehozásakor, destruktort törlésekor hívunk. Például a konstruktor foglalhat memóriát, a destruktor meg felszabadíthatja. Ezeknek a függvényeknek nincsen típusa, és a nevük azonos az osztályéval, csak a destruktornál a név elé kell egy `~` jel is:

```C++
struct ember {
    char* nev;
    int kor;
    bool el;

    // konstruktor
    ember(char* nev_p, int nev_hossza, int kor_p, bool el_p = true) {
        nev = new char[nev_hossza];
        strncpy_s(nev, nev_hossza, nev_p, nev_hossza);
        kor = kor_p;
        el = el_p;
    }

    // destruktor
    ~ember() {
        delete[] nev;
    }
};

ember Endre("Endre", strlen("Endre"), 42);
```

Az elemek létrehozásánál gyakran van az, hogy a konstruktorban `elem = elem_parameter`, de ezt lehet egyszerűbben írni egy inicializálós listával:

```C++
struct ember {
    // ...
    ember(char* nev_p, int nev_hossza, int kor_p, bool el_p = true) : nev(new char[nev_hossza]), kor(kor_p), el(el_p) {
        // Csak a memóriaműveletet kell ide rakni
        strncpy_s(nev, nev_hossza, nev_p, nev_hossza);
    }
    // ...
};
```

Bővítsük ki a `vektor`-unkat egy konstruktorral is:

```C++
struct vektor {
    double x, y, z;

    vektor(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }
};
```

## Nyílvános és privát elemek/függvények

Azt említettem, hogy a `struct` és `class` között csak egy fő különbség van, az pedig az, hogy egy `struct` minden eleme alapból publikus, a `class`-nál meg privát. Ez mit is jelent?
Egy publikus elemhez akármi hozzányúlhat, hívhatja, módosíthatja. Ez problémákhoz vezethet, mert vannak elemek, amiknél azt akarjuk, hogy ne-, vagy csak egy-két függvény módosíthassa. Például ha csinálunk egy string objektumot, ami tárolja a hosszát is, nem akarjuk, hogy módosítsák azt, mert ebből kicímzés/memóriahiba lehet.
Az alapértelmezett beállítást úgy lehet felülírni, ha `public:` vagy `private:` kerül az elemek elé. Egymás után lehet privát és publikus elem, természetesen. Van egy harmadik opció is: a `protected`, erről viszont később lesz szó.

A stringpélda:

```C++
class string {
    // class, alapból privát minden
    char* str;
    int hossz;

    // Belső elemekhez persze hozzá akarunk férni, nem módosító célra, tehát például ha egy függvény adja vissza, akkor nem lesz baj
public:
    char* getStr() { return str; }
    int getHossz() { return hossz; }

    // Nyílvános konstruktorra/destruktorra szinte mindig szükség van
    string(char* str_p, int hossz) : str(new char[hossz]), hossz(hossz) {
        strncpy_s(str, hossz, str_p, hossz);
    }

    ~string() {
        delete[] str;
    }
}

string teszt("Tej #1", strlen("Tej #1"));
teszt.hossz = 51; // ERROR, privát elemet nem látunk, és módosítani sem tudjuk!
teszt.getHossz() = 51; // ERROR, függvény értéket ad vissza, ami nem módosítható változó
std::cout << teszt.getHossz(); // OK
```

A vektorunkat átírhatjuk class-á (ez ajánlott nem C-s objektumoknál), public elemekkel:

```C++
class vektor {
public:
    double x, y, z;

    vektor(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }
};
```

## Statikus elem

Egy osztály statikus eleme olyan elem, ami az osztály *minden* példányánál közös, ha az egyiknél módosítjuk, akkor az összesnél. Ezt nem a `.`, hanem a namespaces `::` operátorral lehet elérni:

```C++
class kor {
    static const double PI = 3.14159;

public:
    double R;
    
    // kor:: elhagyható objektumon belül
    double kerulet() { return 2.0 * R * kor::PI; }
    double terulet() { return R * R * PI; }
}
```

Például nézhetjük a vektorunknál, hogy egyszerre hány elem létezik:

```C++
class vektor {
    static int vektorokSzama = 0;
public:
    double x, y, z;

    vektor(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {
        vektorokSzama++;
    }

    ~vektor() { vektorokSzama--; }

    int hanyVektorVan() { return vektorokSzama; }

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }
};
```

## Barátok

A C++ osztályoknak lehetnek barátai is (több, mint neked, az biztos). Egy barát hozzáférhet privát elemekhez. Az objektumon belül kell a primitívjét, és a `friend` kulcsszót használni, hogy definiáljunk egy barátot.  
Például az előző példánkat úgy módosíthatjuk, hogy `hanyVektorVan` legyen külön függvény:

```C++
// Prototípus, hogy a fordító tudja, hogy létezik a függvény
int hanyVektorVan();

class vektor {
    static int vektorokSzama = 0;
public:
    double x, y, z;

    vektor(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {
        vektorokSzama++;
    }

    ~vektor() { vektorokSzama--; }

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }

    friend int hanyVektorVan();
};

int hanyVektorVan() {
    // vektorokSzama privát, de mivel barátja a függvénynek, hozzáférhetünk
    return vektor::vektorokSzama;
}
```
