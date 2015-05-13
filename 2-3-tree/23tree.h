
typedef struct node23{
	int y1;
	int y2;
	struct node23 *son1;
	struct node23 *son2;
	struct node23 *son3;
} node23;


int init23(char *file);
void print_tree23(node23 *node,int ht);
int height23(node23 *node);
int min23(node23 *node);
int max23(node23 *node);
void free_tree23(node23 *tree);
node23 *insert23(int data, node23 **tree);
int valid23(node23 *tree);
node23 *search23(int x, node23 *root);
