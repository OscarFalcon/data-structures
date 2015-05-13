#include <stdio.h>
#include <stdlib.h>

#include "23tree.h"

#define TRUE 1;
#define FALSE 0; 

FILE *debug;

static int initial;
static int last;


/** opens stream for debug log **/
int init23(char *file)
{
	
	if( file == NULL)	
		debug = stderr;
	else if( (debug = fopen(file,"w")) == NULL)
	{
		perror(file);
		return -1;
	}
	return 0;	
}

/** prints n spaces **/
static void indent23(int n)
{
	int i;
	
	for(i=0;i<n;i++)
		fprintf(debug,"%s"," ");
	return;
}


/* prints tree from node on down **/
void print_tree23(node23 *node, int ht)
{
	if(node == NULL)
	{
		fprintf(debug,"null tree\n");
		return;
	}

	indent23(ht);
	
	if(node->son1 == NULL)		/** leaf node  and base case for recursion **/
	{
		fprintf(debug,"leaf: data = %d\n",node->y1);
		return;
	}
	
	if(node->son3 != NULL)		/** internal node with three children **/
	{
		fprintf(debug,"node: y1 = %d    y2 = %d\n",node->y1,node->y2);
	}
	else
	{
		fprintf(debug,"node: y1 = %d\n",node->y1);
	} 	
	
	ht++;
	print_tree23(node->son1,ht);
	print_tree23(node->son2,ht);
	if(node->son3)
		print_tree23(node->son3,ht);
	
}

/** returns the height of the tree from node on down **/
int height23(node23 *node)
{
	int ht;
	
	if(node == NULL)
	{
		return -1;
	}
	
	for(ht = 0; node->son1 != NULL; ht++)
		node = node->son1;
	
	return ht;
	
}

/** we cannot check for null **/
int min23(node23 *node)
{
	while(node->son1 != NULL)
		node = node->son1;
	return node->y1;
}

/** returns the max number in tree **/
int max23(node23 *node)
{
	while(node->son1 != NULL)
		node = (node->son3 ? node->son3 : node->son2); 
	
	return node->y1;
}


/** free the entire tree from node on down **/
void free_tree23(node23 *tree)
{
	if(tree == NULL) 		/** base case for recursion **/
		return;
	
	free_tree23(tree->son1);
	free_tree23(tree->son2);
	free_tree23(tree->son3);
	free(tree);
}


/** 
	checks to see if the tree is valid 
	in that all the leaf nodes are in order
**/
static int checkOrder23(node23 *node)
{
	if(node->son1 == NULL)		/** base case for recursion **/
	{
		if(initial)
		{
			initial = FALSE;
			last = node->y1;
			return 0;
		}
		else
		{
			if(last < node->y1)
			{
				last = node->y1;
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}

	if(checkOrder23(node->son1) == -1)
		return -1;
	if(checkOrder23(node->son2) == -1)
		return -1;
	if( (node->son3) != NULL && (checkOrder23(node->son3) == -1))
		return -1;
	
	return 0;
}


static int checkDepth23(node23 *node, int ht)
{
	if(node->son1 == NULL)
		return ht == 0 ? 0 : -1;
	
	ht--;
	
	if( checkDepth23(node->son1,ht) == -1)
		return -1;
	
	if(checkDepth23(node->son2,ht) == -1)
		return -1;
	
	if(node->son3 && (checkDepth23(node->son3,ht) == -1))
		return -1;
	
	return 0;
	
}


/**
	checkIndex will check to see if every non
	leaf nodes' indices are correct. 

	max son1 < y1 <= min son2
	max son2 < y2 <= max son3 

**/

static int checkIndex23(node23 *node)
{
	
	if(node->son1 == NULL)		
		return 0;
	
	if( (max23(node->son1) >= node->y1) || (min23(node->son2) < node->y1))
		return -1;
	
	if(node->son3)
	{
		if((max23(node->son2) >= node->y2) || (min23(node->son3) < node->y2))
			return -1;
	}
		
	if(checkIndex23(node->son1) == -1)
		return -1;
	if(checkIndex23(node->son2) == -1)
		return -1;
	if(node->son3 && checkIndex23(node->son3) == -1)
		return -1;
		
	return 0;
	
}



int valid23(node23 *node)
{
	
	if(node == NULL)
		return 0;
	
	if( (checkDepth23(node,height23(node))) == -1 )
	{
		fprintf(debug,"ERROR: Tree failed index test\n");
		return -1;
	}
	
	if(checkOrder23(node) == -1)
	{
		fprintf(debug,"ERROR: Tree failed order test\n");
		return -1;
	}
	
	initial = TRUE;
	if( checkIndex23(node) == -1)
	{
		fprintf(debug,"ERROR: Tree failed index test\n");
		return -1;
	}
	fprintf(debug,"OK\n");
	return 0;
}


node23 *search23(int x, node23 *node)
{
	if(node == NULL)
		return NULL;
	
	while(node->son1 != NULL)
	{
		if(x < node->y1)
			node = node->son1;
		else if(node->son3 == NULL || x < node->y2)
			node = node->son2;
		else
			node = node->son3;
	}
	
	return node->y1 == x ? node : NULL;
	
}


/**
	returns the parent of the leaf node
	where data x is OR should be 
**/
static node23 *search_parent23(int x, node23 *node)
{
	if(node == NULL || node->son1 == NULL)
		return NULL;
	
	while(node->son1->son1 != NULL)
	{
		if(x < node->y1)
			node = node->son1;
		else if(node->son3 == NULL || x < node->y2)
			node = node->son2;
		else
			node = node->son3;
	}
	return node;
}


/** inits a node obtained from a malloc **/
static node23 *avail23(void)
{
	node23 *node;
	
	node = (node23 *) malloc((size_t) sizeof(node23));
	if(node == NULL)
	{
		perror("unable to malloc - avail23");
		return NULL;
	}
	
	node->son1 = node->son2 = node->son3 = NULL;
	return node;
}


node23 *addson(int data, node23 *node, node23 **split, int *low)
{
	node23 *leaf;
	node23 *nodeback; 
	node23 *w; 
	int lowback;
	int child;
	
	*split = NULL;
	
	if( node->son1 == NULL )		// we hit leaf node where we want to insert 
	{
		if(node->y1 == data)
			return NULL;
		
		*split = avail23();
		if( node->y1 <= data)
		{
			(*split)->y1 = data;
			*low = data;
			return (*split);	//return leaf
		}
		else
		{
			(*split)->y1 = node->y1;
			(*split)->y2 = node->y2;
			node->y1 = data;
			*low = (*split)->y1;
			return node;
		}
	}
	
	
	if( data < node->y1)
	{
		child = 1;
		w = node->son1;
	}
	else if(node->son3 == NULL || data < node->y2)
	{
		child = 2;
		w = node->son2;
	}
	else
	{
		child = 3;
		w = node->son3;
	}
	
	leaf = addson(data,w,&nodeback,&lowback);
	
	
	
	return NULL;
}



node23 *insert23(int data, node23 **root)
{
	node23 *leaf;
	node23 *newroot;
	node23 *oldroot;
	node23 *split;
	int minback;
	
	
	if( (*root) == NULL)			/** null tree passed in, trivial case **/
	{
		(*root) = avail23();
		(*root)->y1 = data;
		return (*root);
	}
	
	if((*root)->son1 == NULL)		/** only one leaf node, trivial case  **/
	{
		
		if(data == (*root)->y1)		/** if data is already in tree, return null **/
			return NULL;
		
		leaf = avail23();				/** make leaf node **/ 
		leaf->y1 = data;
		
		newroot = avail23();
		
		if(data < (*root)->y1)			/** new leaf node is son1, old root is son2 **/
		{
			newroot->son1 = leaf;
			newroot->y1 = (*root)->y1;
			newroot->son2 = *root;
		}
		else							/** old root is son1, leaf is son2 **/
		{
			newroot->son1 = *root;
			newroot->y1 = data;
			newroot->son2 = leaf;
		}
		*root = newroot;
		return leaf;
			
	}
	// GENERAL CASE
	leaf = addson(data,*root,&split,&minback);
	if(leaf == NULL)
		return NULL;
	
	if(split != NULL)				/** we must create a new root node because there was a split one level below **/
	{
		oldroot = *root;
		*root = avail23();
		(*root)->son1 = oldroot;
		(*root)->son2 = split; //always return rightmost son in split
		(*root)->son3 = NULL;
		(*root)->y1 = minback;
	}
	return leaf;
}









