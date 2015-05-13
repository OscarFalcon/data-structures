

typedef struct element
{
	struct element *next;
	char *key;
	char *value;
} element_t;


typedef struct dictionary
{
	int size;
	int n;
	struct element **table;
} dict_t;

#define INITIAL_SIZE 1024
#define GROWTH_FACTOR 2
#define MAX_LOAD_FACTOR 1
#define PRIME 37

dict_t *create_dictionary(void);
void free_dictionary(dict_t *d);
