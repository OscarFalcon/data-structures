#include <stdio.h>
#include <stdlib.h>

#include "avl.h"


avl_tree *init_tree(int(*cmp_function)(void *,void *), void (*print_node)(avl_node *))
{
	avl_tree *tree;
		
	if(cmp_function == NULL || *print_node == NULL)
	{
		fprintf(stderr,"cannot have pointer to function null\n");
		return NULL;
	}
	
	tree = malloc((size_t)sizeof(avl_tree));
	if(tree == NULL)
	{
		perror("unable to malloc");
		return NULL;
	}
	
	tree->cmp_function = cmp_function;
	tree->print_node = print_node;
	tree->root = NULL;
	
	return tree;
} 

static avl_node *init_node(void *data)
{
	avl_node *n;
		
	n = malloc((size_t)sizeof(avl_node));
	if(n == NULL)
	{
		perror("unable to malloc node");
		return NULL;
	}
	
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	n->height = 0;		//initially, it's a leaf node
	return n;
}


static void free_node(avl_node *n)
{
	if(n == NULL)
		return;
	
	free_node(n->left);
	free_node(n->right);
	free(n);
}

void free_tree(avl_tree *tree)
{
	free_node(tree->root);
	free(tree);
}

static void prt_tree(void (*print_node)(avl_node *), avl_node *n,int h)
{	
	if(n == NULL)
		return;
	
	(*print_node)(n);
	prt_tree(print_node,n->left,h+1);
	prt_tree(print_node,n->right,h+1);
}

/** prints the tree in preorder traversal **/
void print_tree(avl_tree *tree)
{	
	if(tree == NULL || tree->root == NULL)
	{
		fprintf(stderr,"avl tree or root is null\n");
		return;
	}
	prt_tree(tree->print_node,tree->root,0);
	return;
}

static int max(int a, int b)
{
	return a > b ? a : b;
}

/** returns the width for a tree at height = level **/
int get_width(avl_node *n,int level)
{
	if(n == NULL)
		return 0;
	
	if(level == 0)
		return 1;
	
	return get_width(n->left,level-1) + get_width(n->right,level-1);
}


/** returns the max width of the subtree **/
int max_width(avl_tree *tree)
{
	int i,height,max,w;
	
	if(tree == NULL || tree->root == NULL)
		return -1;
	
	height = tree->root->height;
	max = 0;
	for(i=0; i <= height; i++)
	{
		w = get_width(tree->root,i);
		max = w > max ? w : max;
	}
	return max;
	
}

static int check_node(avl_node *n)
{
	if(n == NULL)
		return -1;
	
	n->height = max(check_node(n->left),check_node(n->right)) + 1; 
	
	int a, b;
	a = (!n->left ? -1 : n->left->height);
	b = (!n->right? -1 : n->right->height);
	
	if(abs(a-b) > 1)
		return -1;
	
	return 0;
}

int check_tree(avl_tree *tree)
{
	return (tree == NULL || tree->root == NULL) ? 0 : check_node(tree->root);
}

/** returns the height of the given node, assuming 
	 both left and right subtrees have the correct 
	 height in their nodes 
**/
static int height(avl_node *node)
{
	avl_node *left;
	avl_node *right;
	
	left = node->left;
	right = node->right;
	
	if(!left && !right)
		return 0;
	
	if(!left)
		return right->height + 1;
	
	if(!right)
		return left->height + 1;
	
	return left->height > right->height ? left->height+1 : right->height+1;
}


/** 
	right rotate around node,
	will change the new root
**/
static void rotate_right(avl_node **node)
{
	avl_node *z, *y, *t;
	
	z = *node;
	y = z->left;
	
	t = y->right;
	y->right = z;
	z->left = t;
	
	fprintf(stderr,"old zh: %d - new zh %d\n",z->height,height(z));
	z->height = height(z);
	y->height = height(y);
	
	*node = y;
	return;
}

static void rotate_left(avl_node **node)
{
	avl_node *z,*y,*t;
	
	z = *node;
	y = z->right;
	
	t = y->left;
	y->left = z;
	z->right = t;
	
	
	/** after the rotation, both of z's children still have correct heights, 
		so if we call height(z) we can get the updated height for 
	**/
	fprintf(stderr,"old zh: %d - new zh %d\n",z->height,height(z));
	z->height = height(z);
	/** now since y's left child is now z (and z's height is correct), 
		and y's left child was never changed, we can update the height 
		for y
	**/
	y->height = height(y);
	
	
	*node = y;
	return;
}
/**
	returns: the balance factor of left compared to right
			 ie if negative, left is smaller than right.
			
**/
static int balance_factor(avl_node *n)
{
	int a;
	
	a = (n->left ? n->left->height : -1 ) - (n->right ? n->right->height : -1 );	
	fprintf(stderr,"balance factor for node %d : %d\n", (*(int *)n->data),a);
	return (n->left ? n->left->height : -1 ) - (n->right ? n->right->height : -1 );
}

static avl_node *insert_node(avl_node *node, void *data, int (*cmp)(void *, void *))
{
	int result;
	
	if(node == NULL)										/** case case for recursion **/
	{
		return init_node(data);
	}
	
	result = cmp((node)->data,data);						/** compare to go left or right **/
	if(result == 0)											/** base case, we already found data in tree, return node **/
		return node;				
	
	if(result < 0 )											/** go left **/
		node->right = insert_node(node->right,data,cmp);
	else
		node->left = insert_node(node->left,data,cmp);		/** fo right **/
	
												
	node->height = height(node);							/** recalculate heights of all the nodes traversed **/	
															 
	result = balance_factor(node);							/** identify what case the tree unbalance is **/
	if(result < -1)
	{
		if(cmp(data,node->right->data) > 0 )
		{
			fprintf(stderr,"right - right case\n");
			rotate_left(&node);
		}
		else
		{
			fprintf(stderr,"right - left case\n");
			rotate_right(&(node->right));
			rotate_left(&node);
		}
	}
	else if(result > 1)
	{
		if(cmp(data,node->left->data) < 0 )
		{
			fprintf(stderr,"left - left case\n");
			rotate_right(&node);
		}
		else
		{
			fprintf(stderr,"left - right case\n");
			rotate_left(&(node->left));
			rotate_right(&node);
		}
	}
	else
	{
		fprintf(stderr,"tree is balanced...\n");
	}
		
	return node;
}

avl_node *insert_tree(avl_tree *tree,void *data)
{
	if(tree == NULL)
	{
		fprintf(stderr,"null tree\n");
		return NULL;
	}
	
	tree->root = insert_node(tree->root,data,tree->cmp_function);
	return tree->root;
}

avl_node *search_tree(avl_tree *tree, void *data)
{
	avl_node *n;
	int (*cmp)(void *,void *);
	
	
	if(tree == NULL || tree->root == NULL || tree->cmp_function == NULL)
		return NULL;
	
	cmp = tree->cmp_function;
	while(n != NULL && cmp(n->data,data) != 0)
	{
		if((cmp(n->data,data) < 0 ))
			n = n->right;
		else
			n = n->left;
	}
	
	return n;
	
}


void delete(avl_node **n)
{
	avl_node **successor;
	avl_node *delete;
	avl_node *t;
	
	fprintf(stderr,"delete\n");
	
	delete = *n;
	
	if(delete->right == NULL && delete->left == NULL)
	{
		fprintf(stderr,"no children\n");
		*n = NULL;
	}
	else if(delete->left == NULL)						//ONLY HAS RIGHT CHILD			
	{						
		fprintf(stderr,"right child\n");
		*n = delete->right;
	}
	else if(delete->right == NULL)						//ONLY HAS LEFT CHILD 
	{
		fprintf(stderr,"left child\n");
		*n = delete->left;
	}
	else
	{
		fprintf(stderr,"two children\n");
		successor = &(delete->right);
		while((*successor)->left != NULL)
			successor = &((*successor)->left);
		
		
		fprintf(stderr,"new is ...%d\n",(*(int *)(*successor)->data));
		
		t = *successor;
		*successor = t->right;
		t->right = delete->right;
		t->left = delete->left;
		*n = t;
	}
	
	free(delete);
}


void delete_node(avl_node **node, void *data, int (*cmp)(void *,void *))
{
	if(node == NULL)
		return;
	
	
	
	fprintf(stderr,"in...%d\n",(*(int *)(*node)->data));
	
	if(cmp((*node)->data,data) < 0)
		delete_node(&((*node)->right),data,cmp);
	else if(cmp((*node)->data,data) > 0)
		delete_node( &((*node)->left),data,cmp);
	//found the node we want to delete
	else
	{
		fprintf(stderr,"found it\n");
		delete(node);
	}
	
	
	
	
	if(*node == NULL)
	{
		fprintf(stderr,"trivially balanced\n");
		return;
	}
	fprintf(stderr,"balancing... new value is...%d\n",(*(int *)(*node)->data));
	int result = balance_factor(*node);	
	if(result < -1)
	{
		if(cmp(data,(*node)->right->data) > 0 )
		{
			fprintf(stderr,"right - right case\n");
			rotate_left(node);
		}
		else
		{
			fprintf(stderr,"right - left case\n");
			rotate_right(&((*node)->right));
			rotate_left(node);
		}
	}
	else if(result > 1)
	{
		if(cmp(data,(*node)->left->data) < 0 )
		{
			fprintf(stderr,"left - left case\n");
			rotate_right(node);
		}
		else
		{
			fprintf(stderr,"left - right case\n");
			rotate_left(&((*node)->left));
			rotate_right(node);
		}
	}
	else
	{
		fprintf(stderr,"tree is balanced...\n");
	}
	
}


void delete_tree(avl_tree *tree, void *data)
{
	
	
	if(tree == NULL || tree->root == NULL || tree->cmp_function == NULL)
		return;
	
	delete_node(&(tree->root),data,tree->cmp_function);
	return;
	
	
}
