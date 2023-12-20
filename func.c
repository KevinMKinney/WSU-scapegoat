#include "func.h"

// recursively itterate through tree to find input string
int searchTree(int val, struct node* root) {

	if (root == NULL) {
		return 0;
	}
	// init variables
	struct node* search = root;
	while (search != NULL) {
		
		if (search->value == val) {
			return 1;
		}

		if (search->value > val) {
			search = search->left;
		} else {
			search = search->right;
		}
	}
	return 0;
}

// recursively itterate through tree until an empty node is reached to insert
int insertNode(int val, struct node** search, struct node** root, int* n, int* q) {

	if (*search == NULL) {
		*search = newNode(val);
		(*n)++;
		(*q)++;

		//printf("bool: %d > %f | N = %d | Q = %d\n", nodeDepth(*root, val), LOG32(*q), (*n), (*q));
		return (nodeDepth(*root, val) > LOG32(*q));
	} else {
		int ret;
		//printf("search: %d | val: %d\n", (*search)->value, val);
		if ((*search)->value > val) {
			//printf("when %d, search is: %p\n", val, (*search));
			ret = insertNode(val, &(*search)->left, root, n, q);
			if (ret) {
				//printf("right--: %d > %d\n", (3*treeSize((*search)->left)), (2*treeSize(*search)));
				//if (((*search)->left != NULL) && ((3*treeSize((*search)->left)) > (2*treeSize(*search)))) {
				if ((3*treeSize((*search)->left)) > (2*treeSize(*search))) {
					
					*search = rebuildTree(*n, *search);
				}
			}
			return ret;
		} else {
			//printf("when %d, search is: %p\n", val, (*search));
			ret = insertNode(val, &(*search)->right, root, n, q);
			if (ret) {
				//printf("right--: %d > %d\n", (3*treeSize((*search)->right)), (2*treeSize(*search)));
				//if (((*search)->right != NULL) && ((3*treeSize((*search)->right)) > (2*treeSize(*search)))) {
				if ((3*treeSize((*search)->right)) > (2*treeSize(*search))) {

					*search = rebuildTree(*n, *search);
				}
			}
			return ret;
		}
	}
	
	return 0;
}

// helper function for making new nodes
struct node* newNode(int val) {
	struct node* temp = malloc(sizeof(struct node));
	// free and stop if cannot allocate space
	if (temp == NULL) {
		//free(temp);
		return NULL;
	}
	temp->value = val;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

// function recursively itterate through tree and removes nodes
void emptyTree(struct node* current) {
	if (current != NULL) {
		emptyTree(current->left);
		current->left = NULL;
		emptyTree(current->right);
		current->right = NULL;
		// free all node memory except for root
		//if (current != root) {
		free(current);
		//}
		//current = NULL;
	}
}

// scapegoat delete
struct node* scapegoatDelete(int val, struct node* delete, int* n, int* q) {
	// base case
	if (delete == NULL) {
		return NULL;
	}

	// move down tree
	if (val < delete->value) {
		delete->left = scapegoatDelete(val, delete->left, n, q);
		return delete;
	}
	if (val > delete->value) {
		delete->right = scapegoatDelete(val, delete->right, n, q);
		return delete;
	}

	// delete for no left child
	if (delete->left == NULL) {
		(*n)--;
		struct node* temp = delete->right;
		free(delete);

		// check tree balance
		if (2*(*n) < (*q)) {
			rebuildTree(*n, delete);
			*q = *n;
		}

		return temp;
	}

	// delete for no right child
	if (delete->right == NULL) {
		(*n)--;
		struct node* temp = delete->left;
		free(delete);

		// check tree balance
		if (2*(*n) < (*q)) {
			rebuildTree(*n, delete);
			*q = *n;
		}

		return temp;
	}
	
	// find left-most node in from the right child
	struct node* temp = delete->right;
	while (temp->left != NULL) {
		temp = temp->left;
	}
		
	// replace target value with temp
	delete->value = temp->value;

	// delete temp
	delete->right = scapegoatDelete(temp->value, delete->right, n, q);

	return delete;
}

// standard bst delete 
struct node* deleteNode(int val, struct node* delete) {
	// base case
	if (delete == NULL) {
		return NULL;
	}

	// move down tree
	if (val < delete->value) {
		delete->left = deleteNode(val, delete->left);
		return delete;
	}
	if (val > delete->value) {
		delete->right = deleteNode(val, delete->right);
		return delete;
	}

	// delete for no left child
	if (delete->left == NULL) {
		struct node* temp = delete->right;
		free(delete);
		return temp;
	}

	// delete for no right child
	if (delete->right == NULL) {
		struct node* temp = delete->left;
		free(delete);
		return temp;
	}
	
	// find left-most node in from the right child
	struct node* temp = delete->right;
	while (temp->left != NULL) {
		temp = temp->left;
	}
		
	// replace target value with temp
	delete->value = temp->value;

	// delete temp
	delete->right = deleteNode(temp->value, delete->right);

	return delete;
}

// functions for printing tree values
void inTraverse(struct node* current) {
	if (current != NULL) {
		inTraverse(current->left);
		printf("%d ", current->value);
		inTraverse(current->right);
	}
}

void preTraverse(struct node* current) {
	if (current != NULL) {
		printf("%d ", current->value);
		inTraverse(current->left);
		inTraverse(current->right);
	}
}

void postTraverse(struct node* current) {
	if (current != NULL) {
		inTraverse(current->left);
		inTraverse(current->right);
		printf("%d ", current->value);
	}
}


struct node* rebuildTree(int n, struct node* scapegoat) {
	// n is not used

	// what is a "dummy node"?
	int val = 1000;
	struct node* w = newNode(val);
	//struct node* w = NULL;

	struct node* z = flatten(scapegoat, w);
	//printTree(z, 0);
	z = buildTree((treeSize(z)), z);

	/* // code for removing dummy node (causes segfault earlier)
	struct node* temp = z;
	while (temp->right->value != val) {
		temp = temp->right;
	}
	temp->right = NULL;
	free(w);
	*/
	//printTree(z, 0);
	z = deleteNode(val, z);
	//printTree(z, 0);
	//printf("W: %d\n", w->value);
	return z;
	//return w->left;
}


struct node* flatten(struct node* x, struct node* y) {
	if (x == NULL) {
		return y;
	}
	x->right = flatten(x->right, y);
	return flatten(x->left, x);
} 

struct node* buildTree(int n, struct node* x) {
	/*
	if (x == NULL) {
		return NULL;
	}*/
	if (n == 0) {
		x->left = NULL;
		return x;
	}
	double cal = (n-1)/2;
	struct node* r = buildTree((int)ceil(cal), x);
	struct node* s = buildTree((int)floor(cal), r->right);
	/*
	s->left = NULL;
	if (r->right != NULL) {
		s = buildTree((int)floor(cal), r->right);
	}*/
	
	// this also works: struct node* s = buildTree((int)cal, r->right);
	r->right = s->left;
	s->left = r;
	return s;
}

// helper function; returns the depth of a node from another node 
int nodeDepth(struct node* search, int val) {
	if (search == NULL) {
		return 0;
	} else {
		if (search->value > val) {
			return 1 + nodeDepth(search->left, val);
		} else {
			return 1 + nodeDepth(search->right, val);
		}
	}
	
	return 0;
}

int treeSize(struct node* search) {
	if (search == NULL) {
		return 0;
	} else {
		return 1 + treeSize(search->right) + treeSize(search->left);
	}
	
	return 0;
}

// function that prints tree (yoinked from geekforgeeks)
void printTree(struct node* root, int space) {
	if (root == NULL) {
		return;
	}
	space += 5;
	printTree(root->right, space);
	printf("\n");
	for (int i = 5; i < space; i++) {
		printf(" ");
	}
	printf("%d\n", root->value);
	printTree(root->left, space);
}
