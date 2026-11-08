#include "queue.h"

// ==========================================
// VERSI 1: ARRAY GESER
// ==========================================
void geser_create(QueueGeser &Q) {
    Q.head = -1; Q.tail = -1; Q.pergeseran = 0;
}

bool geser_isEmpty(QueueGeser Q) { return Q.head == -1; }
bool geser_isFull(QueueGeser Q) { return Q.tail == MAX - 1; }

bool geser_enqueue(QueueGeser &Q, Rekaman R) {
    if (geser_isFull(Q)) return false;
    if (geser_isEmpty(Q)) Q.head = 0;
    Q.tail++;
    Q.info[Q.tail] = R;
    return true;
}

bool geser_dequeue(QueueGeser &Q, Rekaman &R) {
    if (geser_isEmpty(Q)) return false;
    R = Q.info[Q.head];
    // Geser semua elemen ke kiri
    for (int i = 0; i < Q.tail; i++) {
        Q.info[i] = Q.info[i + 1];
        Q.pergeseran++;
    }
    Q.tail--;
    if (Q.tail == -1) Q.head = -1; // Menjadi kosong
    return true;
}

void geser_print(QueueGeser Q) {
    cout << "[Geser] Head: " << Q.head << ", Tail: " << Q.tail << endl;
    for (int i = 0; i < MAX; i++) {
        if (i <= Q.tail && i >= Q.head) cout << "[" << Q.info[i].nomor << ":" << Q.info[i].nilai << "] ";
        else cout << "[ ] ";
    }
    cout << endl;
}

void geser_summary(QueueGeser Q) {
    if (geser_isEmpty(Q)) {
        cout << "Jumlah: 0, Total: 0, Min: TIDAK ADA, Max: TIDAK ADA, Rata-rata: TIDAK ADA\n";
        return;
    }
    int sum = 0, min = 9999, max = -9999;
    for (int i = Q.head; i <= Q.tail; i++) {
        sum += Q.info[i].nilai;
        if (Q.info[i].nilai < min) min = Q.info[i].nilai;
        if (Q.info[i].nilai > max) max = Q.info[i].nilai;
    }
    int n = Q.tail - Q.head + 1;
    cout << "Jumlah: " << n << ", Total: " << sum << ", Min: " << min << ", Max: " << max
         << ", Rata-rata: " << fixed << setprecision(2) << (float)sum/n << endl;
}

// ==========================================
// VERSI 2: ARRAY PEMADATAN
// ==========================================
void padat_create(QueuePadat &Q) {
    Q.head = -1; Q.tail = -1; Q.pergeseran = 0;
}

bool padat_isEmpty(QueuePadat Q) { return Q.head == -1; }
bool padat_isFull(QueuePadat Q) { return Q.tail == MAX - 1; }

bool padat_enqueue(QueuePadat &Q, Rekaman R) {
    if (padat_isFull(Q)) {
        if (Q.head > 0) {
            // Pemadatan
            int idx = 0;
            for (int i = Q.head; i <= Q.tail; i++) {
                Q.info[idx++] = Q.info[i];
                Q.pergeseran++;
            }
            Q.tail = idx - 1;
            Q.head = 0;
        } else {
            return false; // Benar-benar penuh
        }
    }
    if (padat_isEmpty(Q)) Q.head = 0;
    Q.tail++;
    Q.info[Q.tail] = R;
    return true;
}

bool padat_dequeue(QueuePadat &Q, Rekaman &R) {
    if (padat_isEmpty(Q)) return false;
    R = Q.info[Q.head];
    Q.head++;
    if (Q.head > Q.tail) Q.head = Q.tail = -1;
    return true;
}

void padat_print(QueuePadat Q) {
    cout << "[Padat] Head: " << Q.head << ", Tail: " << Q.tail << endl;
    for (int i = 0; i < MAX; i++) {
        if (i >= Q.head && i <= Q.tail && Q.head != -1) cout << "[" << Q.info[i].nomor << ":" << Q.info[i].nilai << "] ";
        else cout << "[ ] ";
    }
    cout << endl;
}

void padat_summary(QueuePadat Q) {
    if (padat_isEmpty(Q)) {
        cout << "Jumlah: 0, Total: 0, Min: TIDAK ADA, Max: TIDAK ADA, Rata-rata: TIDAK ADA\n";
        return;
    }
    int sum = 0, min = 9999, max = -9999;
    for (int i = Q.head; i <= Q.tail; i++) {
        sum += Q.info[i].nilai;
        if (Q.info[i].nilai < min) min = Q.info[i].nilai;
        if (Q.info[i].nilai > max) max = Q.info[i].nilai;
    }
    int n = Q.tail - Q.head + 1;
    cout << "Jumlah: " << n << ", Total: " << sum << ", Min: " << min << ", Max: " << max
         << ", Rata-rata: " << fixed << setprecision(2) << (float)sum/n << endl;
}

// ==========================================
// VERSI 3: CIRCULAR
// ==========================================
void circular_create(QueueCircular &Q) {
    Q.head = 0; Q.count = 0; Q.pergeseran = 0;
}

bool circular_isEmpty(QueueCircular Q) { return Q.count == 0; }
bool circular_isFull(QueueCircular Q) { return Q.count == MAX; }

bool circular_enqueue(QueueCircular &Q, Rekaman R) {
    if (circular_isFull(Q)) return false;
    int tail = (Q.head + Q.count) % MAX;
    Q.info[tail] = R;
    Q.count++;
    return true;
}

bool circular_dequeue(QueueCircular &Q, Rekaman &R) {
    if (circular_isEmpty(Q)) return false;
    R = Q.info[Q.head];
    Q.head = (Q.head + 1) % MAX;
    Q.count--;
    return true;
}

void circular_print(QueueCircular Q) {
    int tail = (Q.head + Q.count - 1) % MAX;
    cout << "[Circular] Head: " << Q.head << ", Count: " << Q.count << " (Tail: " << (Q.count == 0 ? -1 : tail) << ")" << endl;
    for (int i = 0; i < MAX; i++) {
        if (i < Q.count) cout << "[" << Q.info[(Q.head + i) % MAX].nomor << ":" << Q.info[(Q.head + i) % MAX].nilai << "] ";
        else cout << "[ ] ";
    }
    cout << endl;
}

void circular_summary(QueueCircular Q) {
    if (circular_isEmpty(Q)) {
        cout << "Jumlah: 0, Total: 0, Min: TIDAK ADA, Max: TIDAK ADA, Rata-rata: TIDAK ADA\n";
        return;
    }
    int sum = 0, min = 9999, max = -9999;
    for (int i = 0; i < Q.count; i++) {
        int val = Q.info[(Q.head + i) % MAX].nilai;
        sum += val;
        if (val < min) min = val;
        if (val > max) max = val;
    }
    cout << "Jumlah: " << Q.count << ", Total: " << sum << ", Min: " << min << ", Max: " << max
         << ", Rata-rata: " << fixed << setprecision(2) << (float)sum/Q.count << endl;
}