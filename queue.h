//
// Created by Kimberley on 3/21/2025.
//

#ifndef TRAITEMENT_AUTOMATES_QUEUE_H
#define TRAITEMENT_AUTOMATES_QUEUE_H
#define MAXSIZE 50
/**
 * @brief Structure for the queue of integers
 */
typedef struct s_queue
{
    int *values[MAXSIZE];
    int last;
    int first;
} t_queue, *p_queue;

/**
 * @brief Function to create a queue
 * @param
 * @return the queue
 */
p_queue createQueue();

/**
 * @brief Function to check if the queue is empty
 * @param p_queue : pointer to the queue
 * @return an integer : 0 if false, 1 if true
 */
int isEmptyQueue(p_queue);

/**
 * @brief Function to check if the queue is full
 * @return an integer : 0 if false, 1 if true
 */
int isFullQueue(p_queue);

/**
 * @brief Function to enqueue a value in the queue
 * @param p_queue : pointer to the queue
 * @param value : the position to enqueue
 * @return none
 */
void enqueue(p_queue,int);

/**
 * @brief Function to dequeue a value from the queue
 * @param p_queue : pointer to the queue
 * @return the value dequeued
 */
int dequeue(p_queue);

void displayQueue(p_queue q);


#endif //TRAITEMENT_AUTOMATES_QUEUE_H
