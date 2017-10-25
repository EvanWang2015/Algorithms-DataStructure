#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool isCyclicUtil(int v, vector<bool>& visited, vector<bool>& recStack, vector<vector<int>>&adj)
{
	if (visited[v] == false)
	{
		visited[v] = true;
		recStack[v] = true;

		vector<int>::iterator it;
		for (it = adj[v].begin(); it != adj[v].end(); it++)
		{
			if (!visited[*it] && isCyclicUtil(*it, visited, recStack, adj))
				return true;
			if (recStack[*it])
				return true;
		}
	}
	recStack[v] = false;
	return false;
}

int acyclic(vector<vector<int> > &adj) {
	//write your code here
	vector<bool> visited(adj.size(), false);
	vector<bool> recStack(adj.size(), false);

	for (int i = 0; i < adj.size(); i++)
	{
		if (isCyclicUtil(i, visited, recStack, adj))
			return 1;
	}
	return 0;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}
	std::cout << acyclic(adj);
	//system("pause");
	return 0;
}
