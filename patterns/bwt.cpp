/*
Construct Burrows-Wheeler Transform of a String
input format: A string text ending with a "$" symbol
output format: BWT(text)
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
	string result = "";
	vector<string> BWT_Matrix;
	int n = text.size();
	for (int i = 0; i < n; i++)
	{
		string temp;
		for (int j = i; j < n; j++)
		{
			temp += text[j];
		}

		for (int j = 0; j < i; j++)
		{
			temp += text[j];
		}
		BWT_Matrix.push_back(temp);
	}
	
	sort(BWT_Matrix.begin(), BWT_Matrix.end());
	
	
	for (int i = 0; i < n; i++)
		result += BWT_Matrix[i].at(n - 1);

	return result;
}

int main() {
	string text;
	cin >> text;
	cout << BWT(text) << endl;
	//system("pause");
	return 0;
}