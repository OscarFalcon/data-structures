#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avl.h"


int cmp(void *x, void *y)
{
	return  *((int *) x) - *((int *)y); 
	
}

void print_node(avl_node *node)
{
	fprintf(stderr,"node->height = %d, node->data = %d\n",node->height,(*(int *)(node->data)));
}


int main(void)
{
	int array[100];
	int num;
	int i;
	avl_tree *tree;
	
	
	FILE *insert_file;
	FILE *delete_file;
	
	insert_file = fopen("insert.data","r");
	delete_file = fopen("delete.data","r");
	
	if(insert_file == NULL || delete_file == NULL)
	{
		fprintf(stderr,"insert.data or delete.data\n");
		return -1;
	}
	
	
	tree = init_tree(cmp,print_node);
	
	i = 0;
	while(fscanf(insert_file,"%d",&num) == 1)
	{
		fprintf(stderr,"inserting..%d\n",num);
		array[i] = num;
		insert_tree(tree,array+i);
		i++	;
	}
	fprintf(stdout,"height is... %d\n",tree->root->height);
	fprintf(stdout,"max width is... %d\n",max_width(tree));
	
	
	
	fprintf(stderr,"pick number to delete\n");
	while(fscanf(delete_file,"%d",&num) == 1)
	{
		fprintf(stderr,"deleting...%d\n",num);
		delete_tree(tree,&num);
	}
	
	
	/**srand(time(NULL));
	for(i=0;i<10;i++)
	{
		array[i] = rand()%100;
		insert_tree(tree,array+i);
		if(check_tree(tree) == -1 )
		{
			fprintf(stderr,"WRONG TREE\n");
		}
	}**/
	
	
	print_tree(tree);
	free_tree(tree);
	return 0;
}