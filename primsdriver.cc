#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h> 
#include <iostream>
#include <fstream>
#include "timer.c"

#include "prims.cc"

/* ============================================================
 */

/*
int main()
{

// Let us create the graph given in above fugure 
	int V = 9; 
	struct Graph* graph = create_Graph(V); 
	add_Edge(graph, 0, 1, 4); 
	add_Edge(graph, 0, 7, 8); 
	add_Edge(graph, 1, 2, 8); 
	add_Edge(graph, 1, 7, 11); 
	add_Edge(graph, 2, 3, 7); 
	add_Edge(graph, 2, 8, 2); 
	add_Edge(graph, 2, 5, 4); 
	add_Edge(graph, 3, 4, 9); 
	add_Edge(graph, 3, 5, 14); 
	add_Edge(graph, 4, 5, 10); 
	add_Edge(graph, 5, 6, 2); 
	add_Edge(graph, 6, 7, 1); 
	add_Edge(graph, 6, 8, 6); 
	add_Edge(graph, 7, 8, 7); 

	Prims(graph); 

	return 0; 

}
*/

using namespace std;

int main (int argc, char* argv[])
{
	//int N = -1, T = -1;
	long double total_time = 0.0L;

/*
	if (argc == 3) {
		N = atoi (argv[1]);
		T = atoi (argv[2]);
		assert (N > 0);
		assert (T > 0);
	} else {
		fprintf (stderr, "usage: %s <n>\n", argv[0]);
		fprintf (stderr, "where <n> is the length of the list to sort.\n");
		return -1;
	}
*/

	struct Graph* graph_dense;
	int i = 0, original_v = 0, next_v = 0, total_vertex = 0;
	double weight = 0.0;
	
	int original_v_flag = 0, next_v_flag = 1, weight_flag = 2;
	int flag = 0, vertex_flag = 0;
	

	stopwatch_init ();
	struct stopwatch_t* timer_dense = stopwatch_create (); assert (timer_dense);


	ifstream file_dense("dense_100000.txt");
	double content_dense;
	
	while(file_dense >> content_dense)
	{
		if(vertex_flag == 0)
		{
			total_vertex = content_dense;
			vertex_flag = 1;
			graph_dense = create_Graph(total_vertex);
		}
		else if(vertex_flag != 0 && flag == original_v_flag )
		{
			original_v = content_dense;
			flag++;
		}
		else if(vertex_flag != 0 && flag == next_v_flag )
		{
			next_v = content_dense;
			flag++;
		}
		else if(vertex_flag != 0 && flag == weight_flag)
		{
			weight = content_dense;
			add_Edge(graph_dense, original_v, next_v, weight); 
			long double t_qs = stopwatch_stop (timer_dense);
			total_time += t_qs;
			flag = 0;
		}
	}
	
	Prims(graph_dense, 1);


/*
	struct Queue *q = createQueue();
	if(!q)
	{
		return -1;
	}

	srand((unsigned)time(NULL));

	for(int i = 0; i < N; i++)
	{
		enQueue(q, ((float)rand())/RAND_MAX );  
	}
  	printf ("\nN == %d\n\n", N);

  
	// dequeue/enqueue t times
	for(int i = 0; i < T; i++)
	{
		stopwatch_start (timer);
		struct QueueNode *n = deQueue(q);
		enQueue(q, n->number);
		long double t_qs = stopwatch_stop (timer);
		total_time += t_qs;
	}
*/
	// take average
    	//avg_time = total_time;

	printf ("Total time for dense.txt: %Lg seconds\n", total_time);

	printf ("\n");

	stopwatch_destroy (timer_dense);
	



	total_time = 0.0L;
	struct Graph* graph_sparse;
	i = 0, original_v = 0, next_v = 0, total_vertex = 0;
	weight = 0.0;
	
	original_v_flag = 0, next_v_flag = 1, weight_flag = 2;
	flag = 0, vertex_flag = 0;
	

	stopwatch_init ();
	stopwatch_t* timer_sparse = stopwatch_create (); assert (timer_sparse);


	ifstream file_sparse("sparse_100000.txt");
	double content_sparse;
	
	while(file_sparse >> content_sparse)
	{
		if(vertex_flag == 0)
		{
			total_vertex = content_sparse;
			vertex_flag = 1;
			graph_sparse = create_Graph(total_vertex);
		}
		else if(vertex_flag != 0 && flag == original_v_flag )
		{
			original_v = content_sparse;
			flag++;
		}
		else if(vertex_flag != 0 && flag == next_v_flag )
		{
			next_v = content_sparse;
			flag++;
		}
		else if(vertex_flag != 0 && flag == weight_flag)
		{
			weight = content_sparse;
			add_Edge(graph_sparse, original_v, next_v, weight); 
			long double t_qs = stopwatch_stop (timer_sparse);
			total_time += t_qs;
			flag = 0;
		}
	}
	
	Prims(graph_sparse, 2);

	//avg_time = total_time;

	printf ("Total time for sparse.txt: %Lg seconds\n", total_time);

	printf ("\n");

	stopwatch_destroy (timer_sparse);





	return 0;
}

/* eof */
