#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>


int hash_function(int key, int size)
{
	double result;
	result = size * ( fmod ( (key * 0.6180339887),1.0) );

	return (int)result;
}


int insert (int hashtable[], int key, int size)
{
	int hash_index, n=0;
	int reprobe = 0;

	hash_index = hash_function(key, size);
	
	//-2 means the cell is empty
	while (hashtable[hash_index] != -2)
	{
		hash_index++;
		n++;
		reprobe++;

		if (hash_index >= size)
		{
			hash_index = 0;
		}
		
		if(n==size)
		{
			reprobe = 0;
			break;
		}
	}
	

	if( hashtable[hash_index] == -2)
	{
		hashtable[hash_index] = key;	
	}
	
	return reprobe;
	
}




//search function return the number of reprobe.
//if size_percent = 50, it will search for 50% of the table only
//if size_percent = 90, it will search for 90% of the table only
//if it return total size, the number is not found.
int search(int hashtable[], int key, int size, int size_percent)
{
	int hash_index, n=0;
	int reprobe = 0;
	int size_limit;
	
	hash_index = hash_function(key, size);

	if(size_percent == 50)
	{
		size_limit = size/2;
	}

	if(size_percent == 90)
	{
		size_limit = size * 9 / 10;
	}
	
	while (n <= size_limit)
	{
		if(hashtable[hash_index] == key)
		{
			break;
		}
		else
		{
			hash_index++;
			n++;
			reprobe++;
		}
		
		if(hash_index >= size)
		{
			hash_index = 0;
		}
		
		if(n >= size_limit)
		{
			break;
		}
	}
	return reprobe;
}
