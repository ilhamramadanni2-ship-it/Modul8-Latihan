#include "queue.h"

void createQueue(Queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(Queue Q) {
    return Q.head == nullptr;
}

address alokasi(string kode, int berat) {
    address P = new Node;
    if (P != nullptr) {
        P->info.kode = kode;
        P->info.berat = berat;
        P->next = nullptr;
    }
    return P;
}

void dealokasi(address P) {
    delete P;
}

void enqueue(Queue &Q, address P) {
    if (isEmptyQueue(Q)) {
        Q.head = P;
        Q.tail = P;
    } else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

address dequeue(Queue &Q) {
    if (isEmptyQueue(Q)) {
        return nullptr;
    }
    address P = Q.head;
    if (Q.head == Q.tail) {
        Q.head = nullptr;
        Q.tail = nullptr;
    } else {
        Q.head = P->next;
    }
    P->next = nullptr;
    return P;
}

address findElm(Queue Q, string kode) {
    address P = Q.head;
    while (P != nullptr) {
        if (P->info.kode == kode) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

bool fFindElm(Queue Q, address P) {
    address curr = Q.head;
    while (curr != nullptr) {
        if (curr == P) return true;
        curr = curr->next;
    }
    return false;
}

int nbList(Queue Q) {
    int count = 0;
    address P = Q.head;
    while (P != nullptr) {
        count++;
        P = P->next;
    }
    return count;
}

void printInfo(Queue Q) {
    if (isEmptyQueue(Q)) {
        cout << "(Kosong)" << endl;
    } else {
        address P = Q.head;
        while (P != nullptr) {
            cout << "[" << P->info.kode << ", " << P->info.berat << "g] -> ";
            P = P->next;
        }
        cout << "NULL" << endl;
    }
}

void delAll(Queue &Q) {
    address P;
    while (!isEmptyQueue(Q)) {
        P = dequeue(Q);
        dealokasi(P);
    }
}