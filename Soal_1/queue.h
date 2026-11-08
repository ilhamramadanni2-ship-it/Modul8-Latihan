#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

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

// Primitif
void createQueue(Queue &Q);
bool isEmptyQueue(Queue Q);
address alokasi(string kode, int berat);
void dealokasi(address P);
void enqueue(Queue &Q, address P);
address dequeue(Queue &Q);
address findElm(Queue Q, string kode);
bool fFindElm(Queue Q, address P);
int nbList(Queue Q);
void printInfo(Queue Q);
void delAll(Queue &Q);

#endif