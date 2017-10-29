#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <functional>
#include <climits>
using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::make_pair;
using std::greater;
typedef pair<int, long long> iPair;

void shortest_paths(vector<vector<iPair> > &adj, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {

	distance[s] = 0;
	int n = adj.size();

	vector<iPair>::iterator it;
	/*for (it = adj[s].begin(); it != adj[s].end(); it++)
	{
	int v = (*it).first;
	int weight = (*it).second;
	if (distance[v] > distance[s] + weight)
	distance[v] = distance[s] + weight;
	}
	*/
	queue<int> neg_que;
	for (int i = 1; i <n; i++)
	{
		for (int u = 0; u < n; u++)
		{
			if (distance[u] != LLONG_MAX)
			{
				//vector<iPair>::iterator it;
				for (it = adj[u].begin(); it != adj[u].end(); it++)
				{
					int v = (*it).first;
					long long weight = (*it).second;
					if (distance[v] > distance[u] + weight)
						distance[v] = distance[u] + weight;
				}
			}
		}
	}

	// |V|th Bellman Algorithm 
	for (int i = 0; i < n; i++)
	{
		int u = i;
		if (distance[u] == LLONG_MAX)
		{
			reachable[u] = 0;
			shortest[u] = 0;
		}
		else
		{
			//vector<iPair> ::iterator it;
			for (it = adj[u].begin(); it != adj[u].end(); it++)
			{
				int v = (*it).first;
				int weight = (*it).second;
				if (distance[v] > distance[u] + weight)
				{
					neg_que.push(v);
					distance[v] = distance[u] + weight;
				}
				reachable[v] = 1;
			}
			reachable[u] = 1;
		}

	}

	while (!neg_que.empty())
	{
		int u = neg_que.front();
		neg_que.pop();
		shortest[u] = 0;

		if (distance[u] != LLONG_MAX)
		{
			for (it = adj[u].begin(); it != adj[u].end(); it++)
			{
				int v = (*it).first;
				int weight = (*it).second;
				if (distance[v] > distance[u] + weight && shortest[v] != 0)
				{
					neg_que.push(v);
					distance[v] = distance[u] + weight;
					//std::cout << "did it haoppp?";
				}
				if (v == s)
				{
					shortest.assign(n, 0);
					break;
				}
			}
		}
	}

}

int main() {
	int n, m, s;
	std::cin >> n >> m;
	//vector<vector<int> > adj(n, vector<int>());
	//vector<vector<int> > cost(n, vector<int>());
	vector<vector<iPair> > adj(n, vector<iPair>());
	for (int i = 0; i < m; i++) {
		int x, y;
		long long w;
		std::cin >> x >> y >> w;
		//adj[x - 1].push_back(y - 1);
		//cost[x - 1].push_back(w);
		adj[x - 1].push_back(make_pair(y - 1, w));
	}
	std::cin >> s;
	s--;
	vector<long long> distance(n, LLONG_MAX);
	vector<int> reachable(n, 0);
	vector<int> shortest(n, 1);
	shortest_paths(adj, s, distance, reachable, shortest);
	for (int i = 0; i < n; i++) {
		if (!reachable[i]) {
			std::cout << "*\n";
		}
		else if (!shortest[i]) {
			std::cout << "-\n";
		}
		else {
			std::cout << distance[i] << "\n";
		}
	}

	//system("pause");
	return 0;
}
