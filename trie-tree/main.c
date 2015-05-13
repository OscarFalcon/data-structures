#include <stdio.h>
#include "trie.h"



void str_replace(char *string, char old, char new)
{
	if(string == NULL)
		return;
	
	while( *string != '\0'){
		if(*string == old)
			*string = new;
		string++;
	}
	
}

int main (void)
{
	int i;
	char buff[1024];
	node *trie;
	
	
	trie = NULL;
	i = 34;
	while(fgets(buff,sizeof(buff),stdin))
	{
		str_replace(buff,'\n','\0');
		if(insert_word(&trie,buff,i++) == FALSE)
		{
			fprintf(stderr,"could not insert data\n");
		}
	}

	
	fprintf(stderr,"data = %d\n",search_word(trie,"cat"));
	search_word(trie,"cate");
	search_word(trie,"caterpillar");
	search_word(trie,"catt");
	search_word(trie,"someword");
	fprintf(stderr,"number of prefixes with zeb: %d\n",prefixes(trie,"zebbraaa"));
	fprintf(stderr,"listing words...\n");
	list_words(trie);

	
	return 0;
}