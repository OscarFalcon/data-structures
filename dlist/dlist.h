


typedef struct
 {
	 unsigned int size; //current size of the list
	 unsigned int capacity; //total space available in data array
	 int *data; //data array
	
} dlist;

dlist *init_dlist(unsigned int size); //initializes a dlist of intial capacity of "size"
int insert_dlist(dlist *list, unsigned int index, int value); //returns 0 on success, 1 otherwise
int append_dlist(dlist *list, int value); //same as calling insert_dlist with index corresponding to next potential free slot
void delete_dlist(dlist *list, unsigned int index); //deletes value at given position, shifts array accordingly
void free_dlist(dlist *list); //frees the data in the dlist, does not free actual structure

static int double_dlist(dlist *list); //doubles the capacity of the given dlist




