/* NIM: 2509106030 
Nama: Fachrul Aulia Rahman 
*/

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct JadwalKrt {
    string namaKA;
    int noKA;
    string stAwal;
    string stAkhir;
    int htm;
    JadwalKrt* next;
};

struct Tiket {
    string namaPenumpang;
    string namaKA;
    string rute;
    Tiket* next; 
};

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
    (ptrKrt + *jml)->next = NULL; 
    
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

/*
 * Fungsi untuk menambahkan data transaksi baru ke tumpukan (Stack) riwayat.
 * Diimplementasikan menggunakan Single Linked List dengan metode penyisipan di awal (Push).
 */
void pushRiwayat(Tiket** top, string namaPenumpang, string namaKA, string rute) {
    Tiket* nodeBaru = new Tiket;
    nodeBaru->namaPenumpang = namaPenumpang;
    nodeBaru->namaKA = namaKA;
    nodeBaru->rute = rute;
    nodeBaru->next = *top;
    *top = nodeBaru;
}

/*
 * Fungsi untuk memasukkan data penumpang baru ke dalam antrian (Queue).
 * Diimplementasikan menggunakan Single Linked List dengan metode penyisipan di akhir (Enqueue).
 */
void enqueueAntrian(Tiket** front, Tiket** rear, string namaPenumpang, string namaKA, string rute) {
    Tiket* nodeBaru = new Tiket;
    nodeBaru->namaPenumpang = namaPenumpang;
    nodeBaru->namaKA = namaKA;
    nodeBaru->rute = rute;
    nodeBaru->next = NULL;

    if (*rear == NULL) {
        *front = *rear = nodeBaru;
    } else {
        (*rear)->next = nodeBaru;
        *rear = nodeBaru;
    }
    cout << ">> Sukses! Penumpang " << namaPenumpang << " berhasil masuk antrian.\n";
}

/*
 * Fungsi untuk memproses data terdepan dalam antrian (Dequeue) lalu memindahkannya ke riwayat transaksi (Push).
 * Menangani kondisi underflow (kekosongan data) dan menghapus node memori yang telah selesai diproses.
 */
void dequeueProses(Tiket** front, Tiket** rear, Tiket** top) {
    if (*front == NULL) {
        cout << "[!] UNDERFLOW: Antrian kosong, tidak ada tiket yang dapat diproses.\n";
        return;
    }
    
    Tiket* nodeHapus = *front;
    
    cout << ">> Sedang memproses pesanan...\n";
    cout << "   Nama : " << nodeHapus->namaPenumpang << "\n";
    cout << "   Rute : " << nodeHapus->namaKA << " (" << nodeHapus->rute << ")\n";
    
    pushRiwayat(top, nodeHapus->namaPenumpang, nodeHapus->namaKA, nodeHapus->rute);
    cout << ">> Tiket berhasil diproses dan dicatat ke riwayat transaksi!\n";

    *front = (*front)->next;
    
    if (*front == NULL) {
        *rear = NULL;
    }
    
    delete nodeHapus;
}

/*
 * Fungsi untuk menghapus riwayat transaksi paling terakhir dari tumpukan (Pop).
 * Menangani kondisi underflow (kekosongan data) dan melepaskan alokasi memori terkait.
 */
void popRiwayat(Tiket** top) {
    if (*top == NULL) {
        cout << "[!] UNDERFLOW: Riwayat transaksi kosong, tidak ada yang dapat dibatalkan.\n";
        return;
    }
    
    Tiket* nodeHapus = *top;
    cout << ">> Transaksi terakhir atas nama '" << nodeHapus->namaPenumpang 
         << "' berhasil dibatalkan dan dihapus dari riwayat.\n";
    
    *top = (*top)->next;
    delete nodeHapus;
}

/*
 * Fungsi untuk melihat informasi penumpang terdepan pada antrian dan transaksi terakhir pada riwayat.
 * Beroperasi tanpa memodifikasi atau menghapus data di dalam struktur list (Peek).
 */
void peekData(Tiket* front, Tiket* top) {
    cout << "\n--- PEEK (INTIP DATA) ---\n";
    
    cout << "Penumpang Terdepan (Antrian) : ";
    if (front != NULL) {
        cout << front->namaPenumpang << " (Rute: " << front->rute << ")\n";
    } else {
        cout << "[KOSONG]\n";
    }

    cout << "Transaksi Terakhir (Riwayat) : ";
    if (top != NULL) {
        cout << top->namaPenumpang << " (Rute: " << top->rute << ")\n";
    } else {
        cout << "[KOSONG]\n";
    }
}

/*
 * Fungsi untuk menampilkan seluruh data penumpang di dalam antrian (Queue).
 * Melakukan iterasi penelusuran (traversal) node secara berurutan dari depan hingga belakang.
 */
void tampilkanAntrian(Tiket* front) {
    if (front == NULL) {
        cout << ">> Antrian tiket saat ini dalam keadaan kosong.\n";
        return;
    }
    
    cout << "\n=== DAFTAR ANTRIAN PEMBELIAN TIKET ===\n";
    Tiket* bantu = front;
    int i = 1;
    
    while (bantu != NULL) {
        cout << i++ << ". Nama : " << bantu->namaPenumpang << "\n"
             << "   Rute : " << bantu->rute << "\n\n";
        bantu = bantu->next;
    }
}

/*
 * Fungsi untuk menampilkan seluruh riwayat transaksi tiket (Stack).
 * Melakukan iterasi penelusuran node dari posisi paling atas (terbaru) menuju dasar tumpukan.
 */
void tampilkanRiwayat(Tiket* top) {
    if (top == NULL) {
        cout << ">> Belum terdapat riwayat transaksi.\n";
        return;
    }
    
    cout << "\n=== RIWAYAT TRANSAKSI (TERBARU - TERLAMA) ===\n";
    Tiket* bantu = top;
    int i = 1;
    
    while (bantu != NULL) {
        cout << i++ << ". Nama : " << bantu->namaPenumpang << "\n"
             << "   Rute : " << bantu->rute << "\n\n";
        bantu = bantu->next;
    }
}

int main() {
    JadwalKrt listKereta[100]; 
    int totalData = 0;
    
    Tiket* antrianDepan = NULL;
    Tiket* antrianBelakang = NULL;

    Tiket* tumpukanRiwayat = NULL;

    int menu;

    do {
        cout << "\n==========================================\n";
        cout << "   APP MANAJEMEN KERETA API (POSTTEST 4)\n";
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
                string inNamaPenumpang, inNamaKA, inRute;
                cin.ignore();
                cout << "\n--- Form Pemesanan Tiket ---\n";
                cout << "Nama Penumpang: "; getline(cin, inNamaPenumpang);
                tampilkanData(listKereta, totalData);
                cout << "Pilih jadwal kereta (masukkan nomor urut 1-" << totalData << "): ";
                int pilihan; cin >> pilihan;
                
                if (pilihan > 0 && pilihan <= totalData) {
                    inNamaKA = (listKereta + pilihan - 1)->namaKA;
                    inRute = (listKereta + pilihan - 1)->stAwal + " - " + (listKereta + pilihan - 1)->stAkhir;
                    enqueueAntrian(&antrianDepan, &antrianBelakang, inNamaPenumpang, inNamaKA, inRute);
                } else {
                    cout << ">> Pilihan jadwal tidak valid!\n";
                }
                break;
            }
            case 8:
                dequeueProses(&antrianDepan, &antrianBelakang, &tumpukanRiwayat);
                break;
            case 9:
                popRiwayat(&tumpukanRiwayat);
                break;
            case 10:
                peekData(antrianDepan, tumpukanRiwayat);
                break;
            case 11:
                tampilkanAntrian(antrianDepan);
                break;
            case 12:
                tampilkanRiwayat(tumpukanRiwayat);
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