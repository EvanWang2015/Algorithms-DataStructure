/*
Implement an algorithm for the knapsack without repetitions problem. 

In this problem, you are given a set of bars of gold and your goal is to take as much gold as you possible into your bag. 

There is just one copy of each bar and for each bar you can either take it our not (hence you cannot take a fraction of a bar). 

Constraint: 1<=W<=10^4
			1<=n<=300
			0<w0,...,wn-1<=10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

bool myfunction(int i, int j) { return (j>i);}

int optimal_weight(int W, const vector<int> &ws) {

	vector< vector<int> > value(ws.size()+1, vector<int> (W+1));

	//std::cout << value.size()<<" "<<value[0].size() << std::endl;

	/*
	loop to fill the maximum weight(value) your bag takes considering with/without taking current piece
	*/
	for (int i = 0; i <= W; i++)
		value[0][i] = 0;

	for (int i = 0; i <= ws.size(); i++)
		value[i][0] = 0;

	int n = ws.size();
	for (int i = 1; i <= n; i++)
	{
		for (int w = 1; w <= W; w++)
		{
			value[i][w] = value[i - 1][w];
			if (ws[i-1] <= w)
			{
				int val = value[i - 1][w - ws[i-1]] + ws[i-1];
				if (value[i][w] < val)
					value[i][w] = val;
			}
		}
	}

	return value[ws.size()][W];
}

int main() {
	int n, W;
	std::cin >> W >> n;
	vector<int> w(n);
	for (int i = 0; i < n; i++) {
		std::cin >> w[i];
	}
	std::cout << optimal_weight(W, w) << '\n';

	system("pause");
	return 0;
}
