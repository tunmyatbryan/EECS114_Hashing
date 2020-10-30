#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <fstream>


struct Adjacency_List_Node
{
	int next_vertex;
	double weight;
	struct Adjacency_List_Node* next;
};

struct Adjacency_List
{
	struct Adjacency_List_Node* vertex;
};

struct Graph
{
	int total_vertex;
	struct Adjacency_List* array;
};

struct Adjacency_List_Node* New_Adjacency_List_Node(int next_vertex, double weight) 
{ 
	struct Adjacency_List_Node* new_Adjacency_Node = (struct Adjacency_List_Node*)malloc(sizeof(struct Adjacency_List_Node)); 
	new_Adjacency_Node->next_vertex = next_vertex; 
	new_Adjacency_Node->weight = weight; 
	new_Adjacency_Node->next = NULL; 
	return new_Adjacency_Node; 
}

struct Graph* create_Graph(int total_vertex) 
{ 
	struct Graph* new_graph = (struct Graph*)malloc(sizeof(struct Graph)); 
	new_graph->total_vertex = total_vertex; 

	new_graph->array = (struct Adjacency_List*)malloc(total_vertex * sizeof(struct Adjacency_List)); 

	for (int i = 0; i < total_vertex; i++) 
	{
		new_graph->array[i].vertex = NULL; 
	}

	return new_graph;
} 


void add_Edge(struct Graph* graph, int ori_vertex, int next_vertex, double weight) 
{ 
	struct Adjacency_List_Node* new_Adjacency_Node = New_Adjacency_List_Node(next_vertex, weight); 
	new_Adjacency_Node->next = graph->array[ori_vertex].vertex; 
	graph->array[ori_vertex].vertex = new_Adjacency_Node; 

	new_Adjacency_Node = New_Adjacency_List_Node(ori_vertex, weight); 
	new_Adjacency_Node->next = graph->array[next_vertex].vertex; 
	graph->array[next_vertex].vertex = new_Adjacency_Node; 
}

struct Min_Heap_Node
{
	int heap_vertex;
	int heap_key;
};


struct Min_Heap { 
	int size;
	int max_size;
	int* pointer;
	struct Min_Heap_Node** array; 
}; 


struct Min_Heap_Node* New_Min_Heap_Node(int heap_vertex, int heap_key) 
{ 
	struct Min_Heap_Node* new_min_Heap_Node = (struct Min_Heap_Node*)malloc(sizeof(struct Min_Heap_Node)); 
	new_min_Heap_Node->heap_vertex = heap_vertex; 
	new_min_Heap_Node->heap_key = heap_key; 
	return new_min_Heap_Node; 
} 


struct Min_Heap* create_Min_Heap(int max_size) 
{ 
	struct Min_Heap* new_min_Heap = (struct Min_Heap*)malloc(sizeof(struct Min_Heap)); 
	new_min_Heap->size = 0; 
	new_min_Heap->max_size = max_size; 
	new_min_Heap->pointer = (int*)malloc(max_size * sizeof(int));
	new_min_Heap->array = (struct Min_Heap_Node**)malloc(max_size * sizeof(struct Min_Heap_Node*)); 
	return new_min_Heap; 
} 

void swap_Min_Heap_Node(struct Min_Heap_Node** node_a, struct Min_Heap_Node** node_b) 
{ 
	struct Min_Heap_Node* temp = *node_a; 
	*node_a = *node_b; 
	*node_b = temp; 
} 

void Min_Heapify(struct Min_Heap* min_Heap, int heap_index) 
{ 
	int smallest_index, left_index, right_index; 
	int index_size = 2 * heap_index;
	
	smallest_index = heap_index; 
	left_index = index_size + 1; 
	right_index = index_size + 2; 

	if ( (left_index) < (min_Heap->size) ) 
	{
		if( (min_Heap->array[left_index]->heap_key) < (min_Heap->array[smallest_index]->heap_key) )
		{
			smallest_index = left_index; 
		}
	}
	
	if ( (right_index) < (min_Heap->size) ) 
	{
		if( (min_Heap->array[right_index]->heap_key) < (min_Heap->array[smallest_index]->heap_key) )
		{
			smallest_index = right_index; 
		}
	}	

	if (smallest_index != heap_index) { 
		Min_Heap_Node* smallest_Node = min_Heap->array[smallest_index]; 
		Min_Heap_Node* index_Node = min_Heap->array[heap_index]; 

		min_Heap->pointer[smallest_Node->heap_vertex] = heap_index; 
		min_Heap->pointer[index_Node->heap_vertex] = smallest_index; 

		swap_Min_Heap_Node(&min_Heap->array[smallest_index], &min_Heap->array[heap_index]);
		
		Min_Heapify(min_Heap, smallest_index);
	} 
}

int is_Empty(struct Min_Heap* min_Heap) 
{ 
	if(min_Heap->size == 0)
	{
		return 1;
	}
	return 0;
} 

struct Min_Heap_Node* extract_Min(struct Min_Heap* min_Heap) 
{ 
	if (is_Empty(min_Heap) == 1)
	{
		return NULL;
	}
		
	struct Min_Heap_Node* root_node = min_Heap->array[0]; 

	struct Min_Heap_Node* last_node = min_Heap->array[min_Heap->size - 1]; 
	min_Heap->array[0] = last_node; 

	min_Heap->pointer[root_node->heap_vertex] = min_Heap->size - 1; 
	min_Heap->pointer[last_node->heap_vertex] = 0; 

	
	--min_Heap->size;
	Min_Heapify(min_Heap, 0); 

	return root_node;
} 


void decrease_Key(struct Min_Heap* min_Heap, int heap_vertex, int heap_key) 
{ 
	int index;
	index = min_Heap->pointer[heap_vertex]; 

	min_Heap->array[index]->heap_key = heap_key; 

	while (index && ( (min_Heap->array[index]->heap_key) < (min_Heap->array[(index - 1) / 2]->heap_key) ) ) 
	{
		min_Heap->pointer[min_Heap->array[index]->heap_vertex] = (index - 1) / 2; 
		min_Heap->pointer[min_Heap->array[(index - 1) / 2]->heap_vertex] = index; 
		swap_Min_Heap_Node(&min_Heap->array[index], &min_Heap->array[(index - 1) / 2]); 

		index = (index - 1) / 2; 
	} 
}


int is_In_Min_Heap(struct Min_Heap* min_Heap, int heap_vertex) 
{ 
	if (min_Heap->size > min_Heap->pointer[heap_vertex] ) 
	{
		return 1; 
	}
	return 0; 
} 

void printArr(double arr[], int n, int output_flag) 
{ 

	FILE *output;

	if(output_flag == 1)
	{
		output = fopen ("denseMST_output.txt", "w");
	}
	else if(output_flag == 2)
	{
		output = fopen ("spareMST_output.txt", "w");
	}

	for(int i = 0; i < n; i++)
	{
		fprintf(output, "%d - %d\n", i, arr[i]);
	}
	fclose(output);
}

void Prims(struct Graph* graph, int output_flag)
{
	int max_size, vertex;
	max_size = graph->total_vertex;
	
	double primsMST[max_size];
	int weight_key[max_size];
	
	
	struct Min_Heap* min_Heap = create_Min_Heap(max_size);
	
	for (int i = 1; i < max_size; i++) 
	{ 
		primsMST[i] = 0.0; 
		weight_key[i] = 2147483647;
		min_Heap->array[i] = New_Min_Heap_Node(i, weight_key[i]); 
		min_Heap->pointer[i] = i; 
	}
	
	
	weight_key[0] = 0; 
	min_Heap->array[0] = New_Min_Heap_Node(0, weight_key[0]); 
	min_Heap->pointer[0] = 0; 
	
	min_Heap->size = max_size; 
	
	while (is_Empty(min_Heap) == 0) { 
		struct Min_Heap_Node* min_Heap_Node = extract_Min(min_Heap); 
		int j = min_Heap_Node->heap_vertex;

		struct Adjacency_List_Node* prims_adj_list_node = graph->array[j].vertex; 
		while (prims_adj_list_node != NULL) 
		{ 
			vertex = prims_adj_list_node->next_vertex; 

			if (is_In_Min_Heap(min_Heap, vertex) == 1 )
			{
				if(prims_adj_list_node->weight < weight_key[vertex]) 
					{ 
						weight_key[vertex] = prims_adj_list_node->weight; 
						primsMST[vertex] = (double)j; 
						decrease_Key(min_Heap, vertex, weight_key[vertex]); 
					} 
			}
			prims_adj_list_node = prims_adj_list_node->next; 
		} 
	} 
	
	printArr(primsMST, max_size, output_flag);
	
}
