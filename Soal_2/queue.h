#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 6;

struct Rekaman {
    int nomor;
    int nilai;
};

struct QueueGeser {
    Rekaman info[MAX];
    int head;
    int tail;
    int pergeseran;
};

struct QueuePadat {
    Rekaman info[MAX];
    int head;
    int tail;
    int pergeseran;
};

struct QueueCircular {
    Rekaman info[MAX];
    int head;
    int count;
    int pergeseran;
};

// --- Versi 1: Array Geser ---
void geser_create(QueueGeser &Q);
bool geser_isEmpty(QueueGeser Q);
bool geser_isFull(QueueGeser Q);
bool geser_enqueue(QueueGeser &Q, Rekaman R);
bool geser_dequeue(QueueGeser &Q, Rekaman &R);
void geser_print(QueueGeser Q);
void geser_summary(QueueGeser Q);

// --- Versi 2: Array Pemadatan ---
void padat_create(QueuePadat &Q);
bool padat_isEmpty(QueuePadat Q);
bool padat_isFull(QueuePadat Q);
bool padat_enqueue(QueuePadat &Q, Rekaman R);
bool padat_dequeue(QueuePadat &Q, Rekaman &R);
void padat_print(QueuePadat Q);
void padat_summary(QueuePadat Q);

// --- Versi 3: Circular ---
void circular_create(QueueCircular &Q);
bool circular_isEmpty(QueueCircular Q);
bool circular_isFull(QueueCircular Q);
bool circular_enqueue(QueueCircular &Q, Rekaman R);
bool circular_dequeue(QueueCircular &Q, Rekaman &R);
void circular_print(QueueCircular Q);
void circular_summary(QueueCircular Q);

#endif