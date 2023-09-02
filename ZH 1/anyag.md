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

# Komplexebb objektumműveletek, és elemek

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
    static int vektorokSzama;
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

// Nem const statikus változót típuson kívül kell definiálni
int vektor::vektorokSzama = 0;
```

## Barátok

A C++ osztályoknak lehetnek barátai is (több, mint neked, az biztos). Egy barát hozzáférhet privát elemekhez. Az objektumon belül kell a primitívjét, és a `friend` kulcsszót használni, hogy definiáljunk egy barátot.  
Például az előző példánkat úgy módosíthatjuk, hogy `hanyVektorVan` legyen külön függvény:

```C++
// Prototípus, hogy a fordító tudja, hogy létezik a függvény
int hanyVektorVan();

class vektor {
    static int vektorokSzama;
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

vektor::vektorokSzama = 0;

int hanyVektorVan() {
    // vektorokSzama privát, de mivel barátja a függvénynek, hozzáférhetünk
    return vektor::vektorokSzama;
}
```

## Operátor túlterhelés

Hogy lehet, hogy a `std::cout`-ot a `<<` (biteltolás balra) művelettel hívjuk meg? Ez az operátor túlterhelés, amivel felülírhatunk egy beépített műveletet, és egy függvényt hívhatunk helyette. Az fontos, hogy kétoperandú műveletet (pl.: kivonás) csak kétoperandusúként, egyoperandusút egyoperandusúként lehet túlterhelni. Ezeket a túlterheléseket nem feltétlenül kell az osztályon belül definiálni, valamint akármilyen típusokkal megoldható.

Alap szintaxis (példaként az összeadás operátorral):

```C++
class vec2 {
public:
    int x, y;

    vec2(int x = 0.0, int y = 0.0) : x(x), y(y) {}

    vec2 operator+(vec2 masik) {
        return vec2(this->x + masik.x, this->y + masik.y);
    }
};

vec2 egyik(4, 2);
vec2 masik = egyik + vec2(2, 7); // masik = {6, 9}
```

Ennek használatával a `std::cout`-tal is kompatibilissá lehet tenni az objektumokat:

```C++
class vec2 {
    // ...

    friend std::ostream operator<<(std::ostream& os, const vec2& ez);
};

std::ostream operator<<(std::ostream& os, const vec2& ez) {
    os << "{ " << ez.x << "; " << ez.y << "}";
    return os;
}
```

Bővítsük a `vektor`-unkat:

```C++
int hanyVektorVan();

class vektor {
    static int vektorokSzama;
public:
    double x, y, z;

    vektor(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {
        vektorokSzama++;
    }

    ~vektor() { vektorokSzama--; }

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }

    // Matematikai műveletek
    vektor operator+(const vektor masik) {
        return vektor(this->x + masik.x, this->y + masik.y, this->z + masik.z);
    }
    vektor operator-(const vektor masik) {
        return vektor(this->x - masik.x, this->y - masik.y, this->z - masik.z);
    }
    // Konstanssal szorzás
    vektor operator*(double skalar) {
        return vektor(this->x * skalar, this->y * skalar, this->z * skalar);
    }
    // Skalár szorzás, lehet túlterhelni a * operátort többször is, más típust is adhat vissza
    vektor operator*(const vektor masik) {
        return this->x * masik.x + this->y * masik.y + this->z * masik.z;
    }

    // Értékadás, vektor&-t adunk vissza, mert így egy soron belül lehet még felhasználni a művelet eredményét

    // Ez ezesetben redundáns (felesleges), mivel egy az egyben másoljuk át a memóriát
    vektor& operator=(const vektor masik) {
        *this = masik;
        return *this;
    }
    vektor& operator+=(const vektor masik) {
        *this = *this + masik;
        return *this;
    }
    vektor& operator-=(const vektor masik) {
        *this = *this - masik;
        return *this;
    }
    vektor& operator*=(const double skalar) {
        *this = *this * skalar;
        return *this;
    }

    // Összehasonlítás
    bool operator<(vektor masik) {
        return this->hossz() < masik.hossz();
    }
    bool operator>(vektor masik) {
        return this->hossz() > masik.hossz();
    }
    bool operator==(vektor masik) {
        return this->x == masik.x && this->y == masik.y && this->z == masik.z;
    }

    friend int hanyVektorVan();
    friend std::ostream operator<<(std::ostream& os, const vektor& vec);
};

vektor::vektorokSzama = 0;

int hanyVektorVan() {
    return vektor::vektorokSzama;
}

std::ostream operator<<(std::ostream& os, const vektor& vec) {
    os << "{ " << vec.x << "; " << vec.y << "; " << vec.z " }";
    return os;
}
```

## Különböző fajta értékadások (egyenlőség operátor)

Az egyenlővé tétel (=) operátor alapból átmásolja az osztály összes memóriáját az egyik osztályból a másikba. Ez gyakran (például a `vektor`-unknál) tökéletes, de gyakran komoly gondokat okozhat. Például ha van egy pointer elemünk, és két osztály egyenlő, mindkettő fel próbálja szabadítani a memóriát, amikor a destruktort hívja a kód, tehát kicímez. Ezt úgy lehet megoldani, hogy külön műveletet definiálunk az ilyen osztályoknál a sima = helyett, valamint konstruktoroknál is lehet ilyet csinálni:

```C++
class string {
    char* str;
    int hossz;

public:
    char* getStr() { return str; }
    int getHossz() { return hossz; }

    string(char* str_p, int hossz) : str(new char[hossz]), hossz(hossz) {
        strncpy_s(str, hossz, str_p, hossz);
    }

    ~string() {
        delete[] str;
    }

    string(const string& masik) : str(new char[masik.hossz]), hossz(masik.hossz) {
        strncpy_s(str, masik.hossz, masik.str, masik.hossz);
    }

    string& operator=(string& masik) {
        // Ha str != nullptr, akkor fel kell szabadítani
        if (str != nullptr) delete[] str;

        this->hossz = masik.hossz;
        this->str = new char[masik.hossz];
        strncpy_s(str, hossz, masik.str, hossz);
    }
}
```

# Templatek

A C++ egyik fő trükke az úgy nevezett *"zero cost abstraction"* megoldások használata. Ez azt jelenti, hogy absztrakt kifejezések ugyanolyan gyorsan futnak, mintha te írtad volna meg optimalizáltam az algoritmust. Míg a C-ben a fordító vette a kódod, és egyszerűen átalakította gépi kóddá, a C++-ban a fordítóval jelentős mennyiségű munkát csináltathatsz meg úgy, hogy a fordított program nem lesz lassabb. Az egyik ilyen dolog az ú.n. template.  
Ez azt jelenti, hogy csak egy *mintát* csinálsz az osztályból, és megadod, hogy a C++ fordító mi alapján csináljon ebből külön típust. Erre a legegyszerűbb példa az, amikor típusfüggetlenné akarjuk tenni az osztályunk, vagy függvényünk.

Vegyük a következő C++ függvényt:

```C++
-double szoroz(const double a, const double b) {
    return a * b;
}
```

Mit csináljuk, ha int-et akarunk használni? lehet, hogy a paraméterekből *és* az eredményből int-et csinálunk `(int)` használatával, de ez lassú, és kerekítési hibákhoz vezethet. Viszont tudunk templatet csinálni helyette, és a fordító eldönti, hogy milyen típusokra hozzon létre változatokat a függvényből:

```C++
// Itt T a típus neve, amivel dolgozunk
template <typename T>
T szoroz(const T a, const T b) {
    return a * b;
}
```

Ha egy verzióját akarjuk használni, akkor a név és zárójelek között \<>-ben tudjuk megadni a típusparamétert:

```C++
double egyik = szoroz<double>(2.0, -1.0); // -2.0
int masik = szoroz<int>(23, 3); // 69
```

A fordító C++ szabványtól függően gyakran tudja értelmezni, hogy melyik verzió kell, tehát nem mindig kötelező kiírni a relációs jeleket:

```C++
// Nem mindig működik, de hasznos, amikor igen
double egyik = szoroz(2.0, -1.0);
int masik = szoroz(23, 3);
```

Ezt osztályokkal is meg lehet csinálni, tegyük `vektor`-t típusfüggetlenné

```C++
// Minden vektor-ral kapcsolatos függvénynél ki kell rakni!
template <typename T>
int hanyVektorVan();

template <typename T>
class vektor {
    static int vektorokSzama;
public:
    T x, y, z;

    vektor(T x = 0.0, T y = 0.0, T z = 0.0) : x(x), y(y), z(z) {
        vektorokSzama++;
    }

    ~vektor() { vektorokSzama--; }

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }

    vektor<T> operator+(const vektor<T> masik) {
        return vektor(this->x + masik.x, this->y + masik.y, this->z + masik.z);
    }
    vektor<T> operator-(const vektor<T> masik) {
        return vektor(this->x - masik.x, this->y - masik.y, this->z - masik.z);
    }
    
    vektor<T> operator*(double skalar) {
        return vektor(this->x * skalar, this->y * skalar, this->z * skalar);
    }

    vektor<T> operator*(const vektor<T> masik) {
        return this->x * masik.x + this->y * masik.y + this->z * masik.z;
    }

    vektor<T>& operator=(const vektor<T> masik) {
        *this = masik;
        return *this;
    }
    vektor<T>& operator+=(const vektor<T> masik) {
        *this = *this + masik;
        return *this;
    }
    vektor<T>& operator-=(const vektor<T> masik) {
        *this = *this - masik;
        return *this;
    }
    vektor<T>& operator*=(const T skalar) {
        *this = *this * skalar;
        return *this;
    }

    bool operator<(vektor<T> masik) {
        return this->hossz() < masik.hossz();
    }
    bool operator>(vektor<T> masik) {
        return this->hossz() > masik.hossz();
    }
    bool operator==(vektor<T> masik) {
        return this->x == masik.x && this->y == masik.y && this->z == masik.z;
    }

    friend int hanyVektorVan();
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const vektor<U>& vec);
};

template <typename T>
int hanyVektorVan() {
    return vektor<T>::vektorokSzama;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vektor<T>& vec) {
    os << "{ " << vec.x << "; " << vec.y << "; " << vec.z << " }";
    return os;
}

template <typename T>
int vektor<T>::vektorokSzama = 0;
```

# Öröklés (inheritancia)

Az OOP-ban gyakran egy osztály más osztályokra épül. Ez azt jelenti, hogy az eredeti osztály tulajdonságaihoz, függvényeihez van hozzáférése, de ezeket módotíhatja, és adhat is hozzá.  

Vegyünk egy alapesetet: van egy négyzet osztályunk, amiből többfajta négyszöget akarunk csinálni (például most téglalapot).

Az alaposztályunk:

```C++
class negyzet {
public:
    double a;

    negyzet(double a) : a(a) {}

    double terulet() { return a * a; }
    double kerulet() { return 4 * a; }
};
```

Ahhoz, hogy egy objektumból örököljünk, az osztályunk neve után rakunk egy kettőspontot, és felsoroljuk, hogy mi(k)-ből örököl.  
Itt fontos megemlíteni a harmadik láthatósági opciót: a `protected`-et. Azt csinálja ez, hogy privát, DE ha egy osztály egy protected tulajdonságot örököl, tudja módosítani, a `private`-ot nem.  
Az inherintancia esetében is vannak ilyen láthatósági beállítások, és így dönthető el, hogy milyenként kezelhető az osztály az örökölt tulajdonságot:

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

    double kerulet() { return 2 * a + 2 * b; }
    double terulet() { return a * b; }
};
```
