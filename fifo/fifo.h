



#define INCRSZ 1000
#define FIFOSZ(n) (sizeof(fifo_t))

typedef struct fifo
{
	int head;
	int tail;
	unsigned int size;
	unsigned int max_size;
	
	int *data;
} fifo_t;


fifo_t *init_fifo(unsigned int initsz);
int insert_fifo(int data,fifo_t **fifo);
int extract_fifo(int *data, fifo_t *fifo);
void print_fifo(fifo_t *fifo,void (*print)(void *data));

