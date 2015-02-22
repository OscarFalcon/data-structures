#include <stdio.h>
#include <stdlib.h>

#include "trie.h"


node *init_node(int data, char c)
{
	node *n;
	int i;
	
	n = (node *) malloc((size_t)sizeof(node));
	if(n == NULL)
	{
		fprintf(stderr,"malloc error");
		perror("unable to malloc node");
		return NULL;
	}
	
	n->data = data;
	n->character = c;
	n->isWord = FALSE;
	n->prefixes = 0;
	
	for(i=0;i<ALPHABET_SIZE;i++)
		(n->children)[i] = NULL;
	
	return n;
}


int char_index(char c)
{
	if( c < 97 || c > 122)
		return -1;
	return c - 97;
	
}

/** base and c both must not be NULL **/
static int add_word(node *node,char *c,int data, int newNode)
{
	int childNew = FALSE;
	int index;
	
	//fprintf(stderr,"char: %c\n",*c);
	
	if( *c == '\0')									/** recursion base case **/
	{
		node->isWord = TRUE;
		node->data = data;
		return TRUE;
	}
			
	index = char_index(*c);		
	if(node->children[index] == NULL )					/** if there isnt a proper child node, create it **/
	{	
		node->children[index] = init_node(-1,*c);
		if(node->children[index] == NULL)				//if allocte fails, free this and all other nodes that were made in the sequence
		{
			if(newNode == TRUE)
			{
				fprintf(stderr,"free - ");
				free(node);
			}
			return FALSE;
		}
		childNew = TRUE;
	}
	node->children[index]->prefixes++;
	return add_word(node->children[index],c+1,data,childNew);
}

int insert_word(node **trie, char *word,int data)
{
	fprintf(stderr,"inserting %s\n",word);
	
	if(word == NULL)
	{
		fprintf(stderr,"null word not allowed\n");
		return FALSE;
	}
	
	if( *word == '\0')
	{
		fprintf(stderr,"empty word not allowed\n");
	}
	
	if(*trie == NULL && ((*trie = init_node(-1,'\0')) == NULL))
	{
		return FALSE;
	}
	
	return add_word(*trie,word,data,FALSE);
}

int search_word(node *trie, char *word)			// returns the data associated with the word if found, -1 otherwise;
{
	int charIndex;
	char *copy;
	
	if(trie == NULL)
	{
		fprintf(stderr,"trie tree is null");
		return -1;
	}
	
	if(word == NULL || *word == '\0')
	{
		fprintf(stderr,"null or empty word argument");
		return -1;
	}
	
	copy = word;
	while( trie != NULL && *copy != '\0')
	{
		charIndex = char_index(*copy);
		trie = trie->children[charIndex];
		copy++;
	}
	
	if(trie != NULL && trie->isWord == TRUE)
	{
		fprintf(stderr,"word %s found!\n",word);
		return trie->data;
	}
	fprintf(stderr,"word: %s not found\n",word);
	return FALSE;
}

int prefixes(node *trie, const char *prefix)
{
	if(trie == NULL)
		return -1;
	
	while(trie != NULL && *prefix != '\0')
		trie = trie->children[char_index(*prefix++)];
		
	if(trie != NULL )
		return trie->prefixes;
	
	return 0;
}



void indent(int h)
{
	int i;
	for(i=0;i<h;i++)
		printf(" ");
}


static void print_chars(node *n,int h)
{
	int i;
	
	if(n == NULL )		// base case for recursion
	{	
		return;
	}
		
	indent(h);
	
	if(n->isWord == TRUE)
	{
		printf("%c-\n",n->character);
	}
	else
	{
		printf("%c\n",n->character);
	}
	
	
	for(i=0;i<ALPHABET_SIZE;i++)
	{
		print_chars((n->children)[i],h+1);
	}
	
	return;
	
}

void list_words(node *trie)
{
	if(trie == NULL)
	{
		fprintf(stderr,"null trie\n");
		return;
	}
	
	print_chars(trie,0);
}





void print_trie(node *trie)
{
	return;
}

