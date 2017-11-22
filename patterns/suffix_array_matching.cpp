/*

Problem: use the suffix array to solve the multiple pattern matching problem. This is what actually
happens when one needs to solve the pattern matching problem for a massive string like the human genome:
instead of downloading the genome itself, one downloads its suffix array and solves the pattern matching
problem using the array.

Task: find all occurrence of a givencollection of patterns in a string.

Key points: 
1) Suffix array: holds starting position of each suffix beginning a row.
2) To get the suffix array, counting sort is used. 
3) with suffix array, then use binary search to locate start and end indexes.

Author: Haitang Wang

Sample input: 
ATATATA
3
ATA C TATAT
Output:
4 2 0 1

Another example input:
ATA
3
C G C
Output:
//{empty}
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

/*
Sort characters with simple counting algorithm.
The size of count is the number of |Sigma|.
*/
vector<int> sort_characters(const string& text)
{
	int n = text.size();
	vector<int> order(n);
	map<char, int> count;
	map<char, int>::iterator it;
	for (int i = 0; i < n; i++)
	{
		it = count.find(text[i]);
		if (it != count.end())
		{
			it->second++;
		}
		else
			count[text[i]] = 1;
	}

	map<char, int> ::iterator itt = count.begin();
	for (it = ++(count.begin()); it != count.end(); it++)
	{
		it->second += itt->second;
		itt++;
	}

	for (int i = n - 1; i >= 0; i--)
	{
		count[text[i]] = count[text[i]] - 1;
		order[count[text[i]]] = i;
	}

	return order;
}

vector<int> compute_char_classes(const string& text, vector<int>& order)
{
	int n = text.size();
	vector<int> classes(n);
	classes[order[0]] = 0;

	for (int i = 1; i < n; i++)
	{
		if (text[order[i]] != text[order[i - 1]])
			classes[order[i]] = classes[order[i - 1]] + 1;
		else
			classes[order[i]] = classes[order[i - 1]];
	}

	/*for (int i = 0; i < n; i++)
		cout << classes[i] << " ";*/

	return classes;
}

vector<int> sort_doubled(const string& text, int L, vector<int>& order, vector<int>& classes)
{
	int n = text.size();
	vector<int> count(n, 0);
	vector<int> new_order(n);

	for (int i = 0; i < n; i++)
		count[classes[i]] = count[classes[i]] + 1;

	for (int j = 1; j < n; j++)
		count[j] += count[j - 1];

	int start;
	for (int i = n - 1; i >= 0; i--)
	{
		start = (order[i] - L + n) % n;
		count[classes[start]] += -1;
		new_order[count[classes[start]]] = start;
	}

	return new_order;
}

vector<int> update_classes(vector<int>& new_order, vector<int>& classes, int L)
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

/*
Suffix array holds starting position of each suffix beginning a row. 
*/
vector<int> BuildSuffixArray(const string& text) {

	vector<int> order = sort_characters(text);
	vector<int> classes = compute_char_classes(text, order);
	
	int L = 1;
	int n = text.size();
	while (L < n)
	{
		order = sort_doubled(text, L, order, classes);
		classes = update_classes(order, classes, L);
		L = 2 * L;
	}

	/*for (int i = 0; i < n; i++)
		cout << order[i] << " ";*/
	return order;
}

bool pattern_suffix_array_compare_greater(const string& pattern, const string& text, const vector<int>& suffix_array, int index)
{
	int i = 0;
	int n = text.size();
	while (i < pattern.size() && (suffix_array[index] + i)<n)
	{
		if (pattern[i] > text[suffix_array[index] + i])
			return true;
		else if (pattern[i] < text[suffix_array[index] + i])
			return false;
		else //equal
			i++;
	}
	
	return false;
}

bool pattern_suffix_array_compare_smaller(const string& pattern, const string& text, const vector<int>& suffix_array, int index)
{
	int i = 0;
	int n = text.size();
	while (i < pattern.size() && (suffix_array[index] + i)<n)
	{
		if (pattern[i] < text[suffix_array[index] + i])
			return true;
		else if (pattern[i] > text[suffix_array[index] + i])
			return false;
		else //equal
			i++;
	}

	if (i==text.size())
		return true;
	else
		return false;
}

bool pattern_suffix_isequal(const string& pattern,int start, const string& text)
{
	int n = pattern.size();
	for (int i = 0; i < n; i++)
	{
		if (text[i + start] != pattern[i])
			return false;
	}
	return true;
}

vector<int> FindOccurrences(const string& pattern, const string& text, const vector<int>& suffix_array) {
	vector<int> result;

	int min_index = 0;
	int max_index = text.size();

	while (min_index < max_index)
	{
		int middle_index = (min_index + max_index) / 2;
		if (pattern_suffix_array_compare_greater(pattern, text, suffix_array, middle_index))
			min_index = middle_index + 1;
		else
			max_index = middle_index;
	}

	int start = min_index;
	max_index = text.size();

	while(min_index < max_index)
	{
		int middle_index = (min_index + max_index) / 2;
		if (pattern_suffix_array_compare_smaller(pattern, text, suffix_array, middle_index))
		{
			max_index = middle_index;
		}
		else
			min_index = middle_index + 1;
	}

	int end = max_index;

	if (end == text.size())
		end = end - 1;

	for (int i = start; i <= end; i++)
	{
		//if (text[suffix_array[i]] != '$' && text[suffix_array[i]]==pattern[0])
		if (i == end)
		{
			if (pattern_suffix_isequal(pattern, suffix_array[i], text))
			{
				result.push_back(suffix_array[i]);
			}
		}
		else
			result.push_back(suffix_array[i]);
	}

	//cout << "start: "<<start << " " << "end: " << end << endl;
	return result;
}

int main() {
	char buffer[100001];
	cin >> buffer;
	string text = buffer;
	text += '$';
	vector<int> suffix_array = BuildSuffixArray(text);
	int pattern_count;
	cin >> pattern_count;
	vector<bool> occurs(text.length(), false);
	for (int pattern_index = 0; pattern_index < pattern_count; ++pattern_index) {
		cin >> buffer;
		string pattern = buffer;
		vector<int> occurrences = FindOccurrences(pattern, text, suffix_array);
		for (int j = 0; j < occurrences.size(); ++j) {
			occurs[occurrences[j]] = true;
		}
	}
	for (int i = 0; i < occurs.size(); ++i) {
		if (occurs[i]) {
			cout<<i<<" ";
		}
	}
	cout << endl;
	
	system("pause");
	return 0;
}
