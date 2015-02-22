

typedef struct avl_node
{
	void *data;					//pointer to arbitrary data
	struct avl_node *left;		//left pointer
	struct avl_node *right;		//right pointer
	int height;					//height of leaf nodes are 0;
} avl_node;


typedef struct avl_tree
{
	int (*cmp_function)(void *,void *); 	//pointer to a function that will compare two avl_nodes
	void (*print_node)(avl_node *);			//pointer to function that will print a given avl node	
	struct avl_node *root;					// pointer to the root of the avl tree
	
} avl_tree;


avl_tree *init_tree( int (*cmp_function)(void *,void *), void (*print_node)(avl_node *)); 	//inits the avl tree
void print_tree(avl_tree *tree);							//prints the avl tree 
void free_tree(avl_tree *tree);								//frees the entire avl_tree 
int check_tree(avl_tree *tree);								//checks to see if the avl_tree is correct
int max_width(avl_tree *tree);
avl_node *insert_tree(avl_tree *tree,void *data);  			//inserts data into the tree 
avl_node *search_tree(avl_tree *tree, void *data);

void delete_tree(avl_tree *tree, void *data);

