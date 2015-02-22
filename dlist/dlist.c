

#include <stdlib.h>
#include <stdio.h>
#include "dlist.h"



dlist *init_dlist(unsigned int size){
	dlist *list;
	
	if(size == 0){
		perror("Size must be greater than 0");
		return NULL;
	}
	
	
	if( (list = (dlist *) malloc(sizeof(dlist))) == NULL ){
		perror("Unable to malloc memory");
		return NULL;
	} 
	
	if((list->data = malloc(sizeof(int) * size)) == NULL){
		perror("unable to malloc memory");
		free(list);
		return NULL;
	}
	
	list->size = 0;
	list->capacity = size;
	
	double_dlist(list);
	return list;
	
	
}


void free_dlist(dlist *list){
	free(list->data);
	list->size = 0;
	list->capacity = 0;
}


static int double_dlist(dlist *list){
	unsigned int newsize; 
	unsigned int oldsize;
	int i;
	int *new_data;
	
	if(list == NULL){
		perror("NULL list");
		return 1;
	}
	
	if(list->capacity == 0){
		perror("list capacity is 0, defaulting new size to 1");
		newsize = 1;
	}
	else{
		newsize = list->capacity * 2;
	}	
	
	new_data = (int *) malloc(sizeof(int) * newsize);
	if(new_data == NULL){
		perror("unable to malloc memory");
		return 1;
	}
	
	oldsize = list->size;
	for(i = 0; i < oldsize; i++){
		new_data[i] = list->data[i];
	}
	
	free(list->data);
	list->data = new_data;
	list->capacity = newsize;
	
	printf("succesfully doubled list\n");
	return 0;
}	


int insert_dlist(dlist *list, unsigned int index, int value){
	int size;
	int diff;
	
	if(list == NULL){
		perror("null list");
		return 1;
	}
	
	if(index < capacity ){ 				//trival case first
		list->data[index] = value;
		return 0;
	}
	
	diff = (index+1) - capacity; 
	
	
	
	
	
}
















