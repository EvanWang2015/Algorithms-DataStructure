/*
To add parentheses to a given arithmetic expression to maximize its value.

Task: find the maximum value of an arithmetic expression by specifying the order of applying its arithmetric operations using additional parentheses.

Input format: the only line of the input contains string s of length 2n+1 for some n, with symbols s0, s1,..., s2n. Each symbol at an even position of s is a digit 
while each symbol at an odd position is one of three operations from {+, -, *}
*/

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;

/*
Return operation with an unknown operator given by expression char
*/
long long eval(long long a, long long b, char op) {
	if (op == '*') {
		return a * b;
	}
	else if (op == '+') {
		return a + b;
	}
	else if (op == '-') {
		return a - b;
	}
	else {
		assert(0);
	}
}

/*
Input: start position i, end position j, string expression s, maximum vector M, minimum vector m

Algorithms:
MinAndMax is used to find the maximum and minimum values of the subexpression.
M(i,j) = max {M(i,k) op M(k+1,j), 
			  M(i,k) op m(k+1,j),
			  m(i,k) op m(k+1,j),
			  m(i,k) op M(k+1,j)}, where i<=k<=j-1
similarily, m(i,j) is also calcuated with the same approach.

Return: values of min and max, encapsulated in a vector.
Author: Evan Wang
Time: 10/11/2017
*/
vector<long long> MinAndMax(int i, int j, const string &exp, vector< vector <int>> &M, vector< vector<int>> &m)
{
	long long min_v = LLONG_MAX;
	long long max_v = LLONG_MIN;
	vector<long long> val(4);
	for (int k = i; k < j; k++)
	{
		char op = exp.at(2*k+1);
		//std::cout << " "<<op<<" ";
		val[0] = eval(M[i][k], M[k + 1][j], op);
		val[1] = eval(M[i][k], m[k + 1][j], op);
		val[2] = eval(m[i][k], M[k + 1][j], op);
		val[3] = eval(m[i][k], m[k + 1][j], op);
		
		for (int ii = 0; ii < 4; ii++)
		{
			min_v = std::min(min_v, val[ii]);
			max_v = std::max(max_v, val[ii]);
		}
	}

	vector<long long> res;
	res.push_back(min_v);
	res.push_back(max_v);

	return res;
}

/*
Gradually increasing the length of subexpression i, j
Computing M(i,j), the values of M(i,k) and M(k+1,j) are already given.
*/
long long get_maximum_value(const string &exp) {
	
	int n = (exp.size() + 1)/2;

	vector< vector<int>> M(n, vector<int>(n)), m(n, vector<int>(n));

	for (int i = 0; i < n; i++)
	{
		int j = i*2;
		M[i][i] = exp.at(j) - '0';
		m[i][i] = M[i][i];
		//std::cout << M[i][i] << " ";
	}
	//std::cout << std::endl;

	for (int s = 1; s <=n-1; s++)
	{
		for (int i = 0; i <n-s; i++)
		{
			int j =  i+s;
			//std::cout << i << " " << j<<" ";
			vector<long long> res = MinAndMax(i, j, exp, M, m);
			m[i][j] = res[0];
			M[i][j] = res[1];
			//std::cout << m[i][j] << " " << M[i][j] << std::endl;
		}
	}
	
	return M[0][n-1];
}

int main() {
	string s;
	std::cin >> s;
	std::cout << get_maximum_value(s) << '\n';
	system("pause");
	return 0;
}
