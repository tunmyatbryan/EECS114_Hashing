#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "hashchain.c"

/* ============================================================
 */


int main (int argc, char* argv[])
{
	int size = -1;
	int max_number = 100000;
	int key;

	if (argc == 2) {
		size = atoi (argv[1]);
		assert (size > 0);
	} else {
		fprintf (stderr, "usage: %s <n>\n", argv[0]);
		fprintf (stderr, "where <n> is the size of the hash table.\n");
		return -1;
	}

	struct Link_List *hashtable[size];
    	struct Entry entry_record;

	for(int i = 0; i < size; i++)
	{
		hashtable[i] = NULL;
	}

	double size_50 = size/2, size_90 = size * 9 / 10;
	double reprobe_50_count = 0, reprobe_90_count = 0;
	double reprobe_insert_50 = 0, reprobe_insert_90 = 0;
	double average_insert_50 = 0, average_insert_90 = 0;

	double reprobe_search_50 = 0, reprobe_search_90 = 0;
	double average_search_50 = 0, average_search_90 = 0;

	srand((unsigned)time(NULL));	

	for(int i = 0; i < size; i++)
	{
		entry_record.key_data = rand() % max_number;
		
		if( i < size_50 )
		{
			reprobe_50_count = (double)insert(hashtable, entry_record, size);
			reprobe_insert_50 = reprobe_insert_50 + reprobe_50_count;
			reprobe_insert_90 = reprobe_insert_50;
			
		}
		
		if( i >= size_50 && i <= size_90)
		{
			reprobe_insert_90 = reprobe_insert_90 + (double)insert(hashtable, entry_record, size);
		}
	}


	average_insert_50 = reprobe_insert_50 / size_50;
	average_insert_90 = reprobe_insert_90 / size_90;
	
	printf ("the average number of reprobes for inserting 50 percentage load = %lf\n", average_insert_50);
	printf ("the average number of reprobes for inserting 90 percentage load = %lf\n", average_insert_90);
	printf ("\nThere is no reprobing in chaining during insertion. So it is zero. The new key will always be inserted to the chain of the hash table index link list.\n");

	printf ("\n");

	
//search(struct Link_List *hashtable[], int key, int size)

	for(int i = 0; i < 10000; i++)
	{		
		key = rand() % max_number;
		reprobe_search_50 = reprobe_search_50 + (double)search(hashtable, key, size, 50);
		reprobe_search_90 = reprobe_search_90 + (double)search(hashtable, key, size, 90);
	}

	average_search_50 = reprobe_search_50 / 10000;
	average_search_90 = reprobe_search_90 / 10000;

	printf ("the average number of reprobes for searching 50 percentage load = %lf\n", average_search_50);
	printf ("the average number of reprobes for searching 90 percentage load = %lf\n", average_search_90);

	printf ("\n");



	return 0;
}

/* eof */
