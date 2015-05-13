#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void print_array(int *arr, int length)
{
	int i;
	for(i=0;i<length;i++)
		printf("%d ",arr[i]);
	printf("\n");
	
}

/**
This method will pick a pivot and
partition the array around that 
pivot. Returns the pivot.

params: A - an int array 
	    l - the begining of the array
        r - the ending of the array
**/
int partition(int *A,int l, int r)
{
	int head,tail,pivot;
	int tmp;
	
	
	if(A == NULL)
	{
		fprintf(stderr,"array is null");
		return -1;
	}

	head = l;
	tail = r;
	pivot = A[l];
	
	while(1)
	{
		while(head < tail && A[head] <= pivot) head++;
		while(tail >= head && A[tail] > pivot) tail--;
		
		if(head >= tail) break;
		
		tmp = A[head];
		A[head] = A[tail];
		A[tail] = tmp;
	}
	tmp = A[l];
	A[l] = A[tail];
	A[tail] = tmp;
	return tail;
}
	
void quicksort(int *A, int l, int r)
{
	int pivot;

	if( l >= r)
		return;
	
	pivot = partition(A,l,r);
	quicksort(A,l,pivot-1);
	quicksort(A,pivot+1,r);
	
}	


int main(void)
{
	int i;
	int arr[10];
	
	srand(time(NULL));
	for(i=0;i<10;i++)
	{
		arr[i] = rand()%100;
		
	}	
	printf("arr:\n");
	print_array(arr,10);
	quicksort(arr,0,9);
	printf("sorted:\n");
	print_array(arr,10);
	
	return 0;
}