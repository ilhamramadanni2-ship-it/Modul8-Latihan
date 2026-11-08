#include <iostream>
#include <string>
#include "queue.h" 

using namespace std;

// Fungsi bantu untuk menghitung total berat di satu queue
int totalBerat(Queue Q) {
    int total = 0;
    address P = Q.head;
    while (P != nullptr) {
        total += P->info.berat;
        P = P->next;
    }
    return total;
}

int main() {
    Queue A, B;
    createQueue(A);
    createQueue(B);

    int paketTerkirim = 0;
    int beratTerkirim = 0;
    string perintah;

    while (cin >> perintah) {
        if (perintah == "MASUK") {
            string kode;
            int berat;
            cin >> kode >> berat;
            
            // Validasi format
            if (kode.length() < 1 || kode.length() > 10 || berat < 1 || berat > 5000) {
                cout << "Ditolak: Kode atau berat tidak valid.\n";
                continue;
            }
            // Validasi keunikan hanya pada paket aktif di A atau B
            if (findElm(A, kode) != nullptr || findElm(B, kode) != nullptr) {
                cout << "Ditolak: Kode paket masih aktif di antrean.\n";
                continue;
            }
            
            address P = alokasi(kode, berat);
            if (P == nullptr) {
                cout << "Ditolak: Alokasi memori gagal.\n";
            } else {
                enqueue(A, P);
            }
            
        } else if (perintah == "PINDAH") {
            int n;
            cin >> n;
            // Tolak SELURUHNYA jika n melebihi kapasitas (tidak boleh pindah sebagian)
            if (n <= 0 || n > nbList(A)) {
                cout << "Ditolak: Jumlah pemindahan melebihi isi antrean A.\n";
            } else {
                for (int i = 0; i < n; i++) {
                    address P = dequeue(A);
                    enqueue(B, P);
                }
            }
            
        } else if (perintah == "KIRIM") {
            int n;
            cin >> n;
            // Tolak SELURUHNYA jika n melebihi kapasitas B
            if (n <= 0 || n > nbList(B)) {
                cout << "Ditolak: Jumlah pengiriman melebihi isi antrean B.\n";
            } else {
                for (int i = 0; i < n; i++) {
                    address P = dequeue(B);
                    cout << P->info.kode << " " << P->info.berat << "\n";
                    // Update statistik terkirim
                    paketTerkirim++;
                    beratTerkirim += P->info.berat;
                    dealokasi(P); // Bebaskan memori
                }
            }
            
        } else if (perintah == "CARI") {
            string kode;
            cin >> kode;
            
            address P = findElm(A, kode);
            if (P != nullptr) {
                int pos = 1;
                address curr = A.head;
                while (curr != P) { pos++; curr = curr->next; }
                cout << "A " << pos << " " << P->info.berat << "\n";
            } else {
                P = findElm(B, kode);
                if (P != nullptr) {
                    int pos = 1;
                    address curr = B.head;
                    while (curr != P) { pos++; curr = curr->next; }
                    cout << "B " << pos << " " << P->info.berat << "\n";
                } else {
                    cout << "TIDAK DITEMUKAN\n";
                }
            }
            
        } else if (perintah == "LIHAT") {
            cout << "Isi A: "; printInfo(A);
            cout << "Isi B: "; printInfo(B);
            
        } else if (perintah == "REKAP") {
            cout << "A " << nbList(A) << " " << totalBerat(A) << "\n";
            cout << "B " << nbList(B) << " " << totalBerat(B) << "\n";
            cout << "TERKIRIM " << paketTerkirim << " " << beratTerkirim << "\n";
            
        } else if (perintah == "BERSIHKAN") {
            delAll(A);
            delAll(B);
            // Sesuai aturan: Menghapus paket TANPA mereset statistik terkirim
            
        } else if (perintah == "SELESAI") {
            delAll(A);
            delAll(B);
            break;
            
        } else {
            cout << "Ditolak: Perintah tidak dikenali.\n";
        }
    }
    return 0;
}