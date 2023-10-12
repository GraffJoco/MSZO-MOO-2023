#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const double g_y = -9.81;
const string fajlnev = "ZH 1\\feladatok\\eredmenyek.csv";

class test {
    double v_x, v_y, s_x, s_y, t;
public:
    test(double v_x0, double v_y0, double s_x0, double s_y0):
        v_x(v_x0), v_y(v_y0), s_x(s_x0), s_y(s_y0), t(0) {}

    void idolepes(double dt) {
        v_y += g_y * dt;
        s_x += v_x * dt;
        s_y += v_y * dt;
    }

    double getVX() { return v_x; }
    double getVY() { return v_y; }
    double getSX() { return s_x; }
    double getSY() { return s_y; }
    double getT() { return t; }
};

int main() {
    test szimulacio(10, 0, 0, 10);
    ofstream fajl(fajlnev);
    if (!fajl.is_open()) {
        cout << "Nem lehet megnyitni a(z) " << fajlnev << " nevu fajlt!" << endl;
        exit(-1);
    }

    fajl << "t;s_x;s_y;v_x;v_y" << endl;
    for (int i = 0; i < 100; i++) {
        szimulacio.idolepes(0.01);
        fajl << szimulacio.getT() << ";" << szimulacio.getSX() << ";" << szimulacio.getSY() << ";"
            << szimulacio.getVX() << ";" << szimulacio.getVY() << endl;
    }

    fajl.close();
}
