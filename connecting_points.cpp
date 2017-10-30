#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>

using std::priority_queue;
using std::vector;
using std::pair;
using std::sort;
using std::make_pair;
using std::greater;

bool myfunction(pair<double, int>& p1, pair<double, int>& p2)
{
	return (p1.first < p2.first);
}

double minimum_distance(vector<int> x, vector<int> y) {

	double result = 0.;

	vector<int> index(x.size());

	vector<pair<double, int> >dist(x.size(), pair<double, int>());
	int n = x.size();
	for (int i = 0; i < n; i++)
	{
		dist[i] = make_pair(std::numeric_limits<double>::max(), i);
	}

	index[0]=0;
	int size_unexplored = n;
	dist[0].first = 0;
	dist[0].second = 0;
	size_unexplored--;
	while (size_unexplored>=0)
	{	
		std::swap(dist[0], dist[size_unexplored]);
		pair<double, int> min_dist = dist[size_unexplored];
		index.push_back(dist[size_unexplored].second);
		result += min_dist.first;
		//std::cout << "dist[0]: distance, int: " << dist[0].second << "and" << dist[3].second<<std::endl;
	    //std::cout << "loop num:  " << size_unexplored << std::endl;
		for (int i = 0; i < size_unexplored; i++)
		{
			pair<double, int> curr_dist = dist[i];

			double temp_dist = sqrt(pow(x[curr_dist.second] - x[min_dist.second], 2)  + pow(y[curr_dist.second] - y[min_dist.second],2));

		//	std::cout << "i: " << i << " " << x[curr_dist.second] << " and x " << x[min_dist.second] << " y: " << y[curr_dist.second] << " " << y[min_dist.second]<<std::endl;;
			if (temp_dist < curr_dist.first)
				dist[i].first = temp_dist;			
		}
		sort(dist.begin(), dist.begin() + size_unexplored, myfunction);
		size_unexplored--;
		
	}
	

	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
	//system("pause");
	return 0;
}
