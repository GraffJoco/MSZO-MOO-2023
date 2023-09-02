#include <string.h>
#include <iostream>

template <typename T>
class okosPtr {
    T* adat;

public:
    okosPtr(T* adat): adat(adat) {}

    ~okosPtr() {
        delete adat;
    }

    T* get() { return adat; }
};

int main() {
    okosPtr<char> tesztString(new char[64]);
    char* HWorld = (char*)"Hello World!";
    strncpy_s(tesztString.get(), 64, HWorld, strlen(HWorld));

    std::cout << tesztString.get() << std::endl;
}