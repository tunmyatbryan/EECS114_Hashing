#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "hashlinear.c"

/* ============================================================
 */


int main (int argc, char* argv[])
{
	int size = -1, key;
	int max_number = 100000;
	int *hashtable;

	if (argc == 2) {
		size = atoi (argv[1]);
		assert (size > 0);
	} else {
		fprintf (stderr, "usage: %s <n>\n", argv[0]);
		fprintf (stderr, "where <n> is the size of the hash table.\n");
		return -1;
	}


	double size_50 = size/2, size_90 = size * 9 / 10;
	double reprobe_50_count = 0, reprobe_90_count = 0;
	double reprobe_insert_50 = 0, reprobe_insert_90 = 0;
	double average_insert_50 = 0, average_insert_90 = 0;

	double reprobe_search_50 = 0, reprobe_search_90 = 0;
	double average_search_50 = 0, average_search_90 = 0;

	srand((unsigned)time(NULL));

	hashtable = (int*)malloc(size * sizeof(int));

	for(int i = 0; i < size; i++)
	{
		hashtable[i] = -2;
	}


	for(int i = 0; i < size; i++)
	{
		key = rand() % max_number;
		
		if( i < size_50 )
		{
			reprobe_50_count = (double)insert (hashtable, key, size);
			reprobe_insert_50 = reprobe_insert_50 + reprobe_50_count;
			reprobe_insert_90 = reprobe_insert_50;
			
		}
		
		if( i >= size_50 && i <= size_90)
		{
			reprobe_insert_90 = reprobe_insert_90 + (double)insert (hashtable, key, size);
		}
	}

	average_insert_50 = reprobe_insert_50 / size_50;
	average_insert_90 = reprobe_insert_90 / size_90;
	
	printf ("the average number of reprobes for inserting 50 percentage load = %lf\n", average_insert_50);
	printf ("the average number of reprobes for inserting 90 percentage load = %lf\n", average_insert_90);

	printf ("\n");

	
	

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

	free(hashtable);

	return 0;
}

/* eof */
