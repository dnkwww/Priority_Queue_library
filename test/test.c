#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"student.c"

int main()
{
    student_t node[6]=
    {
        {"C120308001", 70, 100},
        {"B220406001", 60, 90},
        {"D120306001", 80, 95},
        {"A220407001", 65, 90},
        {"D220506001", 10, 70},
        {"A120406001", 90, 90}
    };

    PQ_t maxPQ;
    createPQ(&maxPQ, MAXHEAP, sizeof(student_t), 100, compareMath);

    printf("IsEmpty: %d\n", IsEmpty(&maxPQ));
    printf("IsFull: %d\n", IsFull(&maxPQ));

    printf("-----------------------\n");
    printf("add student_t node into maxPQ:\n");
    int i;
    for(i=0; i<6; i++)
        Enqueue(&maxPQ, &node[i]);

    print(&maxPQ);

    printf("IsEmpty: %d\n", IsEmpty(&maxPQ));
    printf("IsFull: %d\n", IsFull(&maxPQ));

    printf("-----------------------\n");
    printf("after Dequeue node :\n");
    Dequeue(&maxPQ);
    print(&maxPQ);

    return 0;
}
