#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct Entry
{
      int key_data;
};

struct Link_List
{
      struct Entry data;
      struct Link_List *link;
};

int hash_function(int key, int size)
{
	double result;
	result = size * ( fmod ( (key * 0.6180339887),1.0) );

	return (int)result;
}

int insert(struct Link_List *hashtable[], struct Entry entry_link_list, int size)
{
	int key, hash_index, reprobe=0;
	struct Link_List *temp;
	temp = (struct Link_List*)malloc (sizeof(struct Link_List));

	key = entry_link_list.key_data;

	hash_index = hash_function(key, size);

	temp -> data = entry_link_list;
	temp -> link = hashtable[hash_index];
	hashtable[hash_index] = temp;

	return reprobe;

}

int search(struct Link_List *hashtable[], int key, int size, int size_percent)
{
	int hash_index, n = 0, reprobe = 0, size_limit;
	struct Link_List *temp;

	if(size_percent == 50)
	{
		size_limit = size/2;
	}

	if(size_percent == 90)
	{
		size_limit = size * 9 / 10;
	}

	hash_index = hash_function(key, size);
	temp = hashtable[hash_index];

	while(temp != NULL && n <= size_limit)
	{
		if(temp -> data.key_data == key)
		{
			return reprobe;
		}
		temp = temp -> link;
		reprobe++;
		n++;
	}
	return reprobe;
}
