#include "func.h"

int main() {
	// var initialization
	// input vars
	char input;
	int val;
	char cval;

	// tree vars
	struct node* root = NULL;
	int n = 0;
	int q = 0;

	do {
		// get command
		do {
			scanf("%c", &input);
		} while(isspace(input));

		switch (input) {  
			// insert        
			case 'i': 
				// get value
				scanf("%d", &val);
				// insert only if word is not in tree
				if (!searchTree(val, root)) {
					insertNode(val, &root, &root, &n, &q);
				}
				break;

			// delete 
			case 'd': 
				scanf("%d", &val);
				if (searchTree(val, root)) {
					root = scapegoatDelete(val, root, &n, &q);
				}
				break;

			// search
			case 's':
				// get value
				scanf("%d", &val);
				// search tree for word
				if (searchTree(val, root)) {
					printf("%d is present\n", val); 
				} else {
					printf("%d is missing\n", val);
				}
				break;

			// empty tree
			case 'e': 
				emptyTree(root);
				n = 0;
				q = 0;
				root = NULL;
				break;
				
			// print tree values
			case 't':
				do {
					scanf("%c", &cval);
				} while(isspace(cval));

				switch(cval) {
					case 'i':
						// in-order traversal
						inTraverse(root);
						printf("\n");
						break;
					case 'l':
						// pre-order traversal
						preTraverse(root);
						printf("\n");
						break;
					case 'r':
						// post-order traversal
						postTraverse(root);
						printf("\n");
						break;
					default: 
						printf("Not a legal command!\n");
				}
				break;
			
			// for testing 
			
			case 'N':
				printf("N = %d\n", n);
				break;
				
			case 'Q':
				printf("Q = %d\n", q);
				break;

			case 'r':
				printf("root is %d\n", root->value);
				break;

			case 'p':
				printTree(root, 0);
				break;
			
			// quit
			case 'q':
				printf("-quitting program-\n");
				break;
				
			default:            
				printf("Not a legal command!\n");
		}

	} while (input != 'q');
	// remove tree and free nodes
	//printf("root: %d\n", root->value);
	if (root != NULL) {
		emptyTree(root);
	}
	//free(root);
	return 0;
}
