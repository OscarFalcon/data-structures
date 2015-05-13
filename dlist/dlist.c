#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "dlist.h"


dlist_t *dlist_init(unsigned int init_capacity, size_t element_size, unsigned int growth_factor)
{
	dlist_t *list;
	
	if(init_capacity == 0 || element_size == 0 || growth_factor == 0)
	{
		errno = EINVAL;
		return NULL;
	}
	
	if((list = (dlist_t *) malloc(sizeof(dlist_t))) == NULL)
	{
		errno = ENOMEM;
		return NULL;
	} 
		
	if((list->data = malloc(init_capacity * element_size)) == NULL)
	{
		free(list);
		errno = ENOMEM;
		return NULL;
	}
	
	list->length = 0;
	list->capacity = init_capacity;
	list->element_size = element_size;
	list->growth_factor = growth_factor;
	return list;
}


void dlist_free(dlist_t *list)
{
	free(list->data);
	free(list);
	return;
}


int dlist_insert(dlist_t *list, void *value)
{
	uint8_t *new_data;
	
	if(list == NULL || value == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	if(list->length == list->capacity)
	{
		size_t size = (list->length * list->growth_factor) * list->element_size;
		if((new_data = malloc(size)) == NULL)
		{
			errno = ENOMEM;
			return -1;
		}
		
		memcpy(new_data,list->data,list->length * list->element_size);
		free(list->data);
		list->data = new_data;
		list->capacity = list->length * list->growth_factor;
	}	
	
	memcpy( list->data + (list->length * list->element_size), value, list->element_size);
	list->length++;
	return 0;
}

void *dlist_get(dlist_t *list, unsigned int index)
{
	if(list == NULL || index >= list->length)
	{
		errno = EINVAL;
		return NULL;
	}
	
	return (void *) (list->data + index * list->element_size);
}

void dlist_set(dlist_t *list, unsigned int index, void *value)
{
	if(list == NULL || index >= list->length)
	{
		errno = EINVAL;
		return;
	}
	
	memcpy(list->data + (index * list->element_size),value,list->element_size);
	return;
}

















