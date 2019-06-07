#ifndef ITD_NODE___
#define ITD_NODE___

#include "stdlib.h"
#include "stdio.h"

typedef struct node {
	int x;
	int y;
	struct node* next;
}Node;

Node* createNode(int x, int y);

#endif