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