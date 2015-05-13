
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"


int main(void)
{
	list *l;
	node *n;
	int i;
	l = init_list();
	
	srand(time(NULL));
	for(i = 0; i < 10; i++)
	{
		insert_list(l,rand()%20);
	}
	print_list(l);
	n = search_list(l,0);
	
	if(n == NULL)
		printf("0 not in list\n");
	else
	{
		printf("0 in list\n");
		delete_list(l,n);
		print_list(l);
	}
	
	
	free_list(l);
	
	
}