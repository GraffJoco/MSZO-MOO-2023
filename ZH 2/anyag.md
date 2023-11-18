# 2. ZH anyaga

# Operátor túlterhelés

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

    // Hossz
    double operator~() {
        return sqrt(x*x + y*y + z*z);
    }
};

vec2 egyik(4, 2);
vec2 masik = egyik + vec2(2, 7); // masik = {6, 9}
auto hossz = ~masik; // = 10,8166
```

Ennek használatával a `std::cout`-tal is kompatibilissá lehet tenni az objektumokat:

```C++
class vec2 {
    // ...

    friend std::ostream& operator<<(std::ostream& os, const vec2& ez);
};

std::ostream& operator<<(std::ostream& os, const vec2& ez) {
    os << "{ " << ez.x << "; " << ez.y << "}";
    return os;
}
```

## A ++ és -- operátor túlterhelése

A ++ és -- operátor egy speciális eset, ugyanis egyoperandusú, de a változó előtt és mögött is lehet. A pre-, és posztinkrementálás például ezesetben két különböző műveletnek számít, és ezért külön-külön lehet túlterhelni.  
A preinkrementálás esetében a normális túlterhelési metódust kell alkalmazni, a posztinkrementálásnál pedig egy int típusú paramétert is kell kérni, amit nem fogunk használni.

```C++
class vec2 {
    // Preinkrementálás
    vec2 operator++() {
        this->x++;
        return *this;
    }

    // Posztinkrementálás
    vec2 operator++(int) {
        const vec2 minuszEgy = vec2(-1, 0);
        this->x++;
        return *this + minuszEgy;
    }
};

vec2 origo(0, 0);
cout << origo++ << endl; // {0; 0}
cout << origo << endl; // {1; 0} posztinkrementálás növeli az értéket, de nem használja a számításokban

origo = vec2(0, 0);
cout << ++origo << endl; // {1; 0} preinkrementálás növeli az értéket, és használja is
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

**A következő anyagrész nem minden gyakveznél lesz számon kérve**  
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
    teglalap(double a, double b) : negyzet(a), b(b) {}

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
class ember abstract {
    std::string nev; // std::stringről lesz majd később szó

public:
    ember(std::string nev_p) : nev(nev_p) {}

    virtual double berSzamitas() = 0; // Ezen az objektumon nem tudunk bért számítani, az örököltökön viszont igen
}

// Mérnök
class mernok : public ember {
public:
    mernok(std::string nev_p) : ember(nev_p) {}

    virtual double berSzamitas() override {
        return 900000 * 12;
    }
}

// Bölcsész
class bolcsesz : public ember {
public:
    bolcsesz(std::string nev_p) : ember(nev_p) {}

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

    // a < operátor alapján rendez
    sort(adatok.begin(), adatok.end());

    cout << "A rendezett adatok:" << endl;

    for (const auto& i : adatok)
        cout << i << "; ";

    cout << "A minimum: " << adatok[0] << "; a maximum: " << adatok.last() << endl;

    fajl.close();
}
```

## (láncolt) lista

A láncolt lista, C++-ban `list`, egy olyan tároló, ami nem lineárisan, hanem pointerekkel tárolja egymás után az értékeket. Emiatt egyszerű listába helyezni, törölni elemeket, de elérni azokát már nem olyan szimpla: a `[]` operátor és `.at()` függvény nincs értelmezve a listákon. Az elemeken viszont át lehet menni a speciális, iterátoros for ciklusokkal.

A következő példa megmutatja, hogy hogyan lehet a dinamikus törlést alkalmazni:

```C++
#include <list>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Ez visszaadja majd, hogy töröljük-e az elemet
bool bukottE(int jegy) {
    return jegy == 1;
}

int main() {
    srand((unsigned int)time(NULL));

    // Jegyek beírása
    list<int> jegyek;
    for (int i = 0; i < 200; i++) {
        jegyek.push_back(rand() % 5 + 1);
    }

    // Töröljük azokat, akik buktak
    // FONTOS: ha függvénnyel szűrünk, vagy törlünk, akkor nem írunk zárójelt a függvény neve után
    remove_if(jegyek, bukottE);

    cout << 200 - jegyek.size() << " ember bukott meg iden" << endl;

    cout << "A többiek a következö jegyeket kaptak:" << endl;
    for (const auto& i : jegyek) {
        cout << i << "; ";
    }
}
```

# Speciális szűrési, és törlési megoldások lambda függvények használatával

**A következő anyag nem minden gyakveznél lesz számon kérve**  
Az előző példában a `bukottE` függvényt zárójel nélkül adtuk át, miért van ez? Röviden mondva, nem a függvény visszaadott értéke, hanem maga a függvény (pointere) volt a paraméter. A C++ STL tárolóinak egy csomó függvénye van, amelynél így gyorsan megcsinálhatunk ilyen műveleteket, pl.: `find_if`, `remove_if`, `count_if`  
Az itt hívott függvényeket, melyeket csak egyszer hívunk, lambda függvényekre lehet lecserélni, amik gyorsabbak.

A lambdák a következő módon néznek ki:

```C++
[](tipus argumentum, ...) -> retTipus {
    // ...
}
```

ahol `[]` a főfüggvény átadott függvényeit tartalmazza: ha használni akarjuk a változóinkat, akkor $=$-t vagy $\&$-t rakunk oda
    `(tipus argumentum)` a függvény típusait jelenti
    `-> retTipus` a típus, amit a függvény visszaad, de ez általában nem kötelező

Az előző példában a törlés függvényt a következő módon lehet leírni lambdával:

```C++
remove_if(jegyek, [](int jegy) -> bool {
    return jegy == 1;
});
```

Ezekkel lehet speciális szabályok szerint szortírozni is, ami főleg az osztályok esetében fontos:

```C++
/* Példa:
Egy fájlban motorok neve (egyszavas), feszültség, áramigénye, valamint effektív teljesítménye van megadva. Rendezzük hatékonyság alapján sorrendbe ezeket.
Tabokkal vannak az adatok elválasztva.*/
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// struct = minden publikus
struct motor {
    double U, I, W_eff;
    string nev;

    motor(nev, double U, double I, double P_eff) : nev(nev), U(U), I(I), P_eff(P_eff) {}

    friend ostream& operator<<(ostream& os, const motor& ez) {
        os << nev << ": " << U "V, " << I << "A ," << P_eff << "W effektiv";
    }
};

const string fajlnev = "motorok.txt";
stringstream konv;

int main() {
    ifstream fajl(fajlnev);
    vector<motor> motorok;

    if (!fajl.good()) {
        cout << "Nem sikerült a(z) " << fajlnev << "nevü fajlt megnyitni!" << endl>;
        return -1;
    }

    string sor;
    while (!fajl.eof()) {
        getline(fajl, sor);
        if (sor.empty()) continue;
        
        string tempnev;
        double I, U, P;

        konv << sor << endl;
        konv >> tempnev >> I >> U >> P;
        motorok.push_back(motor(tempnev, I, U, P));
    }

    sort(motorok, [](const motor& egyik, const motor& masik) -> bool {
        return (egyik.P_eff / egyik.I / egyik.U) < (masik.P_eff / masik.I / masik.U);
    });

    cout << "A motorok sorrendje: " << endl;

    for (const auto& mot : motorok) {
        cout << mot << endl;
    }

    fajl.close();
}
```
