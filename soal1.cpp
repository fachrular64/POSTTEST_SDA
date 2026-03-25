#include <iostream>
using namespace std;

/*
Analisis Kompleksitas FindMin

Pseudocode:
1  min ← A[0]                  > c1
2  for i ← 1 to n-1            > c2 (n-1 kali)
3     if A[i] < min            > c3 (n-1 kali)
4         min ← A[i]           > c4 (tergantung kondisi)
5  return min                  > c5

Tmin(n) (Best Case)
- Kondisi if tidak pernah benar
- Baris 4 tidak pernah dijalankan
Tmin(n) = c1 + (n-1)c2 + (n-1)c3 + c5
Tmin(n) = an + b
Big-O = O(n)

Tmax(n) (Worst Case)
- Kondisi if selalu benar
- Baris 4 dijalankan (n-1) kali
Tmax(n) = c1 + (n-1)c2 + (n-1)c3 + (n-1)c4 + c5
Tmax(n) = an + b
Big-O = O(n)

Kesimpulan:
Best Case  = O(n)
Worst Case = O(n)
*/

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;

    int min = A[0];
    int indeks = 0;

    for(int i = 1; i < n; i++) {
        if(A[i] < min) {
            min = A[i];
            indeks = i;
        }
    }

    cout << "Nilai minimum = " << min << endl;
    cout << "Indeks minimum = " << indeks << endl;

    return 0;
}
