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
