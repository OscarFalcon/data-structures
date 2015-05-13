#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void print_array(int *arr, int length)
{
	int i;
	for(i=0;i<length;i++)
		printf("%d ",arr[i]);
	printf("\n");
	
}

/**
Merges to sorted arrays into one sorted array
int accending order
**/

int *merge(int *A, int a, int *B, int b, int *C){
	int ai,bi,ci;
	
	
	if(A == NULL || B == NULL)
	{
		fprintf(stderr,"connot have a null array as argument\n");
		return NULL;
	}
	
	ai = bi = ci = 0;
	while(ai < a && bi < b)
		C[ci++] = A[ai] < B[bi] ? A[ai++] : B[bi++];
			
	while(ai < a)
		C[ci++] = A[ai++];
	
	while(bi < b)
		C[ci++] = B[bi++];
	
	return C;
}

/**
copies n elements from src to dest
assumes that src and dest are both big 
enough and that src has initialized values
**/
void copy_array(int *src,int *dest, int n){
	int i;
	
	for(i=0;i<n;i++)
		dest[i] = src[i];
	
	return;
}

/**
sorts the given array A with length n.
**/
void merge_sort(int *A, int n){
	int n1,n2;
	int *a1,*a2;
	
	//base case for recursion 
	if(n == 1)
	{
		return;
	}
	
	n1 = n/2;  //right half of array
	n2 = n - n1; //left half of array
	
	a1 = malloc(sizeof(int)*n1);
	a2 = malloc(sizeof(int)*n2);
	
	if( !a1 || !a2)
	{
		perror("malloc error");
		return;
	}
	
 	copy_array(A,a1,n1);
	copy_array(A+n1,a2,n2);
	
	merge_sort(a1,n1);
	merge_sort(a2,n2);
	
	merge(a1,n1,a2,n2,A);
	
	free(a1);
	free(a2);
}


int main(void)
{
	int i;
	int arr[100];
	
	srand(time(NULL));
	for(i=0;i<100;i++)
	{
		arr[i] = rand()%1000;
		
	}	
	printf("arr:\n");
	print_array(arr,100);
	merge_sort(arr,100);
	printf("sorted:\n");
	print_array(arr,100);
	
	return 0;
}


