#include <stdlib.h>
#include <stdio.h>
#include "btree.h"
	
	
void print_tree(node *node, int height){
	
	if( node == NULL)
		return;
	
	printf("height = %d value = %d\n",height,node->data);
	print_tree(node->left,height+1);
	print_tree(node->right,height+1);
	return;
}

static void prt_tree(node *tree){
	
	if(tree == NULL)
	{
		fprintf(stderr,"null tree\n");
		return;
	}
	
	print_tree(tree,0);
}


void free_tree(node *tree){
	
	if(tree == NULL)
		return;
	
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);	
	return;
}


node *search_tree(int data, node *tree){
	
	if(tree == NULL)
	{
		fprintf(stderr,"null tree");
		return NULL;
	}
	
	while(tree != NULL && tree->data != data)
	{
		if(tree->data < data)
			tree = tree->right;
		else
			tree = tree->left;
	}
	
	return tree;
}

node *insert_tree(int data, node **tree){
	node **p,*q;
	
	p = tree;
	
	while( *p != NULL )
	{
		if( (*p)->data == data )
			return *p;
		else if( (*p)->data < data )
			p = &((*p)->right);
		else
			p = &((*p)->left);
	}
	
	q = malloc(sizeof(node));
	if(q == NULL)
		return NULL;
	
	*p = q;
	q->data = data;
	q->right = NULL;
	q->left = NULL;
	return q;
}


/**
Finds the immediate successor to the 
node with data = data;

returns NULL if no successor is found
**/
node *successor(int data, node *tree){
	node *n;
	node *successor;
	
	n = search_tree(data,tree);
	if(n == NULL)
		return NULL;
	
	successor = n->right;
	if(successor == NULL )
		return NULL;
	
	while(successor->left != NULL)
		successor = successor->left;
	
	return successor; 
	
}

/**
returns the immediate predecessor of a node
with data value = data
NULL if none found 
**/
node *predecessor(int data, node *tree){
	node *n;
	node * predecessor;
	
	n = search_tree(data,tree);
	if(n == NULL)
		return NULL;
	
	predecessor = n->left;
	if(predecessor == NULL)
		return NULL;
	
	while(predecessor->right != NULL)
		predecessor = predecessor->right;
	
	return predecessor;
}



/**
	Deletes the node n, and updates the poiter to n
    and changes the pointer to n to point to either 
    the right or left child of n or the immediate 
	successor of n, whichever is apppropriate
**/

static void delete_node(node **n){
	node *delete;
	node **successor;
	node *t;
	
	delete = *n;										//pointer to the node we want to delete
	
	if(delete->right == NULL && delete->left == NULL) 	// LEAF NODE
	{	
		*n = NULL;
	}
	else if(delete->left == NULL)						//ONLY HAS RIGHT CHILD			
	{						
		*n = delete->right;
	}
	else if(delete->right == NULL)						//ONLY HAS LEFT CHILD 
	{
		*n = delete->left;
	}
	else												// TWO CHILDREN
	{
		
		successor = &(delete->right);
		while( (*successor)->left != NULL)				//get the pointer to the pointer to the successor node 
			successor = &((*successor)->left);
		
		t = *successor;		
		*successor = t->right;							//route around successor node 
		t->right = delete->right;
		t->left = delete->left;
		*n = t;	
	}
	free(delete);
}




void delete_tree(int data, node **tree){
	node **n;
	
	if(tree == NULL)
		return;

	n = tree;
	while( *n != NULL && (*n)->data != data)
	{
		if((*n)->data < data)
			n = &((*n)->right);
		else
			n = &((*n)->left);
	}	
	
	if( *n == NULL)
		return;
	
	delete_node(n);
}






	
	
	


















