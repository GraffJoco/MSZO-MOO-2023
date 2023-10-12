all:
	g++ -o "ZH 1/feladatok/teszt.exe" "ZH 1/feladatok/feladat4.cpp" -Wall
	."\ZH 1\feladatok\teszt.exe"

asm:
	g++ -S -masm=intel "ZH 1/feladatok/feladat4.cpp"