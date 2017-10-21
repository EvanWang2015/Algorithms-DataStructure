#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;
static const long long prime = 10000007;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

long long PolyHash(const string& s, int startL, int endL)
{
	static const long long multiplier = 10;
	long long hash = 0;

	for (int i = startL; i <=endL; i++)
	{
		//hash = (hash*multiplier + s[i]) % prime;
		hash = (hash + s[i])%prime;
	}
	return hash;
}


void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}

bool isEqual(const Data& input, int startL)
{
	for (int i = 0; i < (input.pattern).size(); i++)
	{
		if (input.pattern[i] != input.text[i + startL])
		{
			return false;
		}
	}
	return true;
}

std::vector<int> get_occurrences(const Data& input) {
	const string& s = input.pattern, t = input.text;
	long long value_pattern = PolyHash(input.pattern, 0, input.pattern.size() - 1);
	long long target_hash = PolyHash(t, 0, s.size() - 1);
	int pattern_size = input.pattern.size();
	std::vector<int> ans;

	//std::cout << value_pattern << " "<<pattern_size<<std::endl;
	//std::cout << PolyHash("text", 0, 3) << " " << PolyHash("Text", 0, 3) << std::endl;
	for (size_t i = 0; i + pattern_size <=t.size(); i++)
	{
		if (i != 0)
		{
			target_hash = (target_hash - t[i-1] + t[i + pattern_size-1]);
		}
		int flag = false;
		//std::cout << "i: " << i << " " << target_hash << std::endl;
		if (target_hash == value_pattern)
		{
			flag = isEqual(input, i);
		}
		
		if (flag==true)
			ans.push_back(i);
	}
	//for (size_t i = 0; i + s.size() <= t.size(); ++i)
		//if (t.substr(i, s.size()) == s)
			//ans.push_back(i);
	return ans;
}


int main() {
	std::ios_base::sync_with_stdio(false);
	print_occurrences(get_occurrences(read_input()));
	//system("pause");
	return 0;
}
