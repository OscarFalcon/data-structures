

typedef struct node{
	int data;
	struct node *left;
	struct node *right;
} node;


void print_tree(node *tree,int height);
void free_tree(node *tree);

node *insert_tree(int data, node **tree);

node *search_tree(int data, node *tree);
node *successor(int data, node *tree);
node *predecessor(int data, node *tree);

void delete_tree(int data, node **tree);
int *height(node *tree);
