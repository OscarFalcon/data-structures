
#define ALPHABET_SIZE  26
#define TRUE 1
#define FALSE 2

typedef struct node{
	int data;								// this later can be a pointer to say a definition in a dictionary
	char character;							// the curent character, may not be needed
	int isWord; 							// TRUE if the chain of letters up to this vertex constitute a word 
	unsigned int prefixes; 					// total number of words that have a prefix character sequence up to this node (words can also be prefixes)  
	struct node *children[ALPHABET_SIZE]; 	//array of pointers to nodes for each letter's children
} node;

int insert_word(node **trie, char *word, int data); //inserts the sequence of chars pointed by word into tree trie
int search_word(node *trie, char *word);			// returns the data associated with the word if found, -1 otherwise;
node *init_node(int data, char c); 					//inits a node with data and a character c
int char_index(char c);								//maps the given character into the child number
void print_trie(node *trie);						//prints the trie 
void list_words(node *trie);						//lists all the words in alphabetical order
int prefixes(node *trie, const char *prefix);				//lists the number of prefixes to the given pattern, prefix