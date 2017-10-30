/*
Clustering with Kruskal algorithm.
Author: Haitang Wang
*/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <array>
#include <climits>
using std::vector;
using std::pair;
using std::sort;

typedef pair<int, int> iPair;

bool myfunction(pair<double, iPair> a, pair<double, iPair> b)
{
	return (a.first < b.first);
}

int find(vector<vector<int>> & set_vertexes, int index)
{
	if (set_vertexes[index].size() > 0)
		return index;
	else
	{
		vector<int> ::iterator it;

		for (int i = 0; i < set_vertexes.size(); i++)
		{
			for (it = set_vertexes[i].begin(); it != set_vertexes[i].end(); it++)
			{
				if (*it == index)
					return i;
			}
		}
	}
	return -1;

}

void sets_union(vector<vector<int> > &set_vertexes, int find1, int find2)
{
	vector<int>::iterator it;

	for (it = set_vertexes[find2].begin(); it != set_vertexes[find2].end(); it++)
	{
		set_vertexes[find1].push_back(*it);
	}	
	set_vertexes[find2].erase(set_vertexes[find2].begin(), set_vertexes[find2].begin()+ set_vertexes[find2].size());
}

int cluster_num(vector<vector<int> > &set_vertexes)
{
	vector<int>::iterator it;

	int n = set_vertexes.size();
	int cluster = 0;
	for (int i = 0; i < n; i++)
	{
		if (set_vertexes[i].begin() != set_vertexes[i].end())
			cluster++;
	}

	return cluster;
}

double clustering(vector<int> x, vector<int> y, int k) {

	int n = x.size()*x.size();
	vector<pair<double, iPair> > dist(n, pair<double, iPair>());

	for (int i = 0; i < n; i++)
	{
		int row = i % x.size();
		int col = i / x.size();
		if (row < col)
		{
			dist[i].first = sqrt(pow(x[row] - x[col], 2) + pow(y[row] - y[col], 2));
			dist[i].second.first = row;
			dist[i].second.second = col;
				
		}
		else
		{
			dist[i].first = std::numeric_limits<double>::max();
			dist[i].second.first = row;
			dist[i].second.second = col;
		}
	}

	sort(dist.begin(), dist.end(), myfunction);// the default is increasing 

	vector<vector<int>> set_vertexes(x.size(),vector<int>());

	//cluster sets for all the vertexes 
	for (int i = 0; i < x.size(); i++)
		set_vertexes[i].push_back(i);

	int cluster;

	for (int i = 0; i < n; i++)
	{
		int row = dist[i].second.first;
		int col = dist[i].second.second;

		int find1 = find(set_vertexes, row);
		int find2 = find(set_vertexes, col);

		cluster = cluster_num(set_vertexes);

		if (find1 != find2 && (cluster >k ) )
		{
			sets_union(set_vertexes, find1, find2);
		}
		else
		{
			if (find1 != find2 && (cluster == k))
				return dist[i].first;
		}
	}
		
	return -1;
}

int main() {
	size_t n;
	int k;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cin >> k;
	std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
	//system("pause");
	return 0;
}
