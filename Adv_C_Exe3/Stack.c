#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

charNode* addToHead(charNode* head, charNode* toAddstack);
void deletenode(charNode** head);
void flipBetweenHashes(const char* sentence);
Stack* flip_Between_Hashes(Stack* Stack_with_Hashes);
int size_of_stack(Stack* s);
/***************** Stack ADT Implementation *****************/
//The function initializes the administrative structure of the stack
void initStack(Stack* s)
{
	s->head = NULL;
}//initStack
//The function free stack
void destroyStack(Stack* s)
{
	free(s->head); //release the head
	// add your code here
}
//The function pushes  into a stack by adding it to the top of the linked list stored in the admin structure
void push(Stack* s, char data)
{
	charNode* newnode = (charNode*)malloc(sizeof(charNode));
	if (newnode == NULL)
	{
		printf("push: memory allocation problem\n");
		return;
	}
	newnode->data = data;
	s->head = addToHead(s->head, newnode);
}//push
//A function removes a stack node by removing the first node in the stack
char pop(Stack* s)
{
	char delete_val;
	delete_val = s->head->data;
	deletenode(&(s->head));//remove it from the stack
	return(delete_val);
}//pop

//The function checks if the stack is empty or not
int isEmptyStack(const Stack* s)
{
	if (s->head == NULL)
		return 1;
	else
		return 0;
}//isEmptyStack

/*************** Functions using stacks - Implementation/definition **************************/
//The function  print the input string in the order in which they appear in the string, until the character '#' appears. This character will not be printed,
//But will cause the printing order of the characters to be reversed between itand the next '#'.
void flipBetweenHashes(const char* sentence)
{
	int len = 0;
	char* temp = sentence;
	if (*(temp) == NULL)
	{
		printf("the sentence empty \n");
		return;
	}//if_sentence empty
	while (*(temp) != NULL)
	{
		len++;
		temp++;
	}//while
	Stack* Stack_Hashes = (Stack*)malloc(sizeof(Stack) * len);
	if (Stack_Hashes == NULL)
	{
		printf("flipBetweenHashes: memory allocation problem\n");
		return;
	}//if_flipBetweenHashes_memory allocation fail
	for (int i = len - 1; i >= 0; i--)
	{
		push(Stack_Hashes, *(sentence + i));
	}//push_to_newStack
	while ((Stack_Hashes) != NULL)
	{
		while ((Stack_Hashes->head->data) != '#')
		{
			printf("%c", pop(Stack_Hashes));
		}//print until the first #
		deletenode(&(Stack_Hashes->head));
		//Stack_Hashes++;
		flip_Between_Hashes(Stack_Hashes);
	}//BIG_WHILE  
	return;
}//flipBetweenHashes
//Auxiliary function, prints the inverting string between the 2 #
Stack* flip_Between_Hashes(Stack* Stack_with_Hashes)
{
	charNode* count_node = (charNode*)malloc(sizeof(charNode));
	charNode* node_hold = (charNode*)malloc(sizeof(charNode));
	if (count_node == NULL)
	{
		printf("flip_Between_Hashes_count_node: memory allocation problem\n");
		return;
	}
	if (node_hold == NULL)
	{
		printf("flip_Between_Hashes_count_node: memory allocation problem\n");
		return;
	}
	count_node = Stack_with_Hashes->head;
	int count = 0;
	while (((count_node->data) != '#') && ((count_node->data) != NULL))
	{
		count++;
		node_hold = count_node;
		count_node = count_node->next;
	}//count number of letters Between Hashes
	if ((count_node) == NULL)
		return (Stack_with_Hashes);
	if (count != 0)
	{
		Stack* temp_origital2 = (Stack*)malloc(sizeof(Stack) * count);
		if (temp_origital2 == NULL)
		{
			printf("flip_Between_Hashes: memory allocation problem\n");
			return;
		}//if_flip_Between_Hashes allocation fail
		for (int i = 0; i < count; i++)
		{
			push(temp_origital2, (pop(Stack_with_Hashes)));
		}//input to the upside down stack
		for (int i = 0; i < count; i++)
		{
			printf("%c", pop(temp_origital2));
		}//print Between_Hashes #
		deletenode(&(Stack_with_Hashes->head));
		return(Stack_with_Hashes);
	}//count != 0
}//flip_Between_Hashes
//The function check if the stack of characters is a Palindrome stack 
int isPalindrome(Stack* s)
{

	if (isEmptyStack(s) == 1)
		return 1;
	int count = size_of_stack(s);
	char val;
	Stack* reverse_stack = (Stack*)malloc(sizeof(Stack) * count);
	Stack* temp_stack1 = (Stack*)malloc(sizeof(Stack) * count);
	Stack* backtooriginal_stack = (Stack*)malloc(sizeof(Stack) * count);
	if ((reverse_stack == NULL) || (temp_stack1 == NULL) || (backtooriginal_stack == NULL))
	{
		printf("isPalindrome: memory allocation problem\n");
		return -1;
	}//if_isPalindrome_memory allocation fail
	for (int i = 0; i < count; i++)
	{
		val = pop(s);
		push(reverse_stack, val);
		push(temp_stack1, val);
	}
	for (int i = 0; i < count; i++)
	{
		push(backtooriginal_stack, pop(temp_stack1));
	}
	for (int i = 0; i < count / 2; i++)
	{
		if (pop(backtooriginal_stack) != pop(reverse_stack))
		{
			return 0;
		}
	}//FOR
	destroyStack(backtooriginal_stack);
	return 1;

}//check_if_palindrom
//The function checks and returns the size of the stack
int size_of_stack(Stack* s)
{
	charNode* count_node1 = (charNode*)malloc(sizeof(charNode));
	if (count_node1 == NULL)
	{
		printf("isPalindrome: memory allocation problem\n");
		return -1;
	}
	count_node1 = s->head;
	int count = 0;
	while ((count_node1) != NULL)
	{
		count++;
		count_node1 = count_node1->next;
	}//count the size of the stack
	free(count_node1);
	return count;
}//size_of_stack


//The function moves the first n places at the bottom of the stack (those farthest from the top) to the top of the stack without Hurt order between them.
void rotateStack(Stack* s, int n)
{
	int len = size_of_stack(s);
	if ((n < 0) || (n > len) || (isEmptyStack(s) == 1))
	{
		printf("rotateStack: something illigal\n");
		return;
	}
	Stack* part_up = (Stack*)malloc(sizeof(Stack) * (len - n));
	Stack* part_down = (Stack*)malloc(sizeof(Stack) * n);
	Stack* after_rotateStack = (Stack*)malloc(sizeof(Stack) * len);//Allcate space to the final stack
	if ((part_down == NULL) || (part_up == NULL))
	{
		printf("rotateStack: memory allocation problem\n");
		return -1;
	}//rotateStack_memory allocation fail
	for (int i = 0; i < len - n; i++)
	{
		push(part_up, pop(s));
	}
	for (int i = 0; i < n; i++)
	{
		push(part_down, pop(s));
	}//
	for (int i = 0; i < len - n; i++)
	{
		push(after_rotateStack, pop(part_up));
	}
	for (int i = 0; i < n; i++)
	{
		push(after_rotateStack, pop(part_down));
	}
	for (int i = 0; i < len; i++)
	{
		printf("%c", pop(after_rotateStack));
	}
}//rotateStack



//add a node to the head of the stack
charNode* addToHead(charNode* head, charNode* toAddstack)
{
	toAddstack->next = head;
	head = toAddstack;
	return head;
}//addToHead
//delete node from the stack
void deletenode(charNode** head)
{
	if (*head == NULL) return; //if stack empty
	charNode* tmp = *head;
	*head = (*head)->next;
	free(tmp);
}//deletenode







