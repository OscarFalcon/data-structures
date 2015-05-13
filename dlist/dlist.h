#include <stdint.h>



#define DEFAULT_GROWTH  2
#define DEFAULT_SIZE 1024


typedef struct dlist
{
	 unsigned int length; 			//current size of the list
	 unsigned int capacity; 		//total space available in array
	 size_t element_size;			//size of an idividual element in the array
	 unsigned int growth_factor;	//multiplicative factor of growth when capacity is full
	 uint8_t *data; 				//data array
} dlist_t;

dlist_t *dlist_init(unsigned int length, size_t element_size, unsigned int growth_factor);
void dlist_free(dlist_t *list);
int dlist_insert(dlist_t *list,void *data);
void *dlist_get(dlist_t *list, unsigned int index);
void dlist_set(dlist_t *list, unsigned int index, void *value);