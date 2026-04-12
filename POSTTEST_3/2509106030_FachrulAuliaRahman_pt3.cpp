#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

#define MAX 5 // Kapasitas maksimum Stack dan Queue

using namespace std;

// --- STRUCT LAMA (POSTTEST 2) ---
struct JadwalKrt {
    string namaKA;
    int noKA;
    string stAwal;
    string stAkhir;
    int htm;
};

// --- STRUCT BARU (POSTTEST 3) ---
struct Tiket {
    string namaPenumpang;
    string namaKA;
    string rute;
};

// ==========================================
// FUNGSI-FUNGSI LAMA (JADWAL KERETA)
// ==========================================
void tukarData(JadwalKrt* x, JadwalKrt* y) {
    JadwalKrt sementara = *x;
    *x = *y;
    *y = sementara;
}

void tampilkanData(JadwalKrt* ptrKrt, int jmlData) {
    if (jmlData == 0) {
        cout << ">> Data jadwal belum ada!\n";
        return;
    }
    cout << "\n=== DAFTAR JADWAL KERETA ===\n";
    for (int i = 0; i < jmlData; i++) {
        cout << i + 1 << ". Kereta     : " << (ptrKrt + i)->namaKA << endl;
        cout << "   No. Kereta : " << (ptrKrt + i)->noKA << endl;
        cout << "   Rute       : " << (ptrKrt + i)->stAwal << " - " << (ptrKrt + i)->stAkhir << endl;
        cout << "   Harga      : Rp" << (ptrKrt + i)->htm << "\n\n";
    }
}

void inputKeretaBaru(JadwalKrt* ptrKrt, int* jml) {
    cout << "\n--- Tambah Jadwal Baru ---\n";
    cin.ignore();
    cout << "Nama Kereta   : "; getline(cin, (ptrKrt + *jml)->namaKA);
    cout << "Nomor Kereta  : "; cin >> (ptrKrt + *jml)->noKA;
    cin.ignore();
    cout << "Stasiun Asal  : "; getline(cin, (ptrKrt + *jml)->stAwal);
    cout << "Stasiun Tujuan: "; getline(cin, (ptrKrt + *jml)->stAkhir);
    cout << "Harga Tiket   : "; cin >> (ptrKrt + *jml)->htm;
    
    (*jml)++;
    cout << ">> Sukses nambahin data!\n";
}

void urutHargaSelection(JadwalKrt* ptrKrt, int jml) {
    for (int i = 0; i < jml - 1; i++) {
        int idxTermurah = i;
        for (int j = i + 1; j < jml; j++) {
            if ((ptrKrt + j)->htm < (ptrKrt + idxTermurah)->htm) {
                idxTermurah = j;
            }
        }
        tukarData((ptrKrt + i), (ptrKrt + idxTermurah));
    }
    cout << ">> Sorting harga (Selection Sort) selesai!\n";
}

void prosesGabung(JadwalKrt* ptrKrt, int kiri, int tengah, int kanan) {
    int batasKiri = tengah - kiri + 1;
    int batasKanan = kanan - tengah;

    JadwalKrt* arrayKiri = new JadwalKrt[batasKiri];
    JadwalKrt* arrayKanan = new JadwalKrt[batasKanan];

    for (int i = 0; i < batasKiri; i++) arrayKiri[i] = *(ptrKrt + kiri + i);
    for (int j = 0; j < batasKanan; j++) arrayKanan[j] = *(ptrKrt + tengah + 1 + j);

    int i = 0, j = 0, k = kiri;
    while (i < batasKiri && j < batasKanan) {
        if (arrayKiri[i].namaKA <= arrayKanan[j].namaKA) {
            *(ptrKrt + k) = arrayKiri[i];
            i++;
        } else {
            *(ptrKrt + k) = arrayKanan[j];
            j++;
        }
        k++;
    }

    while (i < batasKiri) { *(ptrKrt + k) = arrayKiri[i]; i++; k++; }
    while (j < batasKanan) { *(ptrKrt + k) = arrayKanan[j]; j++; k++; }

    delete[] arrayKiri;
    delete[] arrayKanan;
}

void urutNamaMerge(JadwalKrt* ptrKrt, int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        urutNamaMerge(ptrKrt, kiri, tengah);
        urutNamaMerge(ptrKrt, tengah + 1, kanan);
        prosesGabung(ptrKrt, kiri, tengah, kanan);
    }
}

void cariRuteLinear(JadwalKrt* ptrKrt, int jml, string asal, string tujuan) {
    bool ketemu = false;
    cout << "\n--- Log Pencarian Linear ---\n";
    for (int i = 0; i < jml; i++) {
        cout << "Mengecek indeks ke-" << i << " (Rute: " << (ptrKrt + i)->stAwal << " - " << (ptrKrt + i)->stAkhir << ")...\n";
        
        if ((ptrKrt + i)->stAwal == asal && (ptrKrt + i)->stAkhir == tujuan) {
            cout << "\n[!] MATCH KETEMU: Kereta " << (ptrKrt + i)->namaKA << " | No: " << (ptrKrt + i)->noKA 
                 << " | Harga: Rp" << (ptrKrt + i)->htm << "\n";
            ketemu = true;
        }
    }
    if (!ketemu) {
        cout << "\n[!] Waduh, rute " << asal << " ke " << tujuan << " nggak ketemu.\n";
    }
}

void sortNomorBubble(JadwalKrt* ptrKrt, int jml) {
    for (int i = 0; i < jml - 1; i++) {
        for (int j = 0; j < jml - i - 1; j++) {
            if ((ptrKrt + j)->noKA > (ptrKrt + j + 1)->noKA) {
                tukarData((ptrKrt + j), (ptrKrt + j + 1));
            }
        }
    }
}

void cariNoJump(JadwalKrt* ptrKrt, int jml, int targetNo) {
    if (jml == 0) {
        cout << ">> Isi data dulu bro!\n"; return;
    }
    
    sortNomorBubble(ptrKrt, jml);

    int lompatan = sqrt(jml);
    int sblm = 0;

    while ((ptrKrt + min(lompatan, jml) - 1)->noKA < targetNo) {
        sblm = lompatan;
        lompatan += sqrt(jml);
        if (sblm >= jml) {
            cout << ">> Nomor kereta " << targetNo << " nggak ada di list.\n";
            return;
        }
    }

    while ((ptrKrt + sblm)->noKA < targetNo) {
        sblm++;
        if (sblm == min(lompatan, jml)) {
            cout << ">> Nomor kereta " << targetNo << " nggak ada di list.\n";
            return;
        }
    }

    if ((ptrKrt + sblm)->noKA == targetNo) {
        cout << "\n[!] MATCH KETEMU: Kereta " << (ptrKrt + sblm)->namaKA << " dengan rute " 
             << (ptrKrt + sblm)->stAwal << " - " << (ptrKrt + sblm)->stAkhir << "\n";
    } else {
        cout << ">> Nomor kereta " << targetNo << " nggak ada di list.\n";
    }
}


// ==========================================
// FUNGSI-FUNGSI BARU (POSTTEST 3)
// ==========================================

// 1. Fungsi Push Stack (Tambah ke Riwayat)
void pushRiwayat(Tiket* ptrStack, int* top, Tiket dataTransaksi) {
    if (*top == MAX - 1) {
        cout << "[!] OVERFLOW: Stack Riwayat Transaksi Penuh!\n";
        return;
    }
    (*top)++;
    *(ptrStack + *top) = dataTransaksi;
}

// 2. Fungsi Enqueue (Masuk Antrian)
void enqueueAntrian(Tiket* ptrQueue, int* front, int* rear, Tiket dataBaru) {
    if (*rear == MAX - 1) {
        cout << "[!] OVERFLOW: Antrian Tiket Penuh (Maksimal " << MAX << " antrian)!\n";
        return;
    }
    if (*front == -1) {
        *front = 0;
    }
    (*rear)++;
    *(ptrQueue + *rear) = dataBaru;
    cout << ">> Sukses! Penumpang " << dataBaru.namaPenumpang << " berhasil masuk antrian.\n";
}

// 3. Fungsi Dequeue (Proses Tiket & Pindah ke Stack Riwayat)
void dequeueProses(Tiket* ptrQueue, int* front, int* rear, Tiket* ptrStack, int* top) {
    if (*front == -1 || *front > *rear) {
        cout << "[!] UNDERFLOW: Antrian kosong, tidak ada tiket yang bisa diproses.\n";
        return;
    }
    
    // Ambil data paling depan (indeks ke-0)
    Tiket tiketDiproses = *(ptrQueue + *front);
    cout << ">> Sedang memproses pesanan...\n";
    cout << "   Nama : " << tiketDiproses.namaPenumpang << "\n";
    cout << "   Rute : " << tiketDiproses.namaKA << " (" << tiketDiproses.rute << ")\n";
    
    // Masukkan ke Stack Riwayat
    pushRiwayat(ptrStack, top, tiketDiproses);
    cout << ">> Tiket berhasil diproses dan dicatat ke riwayat transaksi!\n";

    // PERGESERAN ELEMEN (WAJIB MENGGUNAKAN DEREFERENSI POINTER)
    for (int i = 0; i < *rear; i++) {
        *(ptrQueue + i) = *(ptrQueue + i + 1);
    }
    (*rear)--;
    
    if (*rear == -1) {
        *front = -1; // Reset queue jika sudah habis diproses
    }
}

// 4. Fungsi Pop Stack (Hapus Riwayat Terakhir)
void popRiwayat(Tiket* ptrStack, int* top) {
    if (*top == -1) {
        cout << "[!] UNDERFLOW: Riwayat transaksi kosong, tidak ada yang bisa dibatalkan!\n";
        return;
    }
    cout << ">> Transaksi terakhir atas nama '" << (ptrStack + *top)->namaPenumpang 
         << "' berhasil dibatalkan/dihapus dari riwayat.\n";
    (*top)--;
}

// 5. Fungsi Peek (Lihat Terdepan & Terakhir)
void peekData(Tiket* ptrQueue, int front, int rear, Tiket* ptrStack, int top) {
    cout << "\n--- PEEK (INTIP DATA) ---\n";
    
    // Peek Queue
    cout << "Penumpang Terdepan (Antrian) : ";
    if (front != -1 && front <= rear) {
        cout << (ptrQueue + front)->namaPenumpang << " (Rute: " << (ptrQueue + front)->rute << ")\n";
    } else {
        cout << "[KOSONG]\n";
    }

    // Peek Stack
    cout << "Transaksi Terakhir (Riwayat) : ";
    if (top != -1) {
        cout << (ptrStack + top)->namaPenumpang << " (Rute: " << (ptrStack + top)->rute << ")\n";
    } else {
        cout << "[KOSONG]\n";
    }
}

// 6. Tampil Antrian (Iterasi pakai Pointer Aritmatika)
void tampilkanAntrian(Tiket* ptrQueue, int front, int rear) {
    if (front == -1 || front > rear) {
        cout << ">> Antrian tiket saat ini kosong!\n";
        return;
    }
    cout << "\n=== DAFTAR ANTRIAN PEMBELIAN TIKET ===\n";
    for (int i = front; i <= rear; i++) {
        cout << (i - front + 1) << ". Nama : " << (ptrQueue + i)->namaPenumpang << "\n"
             << "   Rute : " << (ptrQueue + i)->rute << "\n\n";
    }
}

// 7. Tampil Riwayat (Iterasi pakai Pointer Aritmatika)
void tampilkanRiwayat(Tiket* ptrStack, int top) {
    if (top == -1) {
        cout << ">> Belum ada riwayat transaksi!\n";
        return;
    }
    cout << "\n=== RIWAYAT TRANSAKSI (TERBARU - TERLAMA) ===\n";
    // Iterasi Stack dari atas ke bawah
    for (int i = top; i >= 0; i--) {
        cout << (top - i + 1) << ". Nama : " << (ptrStack + i)->namaPenumpang << "\n"
             << "   Rute : " << (ptrStack + i)->rute << "\n\n";
    }
}

int main() {
    JadwalKrt listKereta[100]; 
    int totalData = 0;
    
    // Variabel Queue (Antrian)
    Tiket antrian[MAX];
    int front = -1, rear = -1;

    // Variabel Stack (Riwayat)
    Tiket riwayat[MAX];
    int top = -1;

    int menu;

    do {
        cout << "\n==========================================\n";
        cout << "   APP MANAJEMEN KERETA API (POSTTEST 3)\n";
        cout << "==========================================\n";
        cout << "1. Input Jadwal Baru\n";
        cout << "2. Cek Semua Jadwal\n";
        cout << "3. Sortir Harga Termurah (Selection Sort)\n";
        cout << "4. Sortir Nama A-Z (Merge Sort)\n";
        cout << "5. Cari Rute Spesifik (Linear Search)\n";
        cout << "6. Cari by Nomor Kereta (Jump Search)\n";
        cout << "------------------------------------------\n";
        cout << "7. Masuk Antrian Pembelian Tiket (Enqueue)\n";
        cout << "8. Proses Tiket Terdepan (Dequeue & Push)\n";
        cout << "9. Batalkan Transaksi Terakhir (Pop)\n";
        cout << "10. Cek Data Terdepan & Terakhir (Peek)\n";
        cout << "11. Tampilkan Semua Antrian (Queue)\n";
        cout << "12. Tampilkan Riwayat Transaksi (Stack)\n";
        cout << "0. Exit\n";
        cout << "Pilih menu > ";
        cin >> menu;

        switch (menu) {
            case 1:
                inputKeretaBaru(listKereta, &totalData); 
                break;
            case 2:
                tampilkanData(listKereta, totalData);
                break;
            case 3:
                urutHargaSelection(listKereta, totalData);
                tampilkanData(listKereta, totalData);
                break;
            case 4:
                if(totalData > 0) {
                    urutNamaMerge(listKereta, 0, totalData - 1);
                    cout << ">> Sorting nama (Merge Sort) selesai!\n";
                    tampilkanData(listKereta, totalData);
                } else {
                    cout << ">> Isi data dulu bro!\n";
                }
                break;
            case 5: {
                string inputAsal, inputTujuan;
                cin.ignore();
                cout << "Cari Stasiun Asal   : "; getline(cin, inputAsal);
                cout << "Cari Stasiun Tujuan : "; getline(cin, inputTujuan);
                cariRuteLinear(listKereta, totalData, inputAsal, inputTujuan);
                break;
            }
            case 6: {
                int inputNomor;
                cout << "Masukkan Nomor Kereta: ";
                cin >> inputNomor;
                cariNoJump(listKereta, totalData, inputNomor);
                break;
            }
            case 7: {
                if (totalData == 0) {
                    cout << ">> Data jadwal kereta masih kosong! Tambah jadwal dulu di Menu 1.\n";
                    break;
                }
                Tiket tiketBaru;
                cin.ignore();
                cout << "\n--- Form Pemesanan Tiket ---\n";
                cout << "Nama Penumpang: "; getline(cin, tiketBaru.namaPenumpang);
                tampilkanData(listKereta, totalData);
                cout << "Pilih jadwal kereta (masukkan nomor urut 1-" << totalData << "): ";
                int pilihan; cin >> pilihan;
                
                if (pilihan > 0 && pilihan <= totalData) {
                    tiketBaru.namaKA = (listKereta + pilihan - 1)->namaKA;
                    tiketBaru.rute = (listKereta + pilihan - 1)->stAwal + " - " + (listKereta + pilihan - 1)->stAkhir;
                    enqueueAntrian(antrian, &front, &rear, tiketBaru);
                } else {
                    cout << ">> Pilihan jadwal tidak valid!\n";
                }
                break;
            }
            case 8:
                dequeueProses(antrian, &front, &rear, riwayat, &top);
                break;
            case 9:
                popRiwayat(riwayat, &top);
                break;
            case 10:
                peekData(antrian, front, rear, riwayat, top);
                break;
            case 11:
                tampilkanAntrian(antrian, front, rear);
                break;
            case 12:
                tampilkanRiwayat(riwayat, top);
                break;
            case 0:
                cout << ">> Program ditutup.\n";
                break;
            default:
                cout << ">> Pilihan salah, coba lagi!\n";
        }
    } while (menu != 0);

    return 0;
}