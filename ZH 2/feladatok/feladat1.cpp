#include <iostream>
#include <math.h>

using namespace std;

template <typename T>
struct vektor
{
    T x, y, z;

    vektor(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}

    vektor<T> operator+(const vektor<T> masik) {
        return vektor(this->x + masik.x, this->y + masik.y, this->z + masik.z);
    }
    vektor<T> operator-(const vektor<T> masik) {
        return vektor(this->x - masik.x, this->y - masik.y, this->z - masik.z);
    }
    vektor<T> operator*(double skalar) {
        return vektor(this->x * skalar, this->y * skalar, this->z * skalar);
    }
    vektor<T> operator/(double skalar) {
        return vektor(this->x / skalar, this->y / skalar, this->z / skalar);
    }
    vektor<T> operator^(const vektor<T> masik) {
        return vektor<T>(
            this->y * masik.z - this->z * masik.y,
            this->z * masik.x - this->x * masik.z,
            this->x * masik.y - this->y * masik.x);
    }

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }

    friend ostream &operator<<(ostream &os, const vektor<T> ez) {
        os << "{" << ez.x << "; " << ez.y << "; " << ez.z << "}";
        return os;
    }
};

int main() {
    double R = 0.5;
    double m = 5;
    auto F = vektor<double>(10, 50, 0);
    auto omega = vektor<double>(0, 0, -3);

    // 1. alfeladat: v_A = ?
    // Először meg kell határozni r_BA-t, ami -Rj
    auto r_BA = vektor<double>(0, -1, 0) * R;
    auto v_A = omega ^ r_BA;
    cout << "v_A = " << v_A << " m/s" << endl;

    // 2. alfeladat
    auto a_A = F / m;
    cout << "a_A = " << a_A << " N" << endl;

    // 3. alfeladat
    // r_AG = 1/(e^2 + w^4)*(w^2 * a_A + e ^ a_A)
    // r_AG = 1/(w^4) * (w^2 * a_A)
    // r_AG = w^-2 * a_A
    auto r_AG = a_A * pow(omega.hossz(), -2);
    cout << "r_AP = " << r_AG << " m" << endl;
}