#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PQ.h"

typedef struct myElement
{
    char ID[10];
    int math;
    int eng;
} student_t;

int compareMath(void *elementA, void *elementB)
{
    int mathA = ((student_t *)elementA)->math;
    int mathB = ((student_t *)elementB)->math;
    if(mathA > mathB)
    {
        return 1;
    }
    else if(mathA < mathB)
    {
        return -1;
    }
    return 0;
}

void print(PQ_t *pq)
{
    int i;
    student_t *temp;
    for (i=0; i<pq->heap.numElements; i++)
    {
        temp = (student_t *)(pq->heap.elements+i*sizeof(student_t));
        temp->ID[10] = '\0';
        printf("index=%d, ID=%s,math=%d, eng=%d\n",i,temp->ID, temp->math, temp->eng);
    }
}

