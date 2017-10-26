/*
Computing the minimum cost of a flight. 
Implement algorithm of Dijkstra to find minimum cost of a flight. 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>
using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::greater;
using std::make_pair;

typedef pair<int, int> iPair;

int distance(vector<vector<iPair> > &adj, int s, int t) {

	vector<int> dist(adj.size(), INT_MAX);
	priority_queue < iPair, vector <iPair>, greater<iPair> > pq;
	dist[s] = 0;
	pq.push(make_pair(0, s));

	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		vector<iPair> ::iterator it;
		for (it = adj[u].begin(); it != adj[u].end(); it++)
		{
			int v = (*it).first;
			int weight = (*it).second;
			if (dist[v] > dist[u] + weight)
			{				
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	
	if (dist[t] != INT_MAX)
		return dist[t];
	else
		return -1;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<iPair> > adj2(n, vector<iPair>());
	vector<vector<int> > cost(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		//adj[x - 1].push_back(y - 1);
		//cost[x - 1].push_back(w);
		adj2[x - 1].push_back(make_pair(y - 1, w));
	}
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj2, s, t);
	system("pause");
	return 0;
}
