/*
Constuct a Suffix Tree of a String

Input: A string text ending with a "$" symbol.

output: The strings labeling the edges of SuffixTree() in any order.

Author: Haitang Wang

*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>


using namespace std;

struct Node
{
	int start_;
	int length_;
	map<char, Node*> children;
};

class SuffixTree
{
private:
	Node root;
	vector<Node*> allNodes;
public:
	int tree_size;
	SuffixTree():tree_size(0){ }
	~SuffixTree()
	{
		for (int i = 0; i < allNodes.size(); i++)
			delete allNodes[i];
	}
public:
	void insert_node(const string& key, int start_);
	void build_trie(const string& key);
	void print_trie(Node* current, const string& key);
	void print(const string& key);
	void easy_print(const string& key);
	
};

void SuffixTree::insert_node(const string&key, int start_)
{
	Node* current = &root;
	map<char, Node*> ::iterator it;
	for (int i = start_; i < key.size(); i++)
	{
		it = current->children.find(key[i]);

		//start a new node
		if (it == current->children.end())
		{
			Node* new_node = new Node;
			new_node->start_ = i;
			new_node->length_ = key.size() - i;
			allNodes.push_back(new_node);
			current->children[key[i]] = new_node;
			tree_size++;
			return;
		}
		//already exists
		else if (it != current->children.end() && it->second->length_ == 1)
		{
			current = it->second;
			continue;
		}
		else if (it != current->children.end() && it->second->length_ > 1)
		{
			int k = 0;
			while (k < it->second->length_ && key[it->second->start_ + k] == key[i + k])
			{
				k++;
				if (k == it->second->length_)
				{
					current = it->second;
					i = i + k - 1;
					continue;
				}

			}
		
			//in this case, we need to split the old node 
			if (k < it->second->length_)
			{
				Node* new_node = new Node;
				new_node->start_ = it->second->start_ + k;
				new_node->length_ = it->second->length_ - k;
				
				it->second->length_ = k;
				current = it->second;
				current->children[key[new_node->start_]] = new_node;
				tree_size++;
				allNodes.push_back(new_node);
				

				//insert a new node 
				Node* new_node2 = new Node;
				new_node2->start_ = i + k;
				new_node2->length_ = key.size() - i - k;
				current->children[key[new_node2->start_]] = new_node2;
				tree_size++;
				allNodes.push_back(new_node2);
				return;
			}	
		}
	}
}

void SuffixTree::build_trie(const string& key)
{
	for (int i = key.size()-1; i >=0; i--)
	{
		insert_node(key, i);
	}
}

void SuffixTree::easy_print(const string& key)
{
	for (int i = 0; i < allNodes.size(); i++)
		cout << key.substr(allNodes[i]->start_, allNodes[i]->length_) << endl;

	//cout << tree_size << endl;
}

void SuffixTree::print_trie(Node* current, const string& key)
{
	if (current == nullptr)
	{
		return;
	}
	for (map<char, Node*> ::iterator it = current->children.begin(); it != current->children.end(); it++)
	{
		string out_put;
		for (int i = 0; i < it->second->length_; i++)
			out_put = out_put + key[i+it->second->start_];
		cout <<out_put << endl;
		print_trie(it->second, key);
	}
}

void SuffixTree::print(const string &key)
{
	print_trie(&root, key);
}

vector<string> ComputeSuffixTreeEdges(const string& text) {
	vector<string> result;
	// Implement this function yourself
	SuffixTree ST;
	ST.build_trie(text);
	//cout << ST.tree_size << endl;
	//ST.easy_print(text);
	ST.print(text);
	return result;
}

int main() {
	string text;
	cin >> text;
	vector<string> edges = ComputeSuffixTreeEdges(text);
	for (int i = 0; i < edges.size(); ++i) {
		cout << edges[i] << endl;
	}
	system("pause");
	return 0;
}
