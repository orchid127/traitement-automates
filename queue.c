//
// Created by Kimberley on 3/21/2025.
//
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/**
 * @brief Function to create a queue
 * @param size : the size of the queue
 * @return the queue
 */
p_queue createQueue()
{
    p_queue queue = (t_queue*)malloc(sizeof(t_queue));
    queue->first = queue->last = 0;
    *queue->values = (int*)malloc(MAXSIZE * sizeof(int));
    return queue;
}

int isEmptyQueue(p_queue queue) {
    return (queue->first ==queue->last);
}

int isFullQueue(p_queue queue)
{
        return (queue->last - queue->first == MAXSIZE);
}

void enqueue(p_queue queue, int val)
{
    int pos;
    pos = queue->last % MAXSIZE;
    *queue->values[pos] = val;
    queue->last++;
}

int dequeue(p_queue queue)
{
    int res;
    int pos;
    pos = queue->first % MAXSIZE;
    res = *queue->values[pos];
    queue->first++;
    return res;
}

void displayQueue(p_queue queue)
{
    printf(" out <- ");
    for (int cpt = queue->first ; cpt < queue->last; cpt++)
    {
        printf("%d <- ", *queue->values[cpt%MAXSIZE]);
    }

    printf("in\n");

    return;
}