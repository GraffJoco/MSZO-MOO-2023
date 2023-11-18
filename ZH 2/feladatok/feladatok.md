# A 2. ZH feladatai

## 1. feladat

Csináljunk egy 3D-s vektor struktúrát, és oldjunk meg vele egy dinamika feladatot! A műveleteket operátor túlterheléssel oldd meg, kiírással együtt.
A vektor legyen sablon, de a számításoknál `double`-t használj!

![](feladat1.png)

A következők a kezdeti paraméterek:

$$R = 0,5 m \\
m = 5 kg \\
\underline{v_B} = \underline{0} \\
\underline{F} = \begin{bmatrix} 10 \\ 50 \\ 0 \end{bmatrix} N \\
\varepsilon = 0\\
\underline{\omega} = -3 \underline{k} {rad\over{s}}$$

A következőket kell meghatározni:

$$\underline{v_A} = ? \\
\underline{a_A} = ? \\
\underline{r_{AG}} = ?$$

Ha nem emlékszel, a következők a dinamika alapképletei:

$$\underline{F} = m\underline{a} \\
\underline{v_B} = \underline{v_A} + \underline{\omega} \times \underline{r_{AB}} \\
\underline{r_{AG}} = {1\over{\varepsilon^2+\omega^4}}\cdot(\omega^2\cdot\underline{a_A} + \underline{\varepsilon}\times\underline{a_A})$$

## 2. feladat

Csináljuk egy Test objektumot, ami az alapja lesz mindennek, ami rá épül. Minden testnek két függvénye van: terulet() és kerulet(), amik kiszámolják az egyes tulajdonságokat, és visszaadják az értéket (minden numerikus érték legyen double!).

Erre építsük a következő osztályokat:

1. Kör:
    - R (sugár tulajdonság)
2. Téglalap:
    - a oldal
    - b oldal
3. Háromszög:
    - a oldal
    - b oldal
    - gamma szög (a és b oldal közötti szög)
    - privát elemként tárold a c oldalt is, amit a konstruktor számol ki!

Polimorfizmussal garantáld, hogy mindig az osztály jó függvényét hívjuk!

## 3. feladat

Csináljuk meg az előző mintafeladatokban lévő GPU osztályt! (név: egyszavas string, GHz: double, ár: double)

Most a fájl elején nincs, hogy hány adat lesz, tehát STL tárolóba rakd az egyes példányokat!
Ezeket rendezd azalapján, hogy melyik éri meg legjobban, és írd ki a konzolba!
