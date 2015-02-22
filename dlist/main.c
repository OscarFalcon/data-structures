#include <stdio.h>
#include "dlist.h"

#define INIT_SZ 100

int main(void)
{
	dlist *list;
	
	
	if( (list = init_dlist(INIT_SZ)) == NULL){
		perror("dlist init failed");
		return 1;
	}
	printf("success\n");
	free_dlist(list);
	
	
	return 0;
}