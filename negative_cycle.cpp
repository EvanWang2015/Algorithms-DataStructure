/*
Detecting anomalies in Currency Exchange Rates. 
You are given a list of currencies of c1, c2, ...,cn together with a list of 
exchange rates: rij is the number of units of currency cj that one gets for 
one unit of ci. You would like to check whether it is possible to start with one unit
of some currency, perform a sequence of exchange, and get more than one unit of same currency.
=> which is equivalent to a negative cycle in the graph: 
ci->cj->...->ci has negative weight. This means that 
-(logcij + logcjk+logcki)<0. => 2^(logcij + log cjk + log cki)>1
*/

#include <iostream>
#include <vector>
#include <functional>
#include <climits>
using std::pair;
using std::make_pair;
using std::vector;

typedef pair<int, int> iPair;

int negative_cycle(vector<vector<iPair> > &adj) {
	
	int n = adj.size();
	vector<int> dist(n, INT_MAX);
	for (int i = 1; i < n; i++)
	{
		for (int u = 0; u < n; u++)
		{
			if (dist[u] == INT_MAX)
			{
				dist[u] = 0;
				vector<iPair>::iterator it;
				for (it = adj[u].begin(); it != adj[u].end(); it++)
				{
					int v = (*it).first;
					int weight = (*it).second;
					if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
						dist[v] = dist[u] + weight;
				}
			}		
		}
	}

	//the nth time Bellman-Ford algorithm

	for (int u = 0; u < n; u++)
	{
		vector<iPair>::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++)
		{
			int v = (*it).first;
			int weight = (*it).second;
			if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
				return 1;
		}
	}	

	return 0;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	//vector<vector<int> > adj(n, vector<int>());
	//vector<vector<int> > cost(n, vector<int>());
	vector<vector<iPair> > adj(n, vector<iPair>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;

		//adj[x - 1].push_back(y - 1);
		//cost[x - 1].push_back(w);

		adj[x - 1].push_back(make_pair(y - 1, w));
	}
	std::cout << negative_cycle(adj);
	system("pause");
	return 0;
}
