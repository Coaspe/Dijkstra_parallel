#include "dijkstra.h"
#include <omp.h>
/**
 * Dijsktra Algorithm
 * 
 * @param N The size of map. 
 * @param cost 2D Array of the map's distance. 
 * @param path The shortest path. You have to save the shortest path here. 
 * @param source The point of start. 
 * @param target The point of end. 
 * @param numThreads The number of threads executing this algorithm. 
 * 
 * @return Shortest path cost from source to target. 
**/
int dijsktra(const int N, const vector<vector<int>>& cost, vector<int>& path, const int source, const int target, const int numThreads)
{
    // Set the number of threads. 
    omp_set_num_threads(numThreads);

    // Initialize parameters. 
    vector<int> dist(N, MAX);
    vector<int> prev(N, -1);
    vector<int> selected(N, 0);

	int start = source;
	selected[start] = 1;
	dist[start] = 0;

    // Find shortest path. 
	while (selected[target] == 0)
	{
		int min = MAX;
		int m = 0, d;
#pragma omp parallel private(i) shared(dist, min, selected, prev, N) 
		{
		for (int i = 0; i< N; i++)
		{
			d = dist[start] + cost[start][i];
			if (d < dist[i] && selected[i] == 0)
			{
				dist[i] = d;
				prev[i] = start;
			}

			if (min > dist[i] && selected[i] == 0)
			{
				min = dist[i];
				m = i;
			}
		}

		start = m;
		selected[start] = 1;
	}

    // Write path. 
	start = target;
	while (start != -1)
	{
        path.push_back(start);
		start = prev[start];
	}

    // The path is stored in reverse. 
    // So reverse it. 
    reverse(path.begin(), path.end());

	return dist[target];
}