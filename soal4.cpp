#include <iostream>
using namespace std;

void tukar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x, y;

    cout << "Masukkan nilai x: ";
    cin >> x;
    cout << "Masukkan nilai y: ";
    cin >> y;

    cout << "\nSebelum ditukar:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    tukar(&x, &y);

    cout << "\nSesudah ditukar:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    return 0;
}
