/*
Introduction: the police department of a city has made all streets one-way.

You would like to check whether it is still possible to drive legally from any intersection to
any other intersection. For this, you construct a directed graph: 
vertices are intersections, there is an edge (u, v) whenever there is a (one-way) street from u
to v in the city. Then, it suffices to check whether all the vertices in the graph lie in the same
strongly connected component. 

Output: the number of strongly connected components. 
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

/*
Algorithm for 
*/
void DSFUtil(vector<vector<int> > & adj, vector<bool>& visited, int v, vector<int>& order)
{
	visited[v] = true;
	vector<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end(); it++)
	{
		if (visited[*it]==false)
		{
			DSFUtil(adj, visited, *it, order);
		}
	}
	order.push_back(v);
}

void RevDSFUtil(vector<vector<int> > & adj, vector<bool>& visited, int v)
{
	visited[v] = false;
	vector<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end(); it++)
	{
		if (visited[*it]==true)
		{
			RevDSFUtil(adj, visited, *it);
		}
	}
	//order.push_back(v);
}

int number_of_strongly_connected_components(vector<vector<int> > &adj, vector<vector<int> >& Radj) {
	int result = 0;
	
	vector<bool> visited(Radj.size(), false);
	vector<int> order;

	for (int i = 0; i < Radj.size(); i++)
	{
		if (visited[i] == false)
		{
			DSFUtil(Radj, visited, i, order);
		}
	}

	reverse(order.begin(), order.end());
	//std::cout << order.size() << std::endl;

	for (int i = 0; i < order.size(); i++)
	{
		if (visited[order[i]])
		{
			RevDSFUtil(adj, visited, order[i]);
			result++;
		}
	}

	return result;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > Radj(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		Radj[y - 1].push_back(x - 1);
	}
	std::cout << number_of_strongly_connected_components(adj, Radj);
	system("pause");
	return 0;
}
