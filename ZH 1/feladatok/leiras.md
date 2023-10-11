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

Csinálj egy mátrix osztályt! Ez a mátrix osztály legyen típusfüggetlen, és létrehozáskor adjuk meg neki, hogy mekkora legyen ($M \times N$).  
Úgy lehessen módosítani az egyes elemeket, mint egy kétdimenziós tömbnél (`matrix[1][2]`, ahol az első index a sort, a második az oszlopot jelöli)  
Azt biztosítsd, hogy rendesen szabadítja fel a memóriát!

Végül határozd meg, hogy mennyi:

$$\begin{bmatrix} 1 & 2 & 3 \\\
4 & 5 & 6
\end{bmatrix} +
\begin{bmatrix} 9 & 8 & 7 \\\
6 & 5 & 4
\end{bmatrix}$$

(A kihívást akárhogyan megoldhatod, nem kell `<<`-t túlterhelni, de a formának és értékeknek jónak kell lennie!)

Tippek:  

- A [] operátort is túl lehet tölteni, mutathat egy valódi kétdimenziós tömbhöz
- Két mátrix összeadása két egymásban lévő `for` ciklussal meg lehet oldani, a kiírás is hasonló
