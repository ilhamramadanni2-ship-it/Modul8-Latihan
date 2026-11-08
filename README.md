# Praktikum Struktur Data - Implementasi Queue (C++)

Implementasi ADT Queue untuk dua studi kasus: **Sistem Sortir Paket** berbasis Singly Linked List (Soal 1) dan **Buffer Hasil Ukur** berbasis Array (Soal 2) dengan tiga mekanisme berbeda dalam C++17.

## Struktur Folder

```text
praktikum_queue/
├── soal1/          # Soal 1: Sistem Sortir Paket (Singly Linked List)
│   ├── queue.h     # Deklarasi ADT & primitif Soal 1
│   ├── queue.cpp   # Implementasi primitif Soal 1
│   └── main.cpp    # Loop perintah interaktif (MASUK, PINDAH, dll)
└── soal2/          # Soal 2: Buffer Pencatatan Hasil Ukur (Array 3 Versi)
    ├── queue_3.h   # Deklarasi ADT (Geser, Padat, Circular)
    ├── queue_3.cpp # Implementasi 3 versi Queue serentak
    └── main_3.cpp  # Loop perintah interaktif (TULIS, AMBIL, dll)
```

## ADT Queue

### Soal 1 (Singly Linked List)
```cpp
struct Paket {
    string kode;
    int berat;
};
typedef Paket infotype;
typedef struct Node *address;

struct Node {
    infotype info;
    address next;
};
struct Queue {
    address head;
    address tail;
};
```

### Soal 2 (Array Berkapasitas 6)
```cpp
struct Rekaman {
    int nomor;
    int nilai;
};

// V1 (Geser) & V2 (Pemadatan)
struct QueueGeserPadat {
    Rekaman info[6];
    int head, tail, pergeseran;
};

// V3 (Circular)
struct QueueCircular {
    Rekaman info[6];
    int head, count, pergeseran;
};
```

## Perbedaan Tiga Versi (Soal 2)

| Fitur | Versi 1 (Array Geser) | Versi 2 (Array Pemadatan) | Versi 3 (Circular Queue) |
|---|---|---|---|
| **Head** | Selalu `0` (jika tidak kosong) | Maju saat `dequeue` | Maju melingkar (`% MAX`) |
| **Tail** | Maju saat `enqueue` | Maju saat `enqueue` | Dihitung: `(head + count) % MAX` |
| **Dequeue** | Geser SEMUA elemen ke kiri, `tail--` | Cukup `head++` | `head = (head + 1) % MAX`, `count--` |
| **Enqueue** | `tail++` | `tail++`, geser sisa data ke indeks awal *hanya* jika butuh ruang & `tail == 5` | Mengisi di indeks `tail` dinamis, `count++` |
| **Biaya Waktu** | Enqueue $O(1)$, Dequeue $O(n)$ | Enqueue $O(1)$ amortized (bisa $O(n)$ saat padat), Dequeue $O(1)$ | Enqueue $O(1)$, Dequeue $O(1)$ |
| **Biaya Geser**| Sangat boros pergeseran fisik | Hemat, bergeser sesekali | Tanpa pergeseran fisik di memori (0) |

## Cara Menjalankan

### Terminal (g++)
Buka terminal/PowerShell, masuk ke direktori folder yang sesuai, lalu kompilasi dan jalankan:

**Menjalankan Soal 1:**
```bash
cd soal1
g++ main.cpp queue.cpp -o soal1
./soal1            # Windows: .\soal1.exe
```

**Menjalankan Soal 2:**
```bash
cd soal2
g++ main_3.cpp queue_3.cpp -o soal2
./soal2            # Windows: .\soal2.exe
```

## Contoh Masukan dan Keluaran (Soal 2)

Skenario ini mensimulasikan input data secara interaktif (Ketik perintah di bawah ini ke dalam terminal setelah program berjalan):

**Masukan (Input):**
```text
TULIS 6 12 -4 7 0 15 6
AMBIL 2
TULIS 3 9 11 -2
TULIS 2 9 -2
RINGKAS
LIHAT
SELESAI
```

**Keluaran (Output):**
```text
Berhasil TULIS 6 data.
Mengambil 2 rekaman:
1:12
2:-4
Ditolak: ruang kosong tidak cukup.
Berhasil TULIS 2 data.
RINGKASAN DATA:
Jumlah: 6, Total: 35, Min: -2, Max: 15, Rata-rata: 5.83
[Statistik Pergeseran] Versi 1: 9 | Versi 2: 4 | Versi 3: 0
[Geser] Head: 0, Tail: 5
[3:7] [4:0] [5:15] [6:6] [7:9] [8:-2] 
[Padat] Head: 0, Tail: 5
[3:7] [4:0] [5:15] [6:6] [7:9] [8:-2] 
[Circular] Head: 2, Count: 6 (Tail: 1)
[3:7] [4:0] [5:15] [6:6] [7:9] [8:-2] 
Program selesai.
```

## Catatan Aturan Tambahan

* **All-or-Nothing Validasi:** Pada Soal 1 (`PINDAH n`, `KIRIM n`) dan Soal 2 (`TULIS k`, `AMBIL k`), jika nilai melebihi kapasitas memori atau parameter di luar rentang, maka **seluruh** baris perintah dibatalkan. Tidak ada pengeksekusian sebagian.
* **Keamanan Memori:** Pada Soal 1, fungsi `dealokasi(P)` / `delete` secara ketat dieksekusi setelah paket dikirim agar tidak terjadi *memory leak*. Pada Soal 2, perintah `KOSONGKAN` akan me-reset *pointer head/tail* tanpa menghapus jumlah pergeseran statistik sebelumnya.