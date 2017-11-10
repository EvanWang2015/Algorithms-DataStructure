/*
Mutiple pattern searching probelm application

Input format:
	The first line of the input contains a string Text
	the second line contians an integer n
	each of the following n lines contains a pattern from Patterns.

Output Format:
	All starting positions in Text where a string from Patterns appears as a substring in increasing order. 

Author: Haitang Wang
TIme: 11/10/2017

Input example:
AATCGGGTTCAATCGGGGT
2
ATCG
GGGT

Output:
1 4 11 15
*/

#include <string>
#include <iostream>
#include <vector>
#include <map>


using namespace std;


struct TrieNode
{
	char ch;
	map<char, TrieNode*> children;
	bool word_end;
};

class Trie
{
private:
	int trie_size;
	TrieNode root;
	vector<TrieNode*> children;

public:
	void insert_node(const string& key);
	void build_trie(const vector<string>& words, int length);
	void search(const string& key, vector<int>& result);
	void print_trie(map<char, TrieNode*>& children);
	void print();

	Trie() :trie_size(0) {
		root.ch = '0';
	}
	~Trie()
	{
		for (int i = 0; i < trie_size; ++i)
		{
			delete children[i];
		}
		children.clear();
	}
};


void Trie::insert_node(const string& key)
{
	TrieNode* current = &root;
	map<char, TrieNode*>::iterator it;

	for (int i = 0; i < key.size(); i++)
	{
		it = current->children.find(key[i]);
		if (it != current->children.end())
		{
			if (i == key.size() - 1)
			{
				it->second->word_end = true;
			}
			current = it->second;

			continue;
		}
		else
		{
			TrieNode* new_node = new TrieNode;
			new_node->ch = key[i];
			trie_size++;
			current->children[key[i]] = new_node;
			current = new_node;
			children.push_back(new_node);
		}
	}
	children[trie_size - 1]->word_end = true;	
}

void Trie::build_trie(const vector<string>&words, int length)
{
	for (int i = 0; i < words.size(); i++)
	{
		insert_node(words[i]);
	}
}

void Trie::print_trie(map<char, TrieNode*>& children)
{
	if (children.empty())
	{
		return;
	}
	
	for (map<char, TrieNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		cout << it->first << endl;

		print_trie(it->second->children);
	}
}

void Trie::print()
{
	map<char, TrieNode*> current = root.children;
	print_trie(current);
}

void Trie::search(const string& key, vector<int>& result)
{
	

	for (int i = 0; i < key.size(); ++i)
	{

		map<char, TrieNode*> current = root.children;
		map<char, TrieNode*>::iterator it;
		bool pushed = false;
		for (int j = i; j < key.size(); j++)
		{
			it = current.find(key[j]);

			if (it == current.end())
				break;
			else
			{
				if (it->second->word_end == true)
				{
					//cout << "found: " << i << endl;
					if (!pushed)
					{
						result.push_back(i);
						pushed = true;
					}
					//break;

				}
				current = it->second->children;
			}
		}		
	}
}

vector <int> solve(const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

	Trie t;
	t.build_trie(patterns, n);
	//t.print();
	t.search(text, result);
	//cout << "size: " << result.size() << endl;
	return result;
}

int main(void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve(t, n, patterns);

	for (int i = 0; i < (int)ans.size(); i++)
	{
		cout << ans[i];
		if (i + 1 < (int)ans.size())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	system("pause");
	return 0;
}