/*------------------------------------------------
Build a trie for a collection of string patterns.

Definition:
	The trie has a single root node with degree 0;
	Each edge of Trie is labled with a letter of the alphabet
	Edges leading out of a given node have distinct lables
	Every string in patterns is spelled out by concatenating the letters along some path from the root downward
	Every path from the root to a leaf, spells a string from Patterns.

Input format:
	An integer n and a collection of strings Patterns (each string is given on a separate line).
Constraints:
	strings only contain symbols of A, C, G, T
output: 
	parent ->current node index: label(A/C/G/T)

Author: Haitang Wang
Reference souce1: https://gist.github.com/reterVision/8487831
Reference source2: http://www.geeksforgeeks.org/trie-insert-and-search/
-------------------------------------------------*/
#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef map<char, int> edges;
typedef vector<edges> trie;

const int ALPHABET_SIZE = 4;

//struct trie node
struct TrieNode
{
	//struct TrieNode *children[ALPHABET_SIZE];
	char ch;
	map<char, TrieNode*> children;
	int index;
	int parent_index;

};

//return a new trie node (initialize a 
class Trie
{
private:
	int trie_size;
	TrieNode root;
	vector<TrieNode*> children;
public:
	void insert_node(string key);
	void build_trie(vector<string>& words, int length);
	bool search(string key);
	void print_trie(map<char, TrieNode*> children);
	void print();
	Trie() :trie_size(0) {
		root.ch = '0';
		root.parent_index = -1;
		root.index = 0;
	};
	~Trie()
	{
		for (int i = 0; i < children.size(); ++i)
		{
			delete children[i];
		}
		children.clear();
	}
};

void Trie::insert_node(string key)
{
	TrieNode* current = &root;
	map<char, TrieNode*>::iterator it;

	for (int i = 0; i < key.size(); ++i)
	{
		it = current->children.find(key[i]);
		if (it != current->children.end())
		{
			current = it->second;
			continue;
		}
		else
		{
			TrieNode* new_node = new TrieNode;
			new_node->ch = key[i];
			new_node->index = ++trie_size;
			new_node->parent_index = current->index;
			current->children[key[i]] = new_node;
			current = new_node;
			children.push_back(new_node);
			
		}
	}
}

bool Trie::search(string word)
{
	map<char, TrieNode*> current = root.children;
	map<char, TrieNode*> ::iterator it;

	for (int i = 0; i < word.size(); ++i)
	{
		it = current.find(word[i]);
		if (it == current.end())
		{
			return false;
		}
		else
		{
			current = it->second->children;
		}
	}
	return true;
}

void Trie::build_trie(vector<string>& words, int length)
{
	for (int i = 0; i < words.size(); i++)
	{
		insert_node(words[i]);
	}
}

void Trie::print_trie(map<char, TrieNode*> children)
{
	
	if (children.empty())
	{
		return;
	}

	for (map<char, TrieNode*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		cout << it->second->parent_index<<"->"<<it->second->index <<":"<< it->first << endl;
		print_trie(it->second->children);
	}
}

void Trie::print()
{
	map<char, TrieNode*> current = root.children;
	print_trie(current);
}

//if the node is not present yet, insert key into trie
//if the key is prefix of trie node, just marks leaf node


int main() {
	size_t n;
	std::cin >> n;
	vector<string> patterns;
	for (size_t i = 0; i < n; i++) {
		string s;
		std::cin >> s;
		patterns.push_back(s);
	}

	Trie t;
	t.build_trie(patterns, patterns.size());
	t.print();
	/*for (size_t i = 0; i < t.size(); ++i) {
		for (const auto & j : t[i]) {
			std::cout << i << "->" << j.second << ":" << j.first << "\n";
		}
	}*/
	//system("pause");
	return 0;
}