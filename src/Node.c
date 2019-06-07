#include "Node.h"

Node* createNode(int x, int y) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL) {
		fprintf(stderr, "Error allocation memory");
        exit(1);
	}
	(*newNode).x = x;
	(*newNode).y = y;
	(*newNode).next = NULL;

	return newNode;
}