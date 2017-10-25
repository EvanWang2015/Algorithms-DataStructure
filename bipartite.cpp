/*
Check if a Graph is Bipartite
An undirected graph is called bipartite if its vertices can be split into two parts such that each edge
of the graph joins to vertices from different parts. Bipartite graphs arise naturally in applications where
a graph is used to model connections between objects of two different types. 

An alternative difinition is following: a graph is bipartite if its vertices can be colored with two colors
(say, black and white) such that the endpoints of each edge have different colors. 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
	//I use breadth first search algorithm, starting from a arbitary vertice as the souce. 
	vector<bool> visited(adj.size(), false);
	queue<int> que;
	vector<int> distance(adj.size(), INT_MAX);

	que.push(0);
	distance[0] = 0;
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		vector<int>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++)
		{
			if (distance[*it] == INT_MAX)
			{
				que.push(*it);
				if (distance[*it] == INT_MAX)
				{
					if (distance[u] == 0)
						distance[*it] = 1;
					else
						distance[*it] = 0;						
				}
			}
			else
			{
				if (distance[u] == distance[*it])
					return 0;
			}
		}
	}

	return 1;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << bipartite(adj);

	//system("pause");
	return 0;
}
