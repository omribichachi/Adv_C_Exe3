#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Stack.h"
#include "Queue.h"
#include <string.h>
#include <stdlib.h>
#define len_sentence 100

void main()
{
	Queue q;
	initQueue(&q);
	unsigned int num;
	int check;
	char sentence[len_sentence];
	char sign;
	char* sentence_ptr;
	Stack* newStack = (Stack*)malloc(sizeof(Stack));
	initStack(newStack);
	int temp, check_if_empty, n;
	printf("for queue 1 for stack 2\n");
	scanf_s("%d", &temp);
	if (temp == 1)
	{
		do
		{
			printf("choose one:\n 1 for add item\n 2 for remove item \n 3 for rotate\n 4 cut and replace \n 5 for sort \n 6 for destroy \n 7 for exit\n");
			scanf_s("%d", &temp);
			switch (temp)
			{

			case 1:
				printf("enter number: ");
				scanf_s("%d", &num);
				enqueue(&q, num);
				printQueue(&q);
				break;
			case 2:
				dequeue(&q);
				printQueue(&q);
				break;
			case 3:
				rotateQueue(&q);
				printQueue(&q);
				break;
			case 4:
				cutAndReplace(&q);
				printQueue(&q);
				break;
			case 5:
				sortKidsFirst(&q);
				printQueue(&q);
				break;
			case 6:
				destroyQueue(&q);
			case 7:
				break;
			default:
				printf("try again\n");
				break;
			}
		} while (temp != 7);
	}
	else
	{
		do
		{
			printf("\n choose one:\n 1 for push data\n 2 for delete data\n 3 for Check if the stuck is empty \n 4 for check the size of stack \n 5 to check if the stack is palindrom stack \n 6 to rotate the Stack \n 7 to flip Between Hashes \n 8 for destroy stack\n 9 for exit\n");
			scanf("%d", &temp);
			switch (temp)
			{
			case 1: printf("Enter the data: ");
				fseek(stdin, 0, SEEK_END);
				scanf("%c", &sign);
				push(newStack, sign);
				break;
			case 2:
				printf("\n Pop\n   %c", pop(newStack));
				break;
			case 3:
				check_if_empty = (newStack);
				if (check_if_empty == 1)
					printf("\n the stuck is enpty\n ");
				else
					printf("\n the stuck is not enpty\n ");
				break;
			case 4:
				printf("\n the size of stack is %d:\n ", size_of_stack(newStack));
				break;
			case 5:
				if (isPalindrome(newStack) == 1)
				{
					printf("\n the stack is palindrom \n ");
				}
				else
				{
					printf("\n the stack is not a palindrom stack\n ");
				}
				break;
			case 6:
				printf("Enter the number places to rotate : ");
				scanf("%d", &n);
				rotateStack(newStack, n);
				break;
			case 7:
				printf("\n  plese enter a sentence \n");
				fseek(stdin, 0, SEEK_END);
				scanf(" %s", sentence);
				sentence_ptr = (char*)(malloc(strlen(sentence) + 1));
				if (sentence_ptr != NULL)
					strcpy(sentence_ptr, sentence);//copy the input, end when \0
				else
				{
					printf("allocation error");
					return;
				}
				printf("\n  the stuck after flip Between Hashes if there was \n ");
				flipBetweenHashes(sentence_ptr);
				break;
			case 8:
				destroyStack(newStack);
				break;
			case 9:
				break;
			default: printf("\n Wrong. Pls try again");
			}
		} while (temp != 9);
	}


}