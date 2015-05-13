#include <stdio.h>
#include <stdint.h>
#include "dlist.h"



int main(int argc, char *argv[])
{
	int i;
	double data1, *element;
	dlist_t *list;
	
	
	list = dlist_init(DEFAULT_SIZE,sizeof(double),DEFAULT_GROWTH);

	i = 0;
	
	while(scanf("%lf",&data1) == 1)
	{
		if( dlist_insert(list,&data1) == -1)
		{
			perror("Unable to insert data");
			return -1;
		}
		element = (double *) dlist_get(list,i);
		*element *= 2;
		printf("list[%d] = %lf\n",i,*element);
		i++;
	}
	
	dlist_free(list);
	printf("SUCCESS\n");
}