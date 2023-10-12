# Segítőfeladatok az első ZH-hoz

## 1. feladat

A C++ egyik új könyvtára a `<memory>`, ami implementálja az ú.n. okospointereket. Ezek felszabadítják a bennük tárolt pointert, ha már nincs szükség rájuk (tehát automatikusan hívja a `delete`-et). Csinálj egy osztályt, ami a legegyszerűbbet (`std::unique_ptr<T>`) utánozza!

A konstruktorban adj meg egy pointert, amit egy privát elemben eltárolunk. A destruktor `delete`-tel felszabadítja az elemet. Ha az elemhez hozzá akarunk férni, akkor a `okospointer.get()` függvényt hívjuk. Legyen típusfüggetlen az osztály!

## 2. feladat

Hozz létre egy "GPU" nevű osztályt, ami a következőket tartalmazza: a videókártya neve (egyszavas string), az ára valamint, hogy hány GHz-es az órajele. Egy fájlból olvass ki $n$ darab GPU-t. Egy beépített függvénnyel határozd meg az árarányos értékét (Ft/GHz). A fájlban az összes érték tabokkal van elválasztva, az első sor tartalmazza, hogy hány GPU van. Írd ki a konzolba, hogy melyik a legjobb és legrosszabb kártya Ft/GHz alapján.

## 3. feladat

Készítjünk egy pénzügyi adatfeldolgozó osztályt! A konstruktor kérjen egy stringet, ami megadja az osztálynak, hogy melyik (CSV formátumú) fájlt olvassa be!  
A fájl soraból olvasd ki `bevetel;kiadas` formátumban az akkori bevételeket, kiadásokat (ezek double-ök)!  
Az osztálynak csinálj 3 függvényt, amik:

- Visszaadják, hogy hány elem van
- Visszaadják az átlagos profitot ($\sum bevetel - \sum kiadas\over{elemszam}$)

## 4. feladat

Csináljunk egy kis (2D-s) szimulációt! Legyen egy osztályunk, ami a szimulált testet tartalmazza. A testnek van pozíciója és sebessége, amiket a konstruktorban is kérünk. Ezen kívül az időt is tárolja (ez mindig 0-ról indul). A $\Delta t$ -s időlépéseket egy tagfüggvénnyel számold ki, ahol $\Delta t$ a paraméter, az új lépés adatai pedig a régieket cseréljék le!

A következők a fizikai függvények (ha nem jutna eszedbe):

$$\underline{g} = \begin{bmatrix} 0 \\ -9,81\end{bmatrix} {m\over{s^2}}$$

$$\underline{v_t} = \underline{v_{t-1}} + \underline{g}\Delta t$$

$$\underline{s_t} = \underline{s_{t-1}} + \underline{v_t}\Delta t $$

Szimulálj le 100 lépést, a következő paraméterekkel, és írd ki egy *eredmenyek.csv* nevű fájlba (úgy, hogy függvényekkel le tudod kérni a mostani fiziai paramétereket):

$$\underline{s_0} = \begin{bmatrix} 0 \\ 10 \end{bmatrix} m; \underline{v_0} = \begin{bmatrix} 10 \\ 0 \end{bmatrix}{m\over{s}}; \Delta t = 0,01 s$$
