/*
This algorithm can be used to compute the minimum number of flight segments to get from one city to another one. 
The undirected graph: vertices represent cities, there is an edge between two vertices when there is a flight betwen
the corresponding two cities. Then, it suffices to find a shortest path from one of the given cities to the other one.

Input: A graph is given in the standard format. The next line contains two vertices u and v.
Output: Output the minmum number of edges in a pth from u to v. or -1 if there is no path. 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {

	//que is used to track the discovered vertices during exploration
	queue<int> que;
	vector<int> distance(adj.size(), INT_MAX);
	que.push(s);
	distance[s] = 0;
	vector<int> ::iterator it;
	while (!que.empty())
	{
		int u = que.front();
		que.pop();
		for (it = adj[u].begin(); it != adj[u].end(); it++)
		{
			if (distance[*it] == INT_MAX)
			{
				que.push(*it);
				distance[*it] = distance[u] + 1;
				if (t == *it)
					break;
			}
		}
	}
	if (distance[t] != INT_MAX)
		return distance[t];	
	return -1;
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
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, s, t);
	system("pause");
	return 0;
}
