#include <stdio.h>
#include <string.h>

#include "fifo.h"



void print(void *data)
{
	int *num;
	num = (int *) data;
	fprintf(stderr,"%d\n",*num);
}


int main(void)
{
	char buff[1024];
	int i,num;
	int *varray[1024];
	int array[1024];
	fifo_t *fifo;
	
	
	fifo = init_fifo(1000);
	if(fifo == NULL )
		return -1;
	
	
	i = 0;
	while(scanf("%s %d\n",buff,array+i) == 2 )
	{
		varray[i] = array+i;
		printf("varray[%d] : %d\n",i, *varray[i] );
		printf("%s : %d\n",buff,array[i]);
		
		if(strcmp(buff,"insert") == 0 )
		{
			printf("inserting .. %d\n",array[i]);
			insert_fifo(array[i],&fifo);
		}
		else if(strcmp(buff,"delete") == 0)
		{
			printf("DELETE\n");
		}
		i++;	
	}
	print_fifo(fifo,print);
	
	
	
	
	return 0;
}