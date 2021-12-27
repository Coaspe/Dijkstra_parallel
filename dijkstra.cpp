#include "dijkstra.h"
#include <omp.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
	omp_set_num_threads(numThreads);

	vector<int> dist(N, MAX);
	vector<int> prev(N, -1);
	vector<int> selected(N, 0);

	int start = source;
	selected[start] = 1;
	dist[start] = 0; // source부터 node까지의 현재의 최단 거리를 갖는 vector

	// Find shortest path. 
	while (selected[target] == 0)
	{
		int min = MAX;
		int m = 0;

#pragma omp parallel
		{
			int local_min = MAX;
			int local_m = 0;

#pragma omp for nowait schedule(guided, N / numThreads)
			for (int i = 0; i < N; i++)
			{
				if (selected[i] == 1) {
					continue;
				}
				int d = dist[start] + cost[start][i];

				if (dist[i] > d)
				{
					dist[i] = d;
					prev[i] = start;
				}
				if (local_min > dist[i]) {
					local_min = dist[i];
					local_m = i;
				}
			}
#pragma omp critical
			{
				if (min > local_min)
				{
					min = local_min;
					m = local_m;
				}
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