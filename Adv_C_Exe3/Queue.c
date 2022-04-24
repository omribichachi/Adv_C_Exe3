#include "Queue.h"
#include <stdio.h>

/***************** Queue ADT Implementation *****************/
void initQueue(Queue* q)
{
	q->head = q->tail = NULL;
}

//free the queue
void destroyQueue(Queue* q)
{
	free(q->tail);
	free(q->head);
}

//the function add item to the tail
void enqueue(Queue* q, unsigned int data)
{
	intNode* p = (intNode*)malloc(sizeof(intNode));
	//check allocation code added here…
	if (p == NULL)
	{
		printf("allocation error");
	}
	else
	{
		p->data = data; // set element data
		p->next = NULL;
		if (!isEmptyQueue(q)) q->tail->next = p; // not Empty?
		//Add after last:
		else q->head = p; // Otherwise – it becomes
		//first
		q->tail = p; // update queue tail
	}
}

//the function remove the head
unsigned int dequeue(Queue* q)
{
	if (isEmptyQueue(q))
	{
		printf("Cannot dequeue an empty queue!");
		return 0;
	}
	int temp = q->head->data;
	intNode* p = q->head;
	q->head = q->head->next;
	if (q->head == NULL) //if queue gets empty
		q->tail = NULL;//both front and rear NULL
	free(p);
	return temp;
}
//the function checks if the queue is empty
int isEmptyQueue(const Queue* q)
{
	if (q->head == NULL && q->tail == NULL)return 1;
	else
		return 0;
}

/***************** Functions using Queues - Implementation/definition **************************/

void rotateQueue(Queue* q)//the last in the queue become the first 
{
	Queue temp;
	initQueue(&temp);
	while (q->head != q->tail)//replace the queue to temp queue besides of the last
	{
		enqueue(&temp, dequeue(q));
	}
	while (!isEmptyQueue(&temp))
	{
		enqueue(q, dequeue(&temp));
	}
	destroyQueue(&temp);
}
//The function will cut the queue into 2 parts of the same length. 
// Flip the order of the organs in a half that is close to the tail of the queue and change between The locations of two parts after the change.
// As soon as the queue counts an odd number of organs,
//calculate the average queue, add the result to the queue tailand then continue according to the description of the even case.

void cutAndReplace(Queue* q)
{
	Queue temp1, temp2;
	initQueue(&temp1);
	initQueue(&temp2);
	int len = countQueue(q);
	int sum = sumQueue(q);
	if ((len % 2) != 0)
	{
		enqueue(q, (sum / len));
		len++;
	}
	for (int i = 0; i < (len / 2); i++)
	{
		enqueue(&temp1, dequeue(q));
	}
	for (int i = 0; i < (len / 2); i++)
	{
		rotateQueue(q);
		enqueue(&temp2, dequeue(q));
	}
	while (!isEmptyQueue(&temp2))
	{
		enqueue(q, dequeue(&temp2));
	}
	while (!isEmptyQueue(&temp1))
	{
		enqueue(q, dequeue(&temp1));
	}


}

//The function will sort the queue in descending order so that the high 
//numbers are close to the tail of the queueand the low numbers are close to the top.
void sortKidsFirst(Queue* q)
{
	Queue temp;
	initQueue(&temp);
	while (!isEmptyQueue(q))
	{
		enqueue(&temp, removeMinimum(q));
	}
	while (!isEmptyQueue(&temp))
	{
		enqueue(q, dequeue(&temp));
	}
	destroyQueue(&temp);
}
// the function checks how much items in the queue
int countQueue(Queue* q)
{
	int counter = 0;
	Queue temp;
	initQueue(&temp);
	while (!isEmptyQueue(q))
	{
		enqueue(&temp, dequeue(q));
		counter++;
	}
	while (!isEmptyQueue(&temp))
	{
		enqueue(q, dequeue(&temp));
	}
	return counter;
}
//the function calculate the sum of the items in the queue
int sumQueue(Queue* q)
{
	int sum = 0;
	Queue temp;
	initQueue(&temp);
	while (!isEmptyQueue(q))
	{
		sum += q->head->data;
		enqueue(&temp, dequeue(q));
	}
	while (!isEmptyQueue(&temp))
	{
		enqueue(q, dequeue(&temp));
	}
	return sum;
}

//the function remove the minimum item in the queue
int removeMinimum(Queue* q)
{
	Queue temp;
	initQueue(&temp);
	int min = dequeue(q);
	int check;
	while (!isEmptyQueue(q))
	{
		check = dequeue(q);
		if (check < min)
		{
			enqueue(&temp, min);
			min = check;
		}
		else
		{
			enqueue(&temp, check);
		}
	}
	while (!isEmptyQueue(&temp))
	{
		enqueue(q, dequeue(&temp));
	}
	destroyQueue(&temp);
	return min;
}
//the function print the queue
void printQueue(Queue* q)
{
	Queue temp;
	int num;
	initQueue(&temp);
	printf("\n");
	while (!isEmptyQueue(q))
	{
		num = dequeue(q);
		printf("%d ", num);
		enqueue(&temp, num);
	}
	printf("\n");
	while (!isEmptyQueue(&temp))
	{
		enqueue(q, dequeue(&temp));
	}
	return;
}