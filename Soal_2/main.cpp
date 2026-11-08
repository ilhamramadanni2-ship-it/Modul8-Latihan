#include <iostream>
#include <string>
#include <vector>
#include "queue_3.h"

using namespace std;

void handleTulis(QueueGeser &Q1, QueuePadat &Q2, QueueCircular &Q3, int &nextNomor) {
    int k;
    cin >> k;
    
    // Tampung sementara nilai masukan
    vector<int> nilaiMasuk(k);
    bool valid = true;
    for (int i = 0; i < k; i++) {
        cin >> nilaiMasuk[i];
        if (nilaiMasuk[i] < -1000 || nilaiMasuk[i] > 1000) {
            valid = false;
        }
    }
    
    // Validasi All-or-Nothing
    if (k < 1 || k > 6) {
        cout << "Ditolak: k harus antara 1-6.\n";
        return;
    }
    if (!valid) {
        cout << "Ditolak: terdapat nilai di luar rentang (-1000 s.d 1000).\n";
        return;
    }
    if (k > (MAX - Q3.count)) {
        cout << "Ditolak: ruang kosong tidak cukup.\n";
        return;
    }

    // Jika seluruhnya valid, masukkan ke ketiga antrean
    for (int i = 0; i < k; i++) {
        Rekaman R = {nextNomor, nilaiMasuk[i]};
        geser_enqueue(Q1, R);
        padat_enqueue(Q2, R);
        circular_enqueue(Q3, R);
        
        nextNomor++; // Increment nomor urut hanya jika data berhasil masuk
    }
}

void handleAmbil(QueueGeser &Q1, QueuePadat &Q2, QueueCircular &Q3) {
    int k;
    cin >> k;
    
    // Validasi
    if (k <= 0 || k > Q3.count) {
        cout << "Ditolak: kuantitas pengambilan tidak valid atau data kurang.\n";
        return;
    }

    // Eksekusi pengambilan, cetak output dari salah satu queue
    for (int i = 0; i < k; i++) {
        Rekaman R1, R2, R3;
        geser_dequeue(Q1, R1);
        padat_dequeue(Q2, R2);
        circular_dequeue(Q3, R3);
        
        cout << R3.nomor << ":" << R3.nilai << "\n";
    }
}

void handleLihat(QueueGeser Q1, QueuePadat Q2, QueueCircular Q3) {
    geser_print(Q1);
    padat_print(Q2);
    circular_print(Q3);
}

void handleRingkas(QueueGeser Q1, QueuePadat Q2, QueueCircular Q3) {
    circular_summary(Q3); 
    // Anda juga bisa mencetak pergeseran di sini untuk keperluan analisis laporan
    // cout << "Pergeseran -> V1: " << Q1.pergeseran << " | V2: " << Q2.pergeseran << " | V3: " << Q3.pergeseran << "\n";
}

int main() {
    QueueGeser Q1; geser_create(Q1);
    QueuePadat Q2; padat_create(Q2);
    QueueCircular Q3; circular_create(Q3);
    
    int nextNomor = 1;
    string perintah;

    while (cin >> perintah) {
        if (perintah == "TULIS") {
            handleTulis(Q1, Q2, Q3, nextNomor);
        } 
        else if (perintah == "AMBIL") {
            handleAmbil(Q1, Q2, Q3);
        }
        else if (perintah == "LIHAT") {
            handleLihat(Q1, Q2, Q3);
        }
        else if (perintah == "RINGKAS") {
            handleRingkas(Q1, Q2, Q3);
        }
        else if (perintah == "KOSONGKAN") {
            // Sesuai aturan: membersihkan buffer TANPA mengulang nomor urut atau penghitung pergeseran
            Q1.head = -1; Q1.tail = -1;
            Q2.head = -1; Q2.tail = -1;
            Q3.head = 0; Q3.count = 0;
        }
        else if (perintah == "SELESAI") {
            break;
        }
        else {
            cout << "Ditolak: Perintah tidak dikenali.\n";
        }
    }

    return 0;
}