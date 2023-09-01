#include <iostream>

template <typename T>
int hanyVektorVan();

template <typename T>
class vektor {
    static int vektorokSzama;
public:
    T x, y, z;

    vektor(T x = 0.0, T y = 0.0, T z = 0.0) : x(x), y(y), z(z) {
        vektorokSzama++;
    }

    ~vektor() { vektorokSzama--; }

    double hossz() {
        return sqrt(x * x + y * y + z * z);
    }

    vektor<T> operator+(const vektor<T> masik) {
        return vektor(this->x + masik.x, this->y + masik.y, this->z + masik.z);
    }
    vektor<T> operator-(const vektor<T> masik) {
        return vektor(this->x - masik.x, this->y - masik.y, this->z - masik.z);
    }
    
    vektor<T> operator*(double skalar) {
        return vektor(this->x * skalar, this->y * skalar, this->z * skalar);
    }

    vektor<T> operator*(const vektor<T> masik) {
        return this->x * masik.x + this->y * masik.y + this->z * masik.z;
    }

    vektor<T>& operator=(const vektor<T> masik) {
        *this = masik;
        return *this;
    }
    vektor<T>& operator+=(const vektor<T> masik) {
        *this = *this + masik;
        return *this;
    }
    vektor<T>& operator-=(const vektor<T> masik) {
        *this = *this - masik;
        return *this;
    }
    vektor<T>& operator*=(const T skalar) {
        *this = *this * skalar;
        return *this;
    }

    bool operator<(vektor<T> masik) {
        return this->hossz() < masik.hossz();
    }
    bool operator>(vektor<T> masik) {
        return this->hossz() > masik.hossz();
    }
    bool operator==(vektor<T> masik) {
        return this->x == masik.x && this->y == masik.y && this->z == masik.z;
    }

    friend int hanyVektorVan();
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const vektor<U>& vec);
};

template <typename T>
int hanyVektorVan() {
    return vektor<T>::vektorokSzama;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vektor<T>& vec) {
    os << "{ " << vec.x << "; " << vec.y << "; " << vec.z << " }";
    return os;
}

template <typename T>
int vektor<T>::vektorokSzama = 0;

int main() {}