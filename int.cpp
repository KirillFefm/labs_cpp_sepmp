#include <iostream>
#include <bitset>
#include <climits>

using std::cout;
using std::bitset;
using std::endl;
using std::cin;

template <typename T>
void printBits(T value) {
    const int bits = sizeof(T) * CHAR_BIT;
    bitset<bits> b(value);
    cout << b << endl;
}

int main() {
    cout << "Size int: " << sizeof(int) << " byte\n\n";

    int a = 5;
    int b = -5;

    cout << "5:\n";
    printBits(a);

    cout << "-5:\n";
    printBits(b);

    union {
        int i;
        unsigned int u;
    } v;

    v.i = a;
    cout << "5: " << v.u << "  ";
    printBits(v.u);

    v.i = b;
    cout << "-5: " << v.u << "  ";
    printBits(v.u);

    int maxInt = INT_MAX;
    cout << "INT_MAX = " << maxInt << endl;
    cout << "INT_MAX + 1 = " << maxInt + 1 << endl;

    unsigned int maxUInt = UINT_MAX;
    cout << "UINT_MAX = " << maxUInt << endl;
    cout << "UINT_MAX + 1 = " << maxUInt + 1 << endl;
    cout << "UINT_MAX - 1 = " << maxUInt - 1 << endl;

    return 0;
}
