/*
Calculate suffix array for a long string

If we store suffix array the total length of all suffixes is 1 + 2 + ... + |S| = O(S^2).
Store them all is too memory expensive.

Instead, we use general construction strategy: sorting partial cyclic shifts.

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
using namespace std;

/* ---------------------------------------------------------
Running sort characters is O(|S| + |Sigma|),
where |Sigma| is the number of different characters. 
*/
vector<int> sort_characters(const string& s)
{
	vector<int> order(s.size());
	map<char, int> count;
	map<char, int>::iterator it;
	map<char, int>::iterator itt;
	int n = s.size();

	for (int i = 0; i < n; i++)
	{
		it = count.find(s[i]);
		if (it != count.end())
			it->second++;
		else
			count[s[i]] = 1;
	}
	
	itt = count.begin();
	for (it = ++(count.begin()); it != count.end(); it++)
	{
		it->second = itt->second + it->second;
		itt++;
	}

	for (int i = n - 1; i >= 0; i--)
	{
		count[s[i]] = count[s[i]] - 1;
		order[count[s[i]]] = i;
	}

	return order;
}

/*
Compute char classes 
Runing time is O(|S|)
*/
vector<int> compute_char_classes(const string& s, vector<int>& order)
{
	vector<int> classes(s.size());
	classes[order[0]] = 0;
	int n = s.size();
	for (int i = 1; i < n; i++)
	{
		if (s[order[i]] != s[order[i - 1]])
			classes[order[i]] = classes[order[i - 1]] + 1;
		else
			classes[order[i]] = classes[order[i - 1]];
	}
	return classes;
}

/*
Sort paris: 
1) first sort by second element of pair
2) then use stable sort by first element of pair
*/
vector<int> sort_doubled(const string& s, int L, vector<int>& order, vector<int>& classes)
{
	int n = s.size();
	vector<int> count(n, 0);
	vector<int> new_order(n);

	for (int i = 0; i < n; i++)
	{
		count[classes[i]] = count[classes[i]] + 1;
	}

	for (int j = 1; j < n; j++)
	{
		count[j] = count[j] + count[j - 1];
	}

	for (int i = n - 1; i >= 0; i--)
	{
		int start = (order[i] - L + n) % n;
		count[classes[start]] = count[classes[start]] - 1;
		new_order[count[classes[start]]] = start;
	}
	return new_order;
}

vector<int> update_classes(vector<int> new_order, vector<int>&classes, int L)
{
	int n = new_order.size();
	vector<int> new_class(n);

	new_class[new_order[0]] = 0;

	int cur, prev, mid, mid_prev;
	for (int i = 1; i < n; i++)
	{
		cur = new_order[i];
		prev = new_order[i - 1];
		mid = (cur + L) % n;
		mid_prev = (prev + L) % n;

		if (classes[cur] != classes[prev] || classes[mid] != classes[mid_prev])
		{
			new_class[cur] = new_class[prev] + 1;
		}
		else
			new_class[cur] = new_class[prev];
	}
	return new_class;
}
// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {

	vector<int> order = sort_characters(text);
	vector<int> classes = compute_char_classes(text, order);
	int L = 1, n = text.size();
	while (L < n)
	{
		order = sort_doubled(text, L, order, classes);
		classes = update_classes(order, classes, L);
		L = 2 * L;
	}
	return order;
}

int main() {
	string text;
	cin >> text;
	vector<int> suffix_array = BuildSuffixArray(text);
	for (int i = 0; i < suffix_array.size(); ++i) {
		cout << suffix_array[i] << ' ';
	}
	cout << endl;

	//system("pause");
	return 0;
}
