/*
Find all occurrences of a pattern in a string
*/
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Function: compute prefix array of pattern
Output: prefix array
*/
vector<int> compute_prefix_array(const string& p)
{
	vector<int> prefix(p.size(), 0);

	int border = 0;
	int n = p.size();
	for (int i = 1; i < n; i++)
	{
		while (border > 0 && p[i] != p[border])
			border = prefix[border - 1];
		if (p[i] == p[border])
			border++;
		else
			border = 0;
		prefix[i] = border;
	}

	return prefix;
}
// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
	vector<int> result;	
	string combine_string = pattern + '$' + text;
	vector<int> prefix_array = compute_prefix_array(combine_string);

	int pattern_len = pattern.size();
	for (int i = pattern_len + 1; i < combine_string.size(); i++)
	{
		if (prefix_array[i] == pattern_len)
			result.push_back(i - 2 * pattern_len);
	}
	return result;
}

int main() {
	string pattern, text;
	cin >> pattern;
	cin >> text;
	vector<int> result = find_pattern(pattern, text);
	for (int i = 0; i < result.size(); ++i) {
		cout<<result[i]<<" ";
	}
	cout << endl;

	//system("pause");
	return 0;
}
