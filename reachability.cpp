#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void DFSUtil(vector<vector<int> > &adj, vector<bool>& ans, int v, int y, int & flag)
{
	ans[v] = true;
	vector<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end(); it++)
	{
		if (!ans[*it])
			DFSUtil(adj, ans, *it, y, flag);
		if (y == *it)
		{
			flag = 1;
			return;
		}
	}	
}

int reach(vector<vector<int> > &adj, int x, int y) {
	//write your code here
	vector<bool> ans(adj.size(), false);
	//ans[x] = true;
	int flag = 0;

	DFSUtil(adj, ans, x, y, flag);
	
	return flag;
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
	int x, y;
	std::cin >> x >> y;
	std::cout << reach(adj, x - 1, y - 1);
	
	//system("pause");
	return 0;
}
