typedef struct node{
	int data;
	struct node *next;
	struct node *prev;
} node;

typedef struct list{
	node *head;
	node *tail;
} list;



list *init_list(); //initializes an empty single linked list
node *insert_list(list *l, int data); //inserts in accending order data into the list, returns inserted node
node *search_list(list *l, int data); //searches the list for a node containing the value 'data'
void delete_list(list *l, node *n); //deletes node n from the list
void print_list(list *l); //prints every value of every node in the list
void free_list(list *l); //frees all the nodes in the list, as well as the list struct
