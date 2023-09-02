#include <iostream> // std::cout
#define _USE_MATH_DEFINES // konstansok (pl.: PI)
#include <math.h> // sin, cos, stb.

class Test {
public:
    virtual double terulet() = 0;
    virtual double kerulet() = 0;
};

class Kor : public Test {
public:
    double R;

    Kor(double R) : R(R) {}

    double kerulet() override {
        return 2 * R * M_PI;
    }

    double terulet() override {
        return R * R * M_PI;
    }
};

class Teglalap : public Test {
public:
    double a, b;

    Teglalap(double a, double b) : a(a), b(b) {}

    double kerulet() override {
        return 2 * a + 2 * b;
    }

    double terulet() override {
        return a * b;
    }
};

class Haromszog : public Test {
private:
    double c;
public:
    double a, b, gamma;

    Haromszog(double a, double b, double gamma) :
        a(a), b(b), gamma(gamma) {
            // Koszinusz tétel
            c = sqrt(a * a + b * b - 2 * a * b * cos(gamma));
        }

    double kerulet() override {
        return a + b + c;
    }

    double terulet() override {
        return a * b * sin(gamma) / 2;
    }
};

// Azért van csak itt, mert különben a GCC nem fordítja le a programot
int main() {}