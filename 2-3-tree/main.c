#include <stdio.h>
#include <stdlib.h>
#include "23tree.h"



int main(int argc, char **argv)
{
	node23 *tree;
	int i;
	int num;
	extern FILE *debug;
	
	
	if(argc == 1)
	{
		init23(NULL);
	}
	else if(init23(argv[1]))
	{
		perror(argv[1]);
		return -1;
	}
	
	tree = NULL;
	while(scanf("%d\n",&num) == 1)
	{
		
		i++;
		if(insert23(num,&tree) == NULL)
		{
			fprintf(debug,"Item %d is already in the tree\n,",num);
			i--;
		}
		print_tree23(tree,0);
		fprintf(debug,"Checking Tree - tree size = %d value = %d\n",i,num);
		if(valid23(tree) == -1)
		{
			fprintf(debug,"invalid tree\n");
			print_tree23(tree,0);
			return -1;
		}
		
	}
	fprintf(debug,"All trees are correct!\n");
	return 0;
}