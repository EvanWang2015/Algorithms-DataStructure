#include <cstdio>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <functional>
#include <unordered_map>
#include <iostream>
using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

//record vertexes and distance
typedef vector<vector<pair<int, int> >> Adjmix; 
// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>, vector<pair<Len, int>>, greater<pair<Len, int>>>> Queue;

const Len INF = numeric_limits<Len>::max();

class Bidijkstra {
	// Number of nodes
	int n_;
	// Graph adj_[0] and cost_[0] correspond to the initial graph,
	// adj_[1] and cost_[1] correspond to the reversed graph.
	// Graphs are stored as vectors of adjacency lists corresponding
	// to nodes.
	// Adjacency list itself is stored in adj_, and the corresponding
	// edge costs are stored in cost_.
	//Adj adj_;
	//Adj cost_;
	vector<Adjmix> adjmix_;
	// distance_[0] stores distances for the forward search,
	// and distance_[1] stores distances for the backward search.
	vector<vector<Len>> distance_;
	// Stores all the nodes visited either by forward or backward search.
	//vector<int> workset_;
	// Stores a flag for each node which is True iff the node was visited
	// either by forward or backward search.
	//vector<bool> visited_;
	vector<vector<int>> pri_dequed;
	//unordered_map<int, Len> pri_dequed_r;

public:
	Bidijkstra(int n, vector<Adjmix> adjmix)
		: n_(n), adjmix_(adjmix),distance_(2, vector<Len>(n, INF))//, visited_(n)
	{
		//workset_.reserve(n);
		pri_dequed.resize(2, vector<int> (n));
	}

	// Initialize the data structures before new query,
	// clear the changes made by the previous query.
	void clear() {
		distance_[0].assign(distance_[0].size(), INF);
		distance_[1].assign(distance_[1].size(), INF);

		pri_dequed[0].assign(pri_dequed[0].size(), 0);
		pri_dequed[1].assign(pri_dequed[1].size(), 0);
		//workset_.clear();
	}

	// Processes visit of either forward or backward search 
	// (determined by value of side), to node v trying to
	// relax the current distance by dist.
	void visit(Queue& q, int side, int v) {
				
		if (!q[side].empty())
		{
			pri_dequed[side][v] = 1;
			int u = q[side].top().second;
			q[side].pop();
			vector<pair<int, int>>::iterator it;
			int v ;
			for (it = adjmix_[side][u].begin(); it != adjmix_[side][u].end(); ++it)
			{
				v = (*it).first;
				
				if (distance_[side][v] ==INF || (distance_[side][v] > distance_[side][u] + (*it).second))
				{
					distance_[side][v] = distance_[side][u] + (*it).second;
					q[side].push(make_pair(distance_[side][v], v));
				}					
			}
		}
	}


	//process to find where forward dijkstra and backward dijkstra
	//meet and keep track the shortest distace 
	bool find_uv(int side, int u)
	{
		if (pri_dequed[side][u] == 1)
			return true;
		else
			return false;
	}

	bool bi_dijkstra_end(Len& best_dist, Queue & q)
	{
		
		//cout << q[0].empty() << " and " << q[1].empty() << endl;
		//cout << best_dist << " " << distance_[0][q[0].top().second] << " " << distance_[1][q[1].top().second] << endl;
		if (!q[0].empty() && !q[1].empty())
		{
			if (best_dist < distance_[0][q[0].top().second] || best_dist< distance_[1][q[1].top().second])
				return true;
		}
		else if (!q[0].empty() && q[1].empty())
		{
			if (best_dist < distance_[0][q[0].top().second])
				return true;
		}
		else if (q[0].empty() && !q[1].empty())
		{
			if (best_dist < distance_[1][q[1].top().second])
				return true;
		}
		else
			return false;
	
	}
	// Returns the distance from s to t in the graph.
	Len query(int s, int t) {
		clear();
		Len  best_dist = INF;
		Queue q(2);
		distance_[0][s] = distance_[1][t]=0;
		q[0].push(make_pair(0, s));
		q[1].push(make_pair(0, t));

		int u, v;

		while (!q[0].empty() || !q[1].empty())
		{
			

			if (!q[1].empty())
			{
				u = q[1].top().second;

				visit(q, 1, u);
				
				if (find_uv(0, u)) //when it's recorded 
				{
					if (best_dist > distance_[0][u] + distance_[1][u])
					{
						best_dist = distance_[0][u] + distance_[1][u];
					}
						
					if (bi_dijkstra_end(best_dist, q)==true)
						return best_dist;
				}
			}

			if (!q[0].empty())
			{
				u = q[0].top().second;
				visit(q, 0, u);

				if (find_uv(1, u)) //when it's recorded 
				{
					if (best_dist > distance_[0][u] + distance_[1][u])
					{
						best_dist = distance_[0][u] + distance_[1][u];
					}

					if (bi_dijkstra_end(best_dist, q) == true)
						return best_dist;
				}

			}
		}

		if(best_dist==INF)
			return -1;
		return best_dist;
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	vector<Adjmix> adjmix(2, vector < vector<pair<int, int> >>(n));
	for (int i = 0; i<m; ++i) {
		int u, v, c;
		//scanf("%d%d%d", &u, &v, &c);
		cin >> u >> v >> c;
		adjmix[0][u - 1].push_back(make_pair(v - 1, c));
		adjmix[1][v - 1].push_back(make_pair(u - 1, c));
	}

	Bidijkstra bidij(n, adjmix);

	int t;
	//scanf("%d", &t);
	cin >> t;
	for (int i = 0; i<t; ++i) {
		int u, v;

		cin >> u >> v;
		printf("%lld\n", bidij.query(u - 1, v - 1));
	}

	system("pause");
	return 0;
}
