
#include <stdio.h>
#include <stdlib.h>
#include "list.h"


list *init_list(){
	list *l;
	node *head;
	node *tail;
	

	l = ((list *) malloc(sizeof(list)));
	if(l == NULL)
	{
		perror("Unable to malloc");
		return NULL;
	} 
	
	if((head = malloc(sizeof(node))) == NULL)
	{
		perror("unable to malloc");
		free(l);
		return NULL;
	}
	if((tail = malloc (sizeof(node))) == NULL) 
	{
		perror("unable to malloc");
		free(head);
		free(l);
		return NULL;
	}
	l->head = head;
	l->tail = tail;
	
	l->head->prev = NULL;
	l->head->next = tail;
	
	l->tail->prev = head;
	l->tail->next = NULL;
	
	return l;
}

void free_list(list *l)
{
	node *n;
	node *next;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list");
	}
	
	n = l->head;
	while(n)
	{
		next = n->next;
		free(n);
		n = next;
	}
	free(l);
}



void print_list(list *l)
{
	node *n;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list");
		return;
	}
	
	if(l->head->next == NULL)
	{
		fprintf(stderr,"empty list");
		return;
	}
	
	n = l->head->next;
	while(n->next != NULL)
	{
		printf("%d ",n->data);
		n = n->next;
	} 
	printf("\n");
	
}

static node *init_node(int data){
	node *n;
	
	n = (node *) malloc(sizeof(node));
	if(n == NULL)
	{
		perror("unable to malloc");
		return NULL;
	}
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	return n;	
}

node *insert_list(list *l, int data){
	node *n;
	node *current;
	
	if(l == NULL )
	{
		fprintf(stderr,"null list");
		return NULL;
	}
	
	if( (n = init_node(data)) == NULL)
	{
		return NULL;
	}
	
	current = l->head->next;
	while(current->next != NULL && current->data < data) //while the current node is NOT the tail 
		current = current->next;
	
	n->next = current;
	n->prev = current->prev;
	
	current->prev->next = n;
	current->prev = n;
	
	return n;
}

node *search_list(list *l,int data)
{
	node *traverse;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list\n");
		return NULL;
	}
	
	traverse = l->head->next;
	while(traverse->next != NULL && traverse->data < data)
		traverse = traverse->next;
	
	if(traverse->next == NULL || traverse->data != data)
		return NULL;
	
	return traverse;
}

void delete_list(list *l, node *n){
	node *t;
	
	if(l == NULL)
	{
		fprintf(stderr,"null list");
		return;
	}
	
	t = l->head->next;
	while(t->next != NULL && t != n)
		t = t->next;
	
	if(t->next == NULL)
		return;
	
	t->prev->next = t->next;
	t->next->prev = t->prev;
	free(t);
	return;
}




