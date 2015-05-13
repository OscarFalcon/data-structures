#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fifo.h"


fifo_t *init_fifo(unsigned int initsz)
{
	fifo_t *f;
	
	f = (fifo_t *)malloc(((size_t)FIFOSZ(initsz)));
	if(f == NULL)
	{
		perror("unable to maloc\n");
		return NULL;
	}
	f->head = 0;
	f->tail = -1;
	f->size = 0;
	f->max_size = initsz;
	return f;
}

void print_fifo(fifo_t *fifo,void (*print)(void *data))
{
	int i;
	
	if(fifo == NULL)
	{
		fprintf(stderr,"null fifo\n");
		return;
	}
	
	if(fifo->size == 0)
	{
		printf("empty fifo\n");
		return;
	}
	
	if(fifo->tail >= fifo->head)						// fifo doe does not wrap around 
	{
		for(i=fifo->head; i <= fifo->tail; i++)
		{
			fprintf(stderr,"FIFO[%d] : ",i);
			print(fifo->data+i);						//fifo wraps around
		}
	}
	else
	{
		for(i=fifo->head; i < fifo->max_size ; i++)
		{
			fprintf(stderr,"FIFO[%d] : ",i);
			print(fifo->data+i);
		}
		for(i=0; i <= fifo->tail; i++)
		{	
			fprintf(stderr,"FIFO[%d] : ",i);
			print(fifo->data+i);
		}
	}
	return;
}


int insert_fifo(int data,fifo_t **fifo)
{
	fifo_t *tf;
	int oldmaxsz, size;
	
	if((*fifo)->size == (*fifo)->max_size)
	{
		size = FIFOSZ((*fifo)->max_size + INCRSZ);
		tf = realloc(*fifo,(size_t)size);
		if(tf == NULL)
		{
			perror("unable to reallocate fifo");
			return -1;
		}
		*fifo = tf;
		oldmaxsz = (*fifo)->max_size;
		(*fifo)->max_size += INCRSZ;
		
		/** if there is a wrap around, we need to move head down **/
		if((*fifo)->head)
		{
			size = (oldmaxsz - (*fifo)->head)*sizeof(void *);
			memmove((*fifo)->data+(*fifo)->head+INCRSZ,(*fifo)->data+(*fifo)->head,size);
			(*fifo)->size += INCRSZ;
		}	
	}
	//at this point in code, there is enough space to just add the element at the end of the fifo
	
	if( (*fifo)->tail == (*fifo)->max_size-1)
		(*fifo)->tail = 0;
	else
		(*fifo)->tail++;
	
	(*fifo)->data[(*fifo)->tail] = data;
	(*fifo)->size++;
	return 0;
}

int extract_fifo(int *data, fifo_t *fifo)
{
	if(fifo->size == 0)
		return -1;
	
	fifo->size--;
	*data = fifo->data[fifo->head];
	if(fifo->head == fifo->max_size-1)
		fifo->head = 0;
	else
		fifo->head++;
	return 0;
}












