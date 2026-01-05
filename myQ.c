#include "myQ.h"
unsigned int rpos = 0, wpos = 0, cnt = 0;
int q[MAX_LEN];
int PowerQ[POWER_OF_TWO_LEN];
 /*  Slot One Reserved Queue (SORQ)
    1. rpos와 wpos가 같으면 Empty 또는 Full이다.
    2. Full이면 더이상 쓰지 않고, Empty이면 더이상 읽지 않는다.
    3. 다음 쓸 위치가 읽을 위치이면 Full
    4. rpos만이 wpos == rpos를 만들수 있도록 함 
    5. MAX_LEN - 1 이 REAL_LEN에 해당함 (Slot 1개 희생)
*/
bool SORQ_isFull()
{
    return (wpos + 1) % MAX_LEN == rpos; 
}

bool SORQ_isEmpty()
{
    return wpos == rpos;
}

void SORQ_enqueue(int val)
{
    if(SORQ_isFull()) return;
    // q[wpos++ % MAX_LEN] = val;
    q[wpos] = val;
    wpos = (wpos + 1) % MAX_LEN; // wpos ovf 방지
}

int SORQ_dequeue()
{
    if(SORQ_isEmpty()) return INT_MIN;
    int ret = q[rpos];
    rpos = (rpos + 1) % MAX_LEN;
    return ret;
}


// Cnt 도입하여 전체 사용
bool CNTQ_isFull()
{
    return cnt == MAX_LEN; 
}

bool CNTQ_isEmpty()
{
    return cnt == 0;
}

void CNTQ_enqueue(int val)
{
    if(CNTQ_isFull()) return;
    // q[wpos++ % MAX_LEN] = val;
    q[wpos] = val;
    wpos = (wpos + 1) % MAX_LEN; // wpos ovf 방지
    cnt++;
}

int CNTQ_dequeue()
{
    if(CNTQ_isEmpty()) return INT_MIN;
    int ret = q[rpos];
    rpos = (rpos + 1) % MAX_LEN;
    cnt--;
    return ret;
}


// 비트 마스킹 방법 (Power of Two Queue)
// 제약조건: MAX_LEN이 2^n
/*  기존: index = wpos % 8; (나머지 연산)
    변경: index = wpos & 7; (비트 AND 연산)
*/
bool MSKQ_isFull()
{
    // return ((wpos + 1) & MASK) == rpos;
    // wpos/rpos 무한 증가 방식
    return wpos - rpos == MAX_LEN;
}

bool MSKQ_isEmpty()
{
    return wpos == rpos;
}

void MSKQ_enqueue(int val)
{
    if(MSKQ_isFull()) return;
    PowerQ[wpos++ & MASK] = val;
}

int MSKQ_dequeue()
{
    if(MSKQ_isEmpty()) return -1;
    return PowerQ[rpos++ & MASK];
}



/* 응용: 구조체 + MSKQ*/
 // 큐 초기화
void vq_init(VectorQueue* q)
{
    q->wpos = 0;
    memset(q->frame, 0, sizeof(q->frame)); // for문을 통한 초기화 대체
    memset(q->colSum, 0, sizeof(q->colSum));
}

// 새 벡터 push + 슬라이딩 합(sum) 업데이트
void vq_push(VectorQueue* q, int vec[VECTOR_SIZE])
{
    int idx = q->wpos;
      
    for(int i = 0; i < VECTOR_SIZE; i++)
    {
        // 1. 덮어쓸 자리의 벡터를 sum에서 미리 뺀다
        q->colSum[i] -= q->frame[idx][i];
        // 2. 입력 벡터 값으로 enqueue
        q->frame[idx][i] = vec[i];
        // 3. sum 갱신
        q->colSum[i] += vec[i];
    }

    // 4. 인덱스 갱신
    q->wpos = (q->wpos + 1) & FRAME_MASK;
}

// idx번째 프레임 얻기
int* vq_get(VectorQueue* q, int idx)
{
    int pos = (q->wpos + idx) & FRAME_MASK;
    return q->frame[pos];
}

// 현재 큐에 쌓인 프레임들의 평균 벡터 계산
void computeAverage(VectorQueue* q, float avg[VECTOR_SIZE])
{
    for(int i = 0; i < VECTOR_SIZE; i++)
    {
        avg[i] = (float)q->colSum[i] / FRAME_SIZE;
    }
}