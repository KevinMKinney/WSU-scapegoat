//#ifndef "func.h"
//#define "func.h"
#ifndef FUNC_H
#define FUNC_H
// include c libraries
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
// structs
struct node {
	int value;
	struct node* left;
	struct node* right;
};
// macros
#define LOG32(n) (log(n) / log(3.0/2.0))
// functions
int searchTree(int val, struct node* root);
int insertNode(int val, struct node** search, struct node** root, int* n, int* q);
struct node* newNode(int val);
void emptyTree(struct node* current);
struct node* scapegoatDelete(int val, struct node* delete, int* n, int* q);
struct node* deleteNode(int val, struct node* delete);
void inTraverse(struct node* current);
void preTraverse(struct node* current);
void postTraverse(struct node* current);
struct node* rebuildTree(int n, struct node* scapegoat);
struct node* flatten(struct node* x, struct node* y);
struct node* buildTree(int n, struct node* x);
int nodeDepth(struct node* search, int val);
int treeSize(struct node* search);
void printTree(struct node* root, int space);

#endif
