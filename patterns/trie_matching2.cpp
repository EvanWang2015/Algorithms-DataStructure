#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int const Letters = 4;
int const NA = -1;

struct Node
{
	vector<Node*> next;
	char ch;
	bool word_end;
	Node()
	{
		next.resize(Letters);
		next.assign(Letters, nullptr);
		word_end = false;
	}

	bool isLeaf() const
	{
		return (next[0] == nullptr && next[1] == nullptr && next[2] == nullptr && next[3] == nullptr);
	}
};

int letterToIndex(char letter)
{
	switch (letter)
	{
	case 'A': return 0; break;
	case 'C': return 1; break;
	case 'G': return 2; break;
	case 'T': return 3; break;

	default: assert(false); return -1;
	}
}

class Trie
{
private:
	int trie_size;
	Node root;
	vector<Node*> allNodes;
public:
	Trie()
	{
		trie_size = 0;
	}
	~Trie()
	{
		for (int i = 0; i < trie_size; i++)
		{
			delete allNodes[i];
		}
		allNodes.clear();
		trie_size = 0;
	}
	void insert_node(const string& key);
	void build_trie(const vector<string>& patterns);
	void print_trie(Node* children);
	void print();
	void search(const string& key, vector<int>& result);
};

void Trie::insert_node(const string& key)
{
	Node* current = &root;
	
	for (int i = 0; i < key.size(); i++)
	{
		int index = letterToIndex(key[i]);
		if (current->next[index] != nullptr)
		{
			if (i == key.size() - 1)
			{
				current->next[index]->word_end = true;
				//break;
				//cout << "did it happen" << index << endl;;
			}
			current = current->next[index];
			
		}
		else
		{
			Node* new_node = new Node;
			if (i == key.size() - 1)
			{
				new_node->word_end = true;
			}
			new_node->ch = key[i];
			trie_size++;
			current->next[index] = new_node;
			current = current->next[index];
			allNodes.push_back(new_node);
		}
	}
}

void Trie::build_trie(const vector<string>& patterns)
{
	int n = patterns.size();
	for (int i = 0; i < n; i++)
	{
		insert_node(patterns[i]);
	}
}

void Trie::print_trie(Node* current)
{
	if (current->isLeaf())
	{
		return;
	}

	for (vector<Node*>::iterator it = current->next.begin(); it != current->next.end(); it++)
	{
		if ((*it) != nullptr)
		{
			cout << (*it)->ch << endl;
			print_trie(*it);
		}
	}
}

void Trie::print()
{
	print_trie(&root);
}

void Trie:: search(const string& key, vector<int>& result)
{
	int n = key.size();
	for (int i = 0; i < n; i++)
	{
		Node* current = &root;
		bool flag = false;
		for (int k = i; k < n; k++)
		{
			int j = letterToIndex(key[k]);
			if (current->next[j] != nullptr)
			{
				if (current->next[j]->word_end==true)
				{
					if (!flag)
					{
						result.push_back(i);
						flag = true;
					}					
				}
				current = current->next[j];
			}
			else
				break;
		}		
	}

	//cout << result.size() << endl;
}
vector<int> solve(const string& text, int n, const vector<string>& patterns)
{
	vector<int> result;

	Trie t;
	t.build_trie(patterns);
	//t.print();
	t.search(text, result);
	return result;
}
int main(void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns(n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve(text, n, patterns);

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