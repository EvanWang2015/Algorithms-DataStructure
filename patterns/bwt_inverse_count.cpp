#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

void merge(vector<char>& arr, int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/*creat temp arrays*/
	vector<char> L(n1);
	vector<char> R(n2);

	for ( i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for ( i = 0; i < n2; i++)
		R[i] = arr[m + 1 + i];

	/*merge the temp arrays back into arr[l..r]*/
	// k = l; // Initial index of merged subarray
	i = 0; 
	j = 0;
	k = l;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	
	while (i < n1)
	{
		arr[k] = L[i];
		k++;
		i++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		k++;
		j++;
	}
}

void merge_sort(vector<char>& arr, int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}


/*
-------------------------------
Counting sort algorithm for the first column 
build first column 
*/

void build_first_column(const string& bwt, vector<char>& first_column, unordered_map<char,int>& first_appear)
{
	int n = bwt.size();
	map<char, int> count;
	map<char, int> ::iterator it;
	for (int i = 0; i < n; i++)
	{
		it = count.find(bwt[i]);
		if (it != count.end())
			it->second += 1;
		else
			count[bwt[i]] = 1;
	}

	int i = 0;
	for (it = count.begin(); it != count.end(); it++)
	{
		int j = it->second;
		first_appear[it->first] = i;
		i = i + it->second;
		while (j > 0)
		{
			first_column.push_back(it->first);
			j--;
		}
	}
}

string InverseBWT_naive(const string& bwt) {
	string text = "";
	int n = bwt.size();
	vector<string> BWT_inverse_matrix(n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			string temp;
			temp = bwt[j] + BWT_inverse_matrix[j];
			BWT_inverse_matrix[j] = temp;
		}
		sort(BWT_inverse_matrix.begin(), BWT_inverse_matrix.end());
	}
	text = BWT_inverse_matrix[0].substr(1,n-1);
	text = text + BWT_inverse_matrix[0].substr(0, 1);
	return text;
}

int last_column_count(const string& last_column, int index)
{
	//according to the location at the last column
	int count = 0;
	for (int i = 0; i <= index; i++)
	{
		if (last_column[i] == last_column[index])
			count++;
	}
	return count;
}

int first_column_index(vector<char>& first_column, const string& bwt, int count, int index)
{
	int result = 0;
	for (int i = 0; i < first_column.size() && count>0; i++)
	{
		if (first_column[i] == bwt[index])
			count--;
		result = i;
	}
	return result;
}

int first_column_index_firstOccurrence(vector<char>& first_column, const string& bwt, int count, int index, int start)
{
	int result = 0;
	int n = first_column.size();
	for (int i = start; i < n && count>0; i++)
	{
		if (first_column[i] == bwt[index])
			count--;
		result = i;
	}
	return result;
}

void last_to_first(vector<char>& first_column, const string& last_column, unordered_map<char, int>& first_appear, vector<int>& ans)
{
	unordered_map<char, int> pre_count;
	int n = first_column.size();
	//vector<int> ans;// (n);
	int count = 0;
	unordered_map<char, int>::iterator it;

	for (int i = 0; i < n; i++)
	{
		it = pre_count.find(last_column[i]);
		if (it != pre_count.end())
		{
			it->second += 1;
			
			//ans.push_back(first_column_index_firstOccurrence(first_column, last_column, it->second, i, first_appear[last_column[i]]));

			//without loop through the list, this way gives the index vlaue directly. 
			ans.push_back(first_appear[last_column[i]] + it->second-1);
		}			
		else
		{
			pre_count[last_column[i]] = 1;
			//ans.push_back(first_column_index_firstOccurrence(first_column, last_column, 1, i, first_appear[last_column[i]]));
			ans.push_back(first_appear[last_column[i]]);
		}
	}

}

string InverseBWT_count(const string&bwt)
{
	vector<char> result;
	int n = bwt.size();
	vector<char> first_row;
	unordered_map<char, int> first_appear; //A C G T

	build_first_column(bwt, first_row, first_appear);

	vector<int> lastToFirst;
	
	unordered_map<char, int>::iterator it; //A C G T

	last_to_first(first_row, bwt, first_appear, lastToFirst);
	
	
	int last_index = 0;
	int temp=0; //indicating location of '$'
	//result.resize(n);
	for (int i = 0; i < n; i++)
	{
		//locate the position of last column
		//result += bwt[lastToFirst[last_index]];
		result.push_back(bwt[lastToFirst[last_index]]);
		//result.append(bwt[lastToFirst[last_index]]);
		if (bwt[lastToFirst[last_index]] == '$')
			temp = i;

		last_index = lastToFirst[last_index];

	}
		
	string ans;
	
	for (int i = temp - 1; i >= 0; i--)
		//ans = ans + result[i];
		cout << result[i];
	for (int i =n - 1; i >= temp; i--)
		//ans = ans + result[i];
		cout << result[i];
	
	return ans;
}

int main() {
	string bwt;
	cin >> bwt;
	cout << InverseBWT_count(bwt) << endl;
	//cout << InverseBWT(bwt) << endl;
	system("pause");
	return 0;
}
