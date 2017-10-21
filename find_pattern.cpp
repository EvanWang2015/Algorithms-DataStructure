/*
Find pattern in text using Rabin-Karp's Algorithm

In order to reduce the time complexity, dynamic programming is applied to precompute the hash value of strings. 
*/

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
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


long long PolyHash(const string& s, int p, int x)
{
	long long hash = 0;

	for (int i = s.size() - 1; i >= 0; i--)
		hash = (hash*x + s[i]) % p;
	return hash;
}

bool AreEqual(const string& s1, const string& s2, int startP)
{
	for (int i = 0; i <= s2.size() - 1; i++)
	{
		if (s1[i + startP] != s2[i])
			return false;
	}
	return true;
}

vector<long long> PrecomputeHashes(const string& T, int length, int prime, int x)
{
	vector<long long> H(T.size() - length + 1);

	string s = T.substr(T.size() - length, length);
	//std::cout << "s: " << s << std::endl;

	H[T.size() - length] = PolyHash(s, prime, x);

	long long y = 1;
	for (int i = 1; i <= length; i++)
		y = (y*x) % prime;

	//std::cout << H.size() << " H size" << std::endl;
	for (int i = T.size() - length - 1; i >= 0; i--)
	{
		H[i] = (x*H[i + 1] + T[i] - y*T[i + length]) % prime;
	}
	return H;
}

vector<int> RabinKarp(const string & T, const string& P)
{
	vector<int> ans;
	long long p = prime;
	int x = 263;

	long long pHash = PolyHash(P, p, x);

	vector<long long> H = PrecomputeHashes(T, P.size(), p, x);

	for (int i = 0; i <= T.size() - P.size(); i++)
	{
		if (pHash == H[i])
		{
			if (AreEqual(T, P, i))
			{
				ans.push_back(i);
			}
		}
	}
	return ans;
}


void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}


int main() {
	std::ios_base::sync_with_stdio(false);

	Data data = read_input();
	//vector<int> ans = RabinKarp(data.text, data.pattern);
	//std::cout << ans.size();
	print_occurrences(RabinKarp(data.text, data.pattern));
	//print_occurrences(get_occurrences(read_input()));
	//system("pause");
	return 0;
}
