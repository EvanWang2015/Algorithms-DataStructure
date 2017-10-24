#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void DFSUtil(vector<vector<int> > &adj, vector<bool>& ans, int v)
{
	ans[v] = true;
	vector<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end(); it++)
	{
		if (!ans[*it])
			DFSUtil(adj, ans, *it);
	}
}

int number_of_components(vector<vector<int> > &adj) {
	int res = 0;
	//write your code here
	vector<bool> ans(adj.size(),false);
	for (int i = 0; i < adj.size(); i++)
	{
		if (ans[i]==false)
		{
			DFSUtil(adj, ans, i);
			res++;
		}
	}
	return res;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << number_of_components(adj);
	//system("pause");
	return 0;
}
