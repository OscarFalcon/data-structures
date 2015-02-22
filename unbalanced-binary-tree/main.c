

#include <stdlib.h>
#include <stdio.h>
#include "time.h"

#include "btree.h"



int main(void){
	int i;
	int num;
	int arr[10];
	node *tree = NULL;
	node *result;
	node *n;
	
	srand(time(NULL));
	for(i=0;i<10;i++){
		num = rand()%100;
		arr[i] = num;
		insert_tree(num, &tree);
		printf("%d ",num);
	}
	printf("\n");
	print_tree(tree,0);
	
	printf("Enter search number...\n");
	fscanf(stdin,"%d",&num);
	
	if((result = search_tree(num,tree)) == NULL){
		printf("%d not found\n",num);
		return 0;
	}
	printf("found %d\n",num);
	n = successor(result->data,tree);
	if(n)
		printf("successor = %d\n",n->data);
	else
		printf("no immidiate successor\n");
	
	n = predecessor(result->data,tree);
	if(n)
		printf("predecessor = %d\n",n->data);
	else
		printf("no immidiate predecessor\n");
	
	printf("deleting %d\n",result->data);
	delete_tree(result->data,&tree);
	print_tree(tree,0);
	
	
	
	
	free_tree(tree);	
	
	
}


