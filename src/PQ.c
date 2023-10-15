#include "PQ.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap(PQ_t *pq, int indexA, int indexB); //利用 memcpy 實作 swap
static void ReheapDown(PQ_t * pq, int root, int bottom);
static void ReheapUp(PQ_t * pq, int root, int bottom);

/* 建立一個 pq, 其中 pqClass為此PQ的種類(MINHEAP or MAXHEAP)，元素大小為 elementSize, 最多元數個數為 maxSize, compare 是函數指標 */
void createPQ(PQ_t *pq, H_class pqClass, int elementSize, int maxSize, int (*compare)(void* elementA, void *elementB))
{
    pq->pqClass = pqClass;
    pq->heap.numElements = 0; // 陣列元素數目為0

    // pq->elementSize = elementSize;
    // 佔記憶體4bytes
    if((elementSize % 4) == 0)
        pq->elementSize = elementSize;
    else
        pq->elementSize = (elementSize/4 + 1)*4;

    pq->maxSize = maxSize;
    pq->heap.elements = (void *)malloc(pq->elementSize * pq->maxSize); // 配置元素大小*最大個數的記憶體
    pq->compare = compare;
}

int Enqueue(PQ_t *pq, void * elementA) /* add an element into PQ */
{
    if(IsFull(pq))
        return 0;
    else
    {
        pq->heap.numElements++;
        // pq->heap.elements[pq->heap.numElements-1] = newItem;
        memcpy(pq->heap.elements + (pq->heap.numElements-1) * pq->elementSize, elementA, pq->elementSize);
        ReheapUp(pq, 0, pq->heap.numElements-1);
        return 1;
    }
}

int IsEmpty(PQ_t *pq) /* return 0: not empty, 1: empty*/
{
    return pq->heap.numElements == 0;
}

int IsFull(PQ_t *pq) /* return 0: not full, 1:full */
{
    return pq->maxSize == pq->heap.numElements;
}

void * Dequeue(PQ_t *pq) /*delete an element from PQ */
{
    char *elementItem = (char*)malloc(pq->elementSize);
    memcpy(elementItem, (void *)pq->heap.elements, pq->elementSize);

    void *last = (void *)(pq->heap.elements + (pq->heap.numElements-1)*pq->elementSize);
    memcpy((void *)pq->heap.elements, last, pq->elementSize);

    pq->heap.numElements--;
    ReheapDown(pq, 0, pq->heap.numElements-1);
    return elementItem;
}

static void ReheapDown(PQ_t * pq, int root, int bottom) // 把root往下推(下沉)
{
    int maxChild, rightChild, leftChild;

    leftChild = 2*root+1;  // 左子樹的位置
    rightChild = 2*root+2; // 右子樹的位置

    if(leftChild <= bottom) // 左子樹在heap裡
    {
        if(leftChild == bottom) // 左子樹是最後一個元素（沒有右子樹）
            maxChild = leftChild;  // 左子樹是可能要交換的子樹
        else // 比較左右子樹
        {
            void *elementLeft = (void *)(pq->heap.elements + leftChild*pq->elementSize);
            void *elementRight = (void *)(pq->heap.elements + rightChild*pq->elementSize);
            if(pq->pqClass == MAXHEAP)
            {
                if(pq->compare(elementLeft, elementRight) <= 0) // 左子樹<=右子樹
                    maxChild = rightChild; // 右子樹是可能要交換的子樹
                else
                    maxChild = leftChild; // 左子樹是可能要交換的子樹
            }
            else // MINHEAP
            {
                if(pq->compare(elementLeft, elementRight) >= 0) // 左子樹>=右子樹
                    maxChild = rightChild; // 右子樹是可能要交換的子樹
                else
                    maxChild = leftChild; // 左子樹是可能要交換的子樹
            }
        }

        void *elementRoot = (void *)(pq->heap.elements + root*pq->elementSize);
        void *elementMax = (void *)(pq->heap.elements + maxChild*pq->elementSize);

        //根<最大的子樹 || 根>最小的子樹
        //重複直到根是最大/最小的元素
        if(pq->pqClass == MAXHEAP)
        {
            if(pq->compare(elementRoot, elementMax) < 0)
            {
                swap(pq, root, maxChild);
                ReheapDown(pq, maxChild, bottom);
            }
        }
        else
        {
            if(pq->compare(elementRoot, elementMax) > 0)
            {
                swap(pq, root, maxChild);
                ReheapDown(pq, maxChild, bottom);
            }
        }
    }
}

static void ReheapUp(PQ_t * pq, int root, int bottom) // 把bottom往上推(上浮)
{
    int parent;

    if(bottom > root) // 此樹非空
    {
        parent = (bottom-1)/2; // bottom父親的位置
        void *elementParent = (void *)(pq->heap.elements + parent*pq->elementSize);
        void *elementBottom = (void *)(pq->heap.elements + bottom*pq->elementSize);

        //bottom父親<bottom || bottom父親>bottom
        //直到根是最大/小的元素
        if(pq->pqClass == MAXHEAP)
        {
            if(pq->compare(elementParent, elementBottom) < 0)
            {
                swap(pq, parent, bottom);
                ReheapUp(pq, root, parent);
            }
        }
        else
        {
            if(pq->compare(elementParent, elementBottom) > 0)
            {
                swap(pq, parent, bottom);
                ReheapUp(pq, root, parent);
            }
        }
    }
}

static void swap(PQ_t *pq, int indexA, int indexB) //利用 memcpy 實作 swap
{
    void *elementA = (void *)(pq->heap.elements + indexA*pq->elementSize);
    void *elementB = (void *)(pq->heap.elements + indexB*pq->elementSize);
    char *buf = (char*)malloc(pq->elementSize);
    memcpy(buf, elementA, pq->elementSize);
    memcpy(elementA, elementB, pq->elementSize);
    memcpy(elementB, buf, pq->elementSize);
    free(buf);
}
