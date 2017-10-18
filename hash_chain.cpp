#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct query {
	string s;
	size_t ind;
	vector<string> subS;
};

struct Query {
	string type, s;
	size_t ind;
};

class QueryProcessor {
	int bucket_count;
	// store all strings in one vector
	vector<string> elems;
	vector<query> que;
	size_t hash_function(const string&s) const
	{
		static const size_t multiplier = 263;
		static const size_t p = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; i--)
		{
			hash = (hash*multiplier + s[i]) % p;
		}
		return hash%bucket_count;
	}


public:
	explicit QueryProcessor(int bucket_count) : bucket_count(bucket_count) {}

	void processQuery()
	{
		que.resize(bucket_count);

		int n = 0; 
		cin >> n;
		string type;
		string temp;
		size_t index;
		for (int i = 0; i < n; i++)
		{
			
			cin >> type;
			
			if (type.compare("add") == 0)
			{				
				
				cin >> temp;
				index = hash_function(temp);			
				addString(que[index],temp);
			}
			else if (type.compare("check") == 0)
			{
				cin >> index;
				checkString(index);
			}
			else if(type.compare("find")==0)
			{
				//find string 
				cin >> temp;
				index = hash_function(temp);
				findString(index, temp);
			}
			else//del
			{
				cin >> temp;
				index = hash_function(temp);
				delString(index, temp);
			}
		}
	}
	
	void addString(query& address, string& s)
	{
		if (address.ind == 0)
		{
			address.s = s;
			address.ind++;
		}
		else
		{

			if(address.s.compare(s)!=0)
			{
				int i = 0;
				for (; i < address.ind - 1; i++)
				{
					if (address.subS[i].compare(s) == 0)
					{
						break;
					}
				}
				if (i == address.ind - 1)
				{
					address.subS.push_back(s);
					address.ind++;
				}
			}
		}
	}

	void checkString(size_t index)
	{
		if (que[index].ind == 0)
		{
			elems.push_back("");
		}
		else
		{
			string temp= que[index].s;

			for (int i = 0; i < que[index].ind - 1; i++)
				temp = temp + " " + que[index].subS[i];
			elems.push_back(temp);
		}
	}

	void delString(size_t index, string &s)
	{
		if (que[index].ind == 0)
			return;
		else
		{
			if (que[index].s.compare(s) == 0)
			{
				if (que[index].ind > 1)
				{
					int loc = que[index].ind - 2;
					que[index].s = que[index].subS[loc];
					que[index].ind--;
				}
				else
				{
					que[index].ind--;
				}
			}
			else
			{
				int i = 0;
				for (; i < que[index].ind - 1; i++)
				{
					if (que[index].subS[i].compare(s) == 0)
						break;
				}

				if (i == que[index].ind - 1)
					return;
				else
				{
					for (; i < que[index].ind - 2; i++)
					{
						que[index].subS[i] = que[index].subS[i + 1];
					}
					que[index].ind--;
				}
			}
		}
	}
	void findString(size_t index, string &s)
	{
		if (que[index].ind == 0)
			elems.push_back("no");
		else
		{
			if (que[index].s.compare(s) == 0)
				elems.push_back("yes");
			else
			{
				int i = 0; 
				for (; i < que[index].ind - 1; i++)
				{
					if (que[index].subS[i].compare(s) == 0)
						break;
				}
				if (i == que[index].ind - 1)
					elems.push_back("no");
				else
					elems.push_back("yes");
			}
		}

	}
	void outputQuery()
	{
		size_t length = elems.size();
		for (size_t i = 0; i < length; i++)
			std::cout << elems[i] << "\n";
	}

};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQuery();
	proc.outputQuery();
	//system("pause");
	return 0;
}
