#include <stdio.h>
#include <stdlib.h>

typedef struct mab {
    int offset, size, allocated;
    struct mab * next;
    struct mab * prev;
} MemBlock;

MemBlock * createMemBlock(MemBlock * prev, int size) {
    MemBlock * new = (MemBlock *) malloc(sizeof(MemBlock));
    if (prev == NULL)
        new->offset = 0;
    else
        new->offset = prev->offset + prev->size;
    new->size = size;
    new->allocated = 0;
    new->next = NULL;
    new->prev = prev;
    return new;
}

int memCheck(MemBlock * m, int size) {
    if (m == NULL) return 0;
    return (m->allocated == 1 ? 0 : (m->size >= size) ? 1 : 0);
}

int memAlloc(MemBlock * m, int size) {
    if (memCheck(m, size) == 0) 
        return 0;
    m->allocated = 1;
    return 1;
}

int memFree(MemBlock * m) {
    m->allocated = 0;
    return 1;
}

int memMerge(MemBlock * m) {
    if (m->allocated || m->next->allocated) return 0;
    if (m->next == NULL) return 0;
    m->size = m->size + m->next->size;
    m->next->next->prev = m;
    m->next = m->next->next;
    return 1;
}

int memSplit(MemBlock * m, int size) {
    if (memCheck(m, size) == 0) return 0;
    int newBlockSize = m->size - size;
    m->size = size;
    MemBlock * new = createMemBlock(m, newBlockSize);
    new->next = m->next;
    m->next = new;
    return 1;
}

void main() {
    MemBlock * root = createMemBlock(NULL, 100);
    root->next = createMemBlock(root, 50);
    root->next->next = createMemBlock(root->next, 30);
    root->next->next->next = createMemBlock(root->next->next, 120);


    int processesSizes[4] = {40, 10, 30, 60};
    int processesCount = 4;

    printf("Best Fit:\n");

    for (int i = 0; i < processesCount; i++) {
        MemBlock * iter = (MemBlock *) malloc(sizeof(MemBlock));
        MemBlock * bestBlock = NULL;
        iter = root;
        int bestInd = 0, ind = 0, processSize = processesSizes[i];

        while (iter != NULL) {
            if (memCheck(iter, processSize) && (bestBlock == NULL ? 1: (iter->size < bestBlock->size))) {
                bestBlock = iter;
                bestInd = ind;
            }
            iter = iter -> next;
            ind++;
        }

        if (memAlloc(bestBlock, processSize))
            printf("Block %d of size %d assigned to process %d of size %d\n", bestInd, bestBlock->size, i, processSize);
        else
            printf("No Block Available for process %d of size %d\n", i, processSize);
    }

    MemBlock * iter = (MemBlock *) malloc(sizeof(MemBlock));
    iter = root;
    while (iter != NULL) {
        iter->allocated = 0;
        iter = iter -> next;
    }

    printf("\nFirst Fit:\n");

    for (int i = 0; i < processesCount; i++) {
        MemBlock * iter = (MemBlock *) malloc(sizeof(MemBlock));
        iter = root;
        int ind = 0, processSize = processesSizes[i];

        while (iter != NULL) {
            if (memCheck(iter, processSize)) 
                break;
            iter = iter -> next;
            ind++;
        }

        if (memAlloc(iter, processSize))
            printf("Block %d of size %d assigned to process %d of size %d\n", ind, iter->size, i, processSize);
        else
            printf("No Block Available for process %d of size %d\n", i, processSize);
    }
}