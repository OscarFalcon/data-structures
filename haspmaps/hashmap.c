#include "hashmap.h"


static dict_t *init_dictionary(unsigned int size)
{
	dict_t *d;
	int i;
	
	d = (dict_t *d) malloc(sizeof(dict_t));
	assert(d);
	
	d->size = size;
	d->n = 0;
	
	d->table = malloc((size_t)sizeof(dict_t *) * size);
	assert(d->table);
	
	for(i = 0; i < d->size; i++)
		d->table[i] = NULL;

	return d;
}



dict_t *create_dictionary(void)
{
	return init_dictionary(INITIAL_SIZE);
}

void free_dictionary(dict_t *d)
{
	int i;
	element_t *e;
	element_t *next;
	
	for(i = 0; i < d->size; i++)
	{
		for(e = d->table[i]; e != NULL; e = next)
		{
			next = e->next;
			free(e->key);
			free(e->value);
			free(e);
		}
	}
	free(d->table);
	free(d);	
}


static unsigned long hash_function(char *s)
{
	unsigned const char *us;
	unsigned long h;
	
	h = 0;
	for(us = (unsigned const char *)s; *us; us++)
	{
		h = h * PRIME + us;
	}
	return h;
}



void insert_dictionary(dict_t *d,const char *key, const char *value)
{
	element_t *e;
	unsigned long h;
	
	assert(key);
	assert(value);
	
	e = malloc(sizeof(element_t));
	assert(e);
	
	e->key = strdup(key);
	e->value = strdup(value);
	
	h = hash_function(key) % d->size;
	e->next = d->table[h];
	d->table[h] = e;
	d->n++;
}
