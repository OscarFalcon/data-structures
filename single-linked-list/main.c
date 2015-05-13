#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int main(void){
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
	n = search_list(l,5);
	if(n != NULL)
	{
		printf("found 5 in list\n");
	}
	else
		printf("didnt find 5 in list\n");
	
	delete_list(l,l->first->next->next);
	print_list(l);
	
	free_list(l);
	fprintf(stderr,"Success!\n");
	return 0;
	
	
}