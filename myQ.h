#ifndef MYQ_H
#define MYQ_H

#include <limits.h>
#include <stdbool.h>
#define MAX_LEN 10
#define POWER_OF_TWO_LEN 16
#define MASK (POWER_OF_TWO_LEN - 1)
extern int q[MAX_LEN];
extern int PowerQ[POWER_OF_TWO_LEN];
extern int rpos, wpos;
extern int cnt;

#define FRAME_SIZE 32
#define FRAME_MASK (FRAME_SIZE - 1)
#define VECTOR_SIZE 50

typedef struct {
    int frame[FRAME_SIZE][VECTOR_SIZE];
    int wpos;
    int colSum[VECTOR_SIZE];
} VectorQueue;

bool OSRQ_isFull();
bool OSRQ_isEmpty();
void OSRQ_enqueue(int val);
int OSRQ_dequeue();

bool CNTQ_isFull();
bool CNTQ_isEmpty();
void CNTQ_enqueue(int val);
int CNTQ_dequeue();

bool MSKQ_isFull();
bool MSKQ_isEmpty();
void MSKQ_enqueue(int val);
int MSKQ_dequeue();


void vq_init(VectorQueue* q);
void vq_push(VectorQueue* q, int vec[VECTOR_SIZE]);
int* vq_get(VectorQueue* q, int idx);
void computeAverage(VectorQueue* q, float avg[VECTOR_SIZE]);

#endif