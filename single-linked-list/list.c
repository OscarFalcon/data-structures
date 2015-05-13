#include <stdlib.h>
#include <stdio.h>
#include "list.h"



list *init_list(){
	list *l; 
	
	if( (l = malloc(sizeof(list))) == NULL)
	{
		fprintf(stderr,"unable to malloc memory\n");
		return NULL;
	}
	
	l->first = NULL;
	fprintf(stderr,"Succesfully initialized list\n");
	return l;
}

static node *init_node(int data){ //mallocs initializes a node 
	node *n;
	int i = 0;
	
	if( (n = malloc(sizeof(node))) == NULL)
	{
		fprintf(stderr,"unable to malloc node\n");
		return NULL;
	}
	n->data = data;
	n->next = NULL;
	return n;
}

void free_list(list *l){
	node *nextToDelete;
	node *delete;

	if(l == NULL)
	{
		fprintf(stderr,"Empty list\n");
		return;
	}
	
	delete = l->first;
	while(delete)
	{
		fprintf(stderr,"freeing...%d\n",delete->data);
		nextToDelete = delete->next;
		free(delete);
		delete = nextToDelete;
	}
	free(l);
	
	
	/**delete = l->first;
	if(delete == NULL)
	{
		free(l);
		return;
	}
**/

	

	/**
	while(delete->next != NULL)
	{
		nextToDelete = delete->next;
		free(delete);
		delete = nextToDelete;
	}**/
	//free(delete);
	//free(l);
	return;

}

void print_list(list *l){
	node *n;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list\n");
		return;
	}
	
	n = l->first;
	if(n == NULL)
	{
		fprintf(stderr,"Empty list\n");
		return;
	}
	
	while(n->next != NULL)
	{
		printf("%d ",n->data);
		n = n->next;
	}
	printf("%d\n",n->data);
	return;
}


node *insert_list(list *l, int data){ //inserts in accending order data into the list
	node *n;
	node *traverse;
	node *previous;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list\n");
		return NULL;
	}
	
	if( (n = init_node(data)) == NULL) //init the node we are going to insert
	{
		return NULL;
	}
	
	traverse = l->first;
	previous = NULL;
	while(traverse != NULL && traverse->data < data )
	{
		previous = traverse;
		traverse = traverse->next;
	}
	//after traverse will be the node after where n should be
	if(previous) 
		previous->next = n;
	else
		l->first = n;
	
	n->next = traverse;
	
	fprintf(stderr,"Inserted %d\n",data);
	return n;
}

node *search_list(list *l, int data){ //searches the list for a node containing the value 'data'
	node *n;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list");
		return NULL;
	}
	n = l->first;
	while(n != NULL && n->data < data)
		n = n->next;

	if( n == NULL || n->data != data)
		return NULL;
	return n;
}

void delete_list(list *l, node *n){ //deletes node n from the list
	node **traverse;
	node *t;

	if(l == NULL)
	{
		fprintf(stderr,"null list");
		return;
	}
	
	if(l->first == NULL)
	{
		fprintf(stderr,"empty list");
		return;
	}
	
	if(n == NULL)
	{
		fprintf(stderr,"null node as argument");
		return;
	}
	
	
	traverse = &(l->first);
	while( *traverse != NULL && *traverse != n)
		traverse = &((*traverse)->next);
	
	
	if(*traverse != NULL)
	{
		t = *traverse;
		*traverse = t->next;
		free(t);
	}
	
	return;
}


