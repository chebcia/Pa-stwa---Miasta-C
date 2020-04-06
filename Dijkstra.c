#include "Dijkstra.h"

int minDistance(int dist[], int sptSet[], int size)
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < size; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}
int* dijkstra(struct List * head, int src)
{
	int dist[INITIAL_ARRAY_SIZE];
	int sptSet[INITIAL_ARRAY_SIZE];

	for (int i = 0; i < head->size; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = 0;
	}
	dist[src] = 0;

	for (int count = 0; count < head->size - 1; count++)
	{
		int u = minDistance(dist, sptSet, head->size);


		sptSet[u] = 1;

		for (int v = 0; v < head->size; v++)
			if (!sptSet[v] && findDistanceAtIndex(head, u, v) && dist[u] != INT_MAX
				&& dist[u] + findDistanceAtIndex(head, u, v) < dist[v])
				dist[v] = dist[u] + findDistanceAtIndex(head, u, v);
	}
	return dist;

}
