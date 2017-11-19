#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

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

string InverseBWT(const string& bwt)
{
	string result;
	vector<char> first_row;
	for (int i = 0; i < bwt.size(); i++)
	{
		first_row.push_back(bwt[i]);
	}
	sort(first_row.begin(), first_row.end());

	int first_index, last_index, count;
	last_index = 0;

	for (int i = 0; i < bwt.size(); i++)
	{
		//locate the position of last column
		count = last_column_count(bwt, last_index);
		first_index = first_column_index(first_row, bwt, count, last_index);
		result += bwt[first_index];
		//cout << "count: " << count << " first_index: " << first_index << endl;
		last_index = first_index;
	}

	for (int i = 0; i <result.size(); i++)
	{
		if (result[i] == '$')
		{
			last_index = i;
			break;
		}
	}
	string ans;
	for (int i = last_index - 1; i >= 0; i--)
		ans = ans + result[i];
	for (int i = result.size() - 1; i >= last_index; i--)
		ans = ans + result[i];
	//ans = result.substr(last_index+1, result.size() - last_index-1) + result.substr(0, last_index)+'$';
	return ans;
}

int main() {
	string bwt;
	cin >> bwt;
	cout << InverseBWT(bwt) << endl;
	system("pause");
	return 0;
}
