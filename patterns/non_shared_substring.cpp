/*
Find the shortest non-shared substring of two strings. 

Input: Strings Text1 and Text2
Output: the shortest (non-empty) substring of Text1 that does not appear in Text2. 

Author: Haitang Wang

Description: 

1) Generalized SuffixTree is built for Text1#Text2$
2) Find leaves whose string start from text1 while end with $ sign; AND find nodes only appear in Text1
3) Read

*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <queue>
#include <algorithm>
using namespace std;

struct Node
{
	int start_;
	int length_;
	int left;
	map<char, Node*> children;
	Node* parent;
	Node()
	{
		length_ = 0;
		start_ = 0;
		left = 0;
		parent = NULL;
	}
	
};

class SuffixTree
{
private:
	Node root;
	vector<Node*> allNodes;
public:
	int tree_size;
	SuffixTree() :tree_size(0) { }
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
	void shortest_non_shared_substring(const string&key, int last);
	void print_parent(Node* current, const string&key);
	void marker(Node* current, int last, int final, vector<Node*>& leftNodes, vector<bool>& leaves);
	void marker_start(int last, int final, vector<Node*>& leftNodes, vector<bool>& leaves);
	string traverse_leftNode(Node* current, const string& key, bool leaf);
	vector<string> substrings_leftNodes_to_root(const string&key, vector<Node*>& lastNodes, vector<bool>& left_leaves);
	int shortest_non_shared_string(vector<string>& left_strings);
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
			new_node->parent = current;
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
				new_node->parent = current;
				tree_size++;
				allNodes.push_back(new_node);


				//insert a new node 
				Node* new_node2 = new Node;
				new_node2->start_ = i + k;
				new_node2->length_ = key.size() - i - k;
				new_node2->parent = current;
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
	for (int i = key.size() - 1; i >= 0; i--)
	{
		insert_node(key, i);
	}
	root.parent = NULL;
}

void SuffixTree::easy_print(const string& key)
{
	for (int i = 0; i < allNodes.size(); i++)
	{
		cout << key.substr(allNodes[i]->start_, allNodes[i]->length_);
		if (allNodes[i]->parent != NULL)
		{
			cout << "its parent: "<<key.substr(allNodes[i]->parent->start_, allNodes[i]->parent->length_);
		}

		cout << "left: "<<allNodes[i]->left<<endl;
	}
		
}

void SuffixTree::print_parent(Node* current, const string& key)
{
	if (current == nullptr)
	{
		return;
	}

	for (map<char, Node*> ::iterator it = current->children.begin(); it != current->children.end(); it++)
	{
		string out_put;
		for (int i = 0; i < it->second->length_; i++)
			out_put = out_put + key[i + it->second->start_];
		

		string parent_out;
		if (it->second->parent != NULL)
		{
			for (int i = 0; i < it->second->parent->length_; i++)
			{
				parent_out = parent_out + key[i + it->second->parent->start_];
			}
		}
		cout << out_put << " and its parent: "<<parent_out<<endl;
		print_trie(it->second, key);
	}
}

void SuffixTree::marker (Node* current, int last, int final, vector<Node*>& leftNodes, vector<bool>& leaves)
{
	if (current == nullptr)
		return;

	for (map<char, Node*>::iterator it = current->children.begin(); it != current->children.end(); it++)
	{
		marker(it->second, last, final, leftNodes, leaves);
		if (it->second->start_ + it->second->length_ < last)
		{
			it->second->left = 1;
			leftNodes.push_back(it->second);
			leaves.push_back(false);
		}
		else
		{
			if (it->second->start_ < last-1 && (it->second->start_ + it->second->length_ == final))
			{
				it->second->left = 1;
				leftNodes.push_back(it->second);
				leaves.push_back(true);
			}
		}
	}
}

string SuffixTree::traverse_leftNode(Node* current, const string& key, bool leaf)
{
	if (current == NULL)
	{
		return "";
	}
	if (leaf)
	{
		return key.substr(current->start_, 1) + traverse_leftNode(current->parent, key, false);
	}
	else
		return key.substr(current->start_,current->length_) + traverse_leftNode(current->parent, key, false);
}

void SuffixTree::marker_start(int last, int final, vector<Node*>& leftNodes, vector<bool>& leaves)
{
	marker(&root, last, final, leftNodes, leaves);
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
			out_put = out_put + key[i + it->second->start_];
		cout << out_put << endl;
		print_trie(it->second, key);
	}
}

void SuffixTree::shortest_non_shared_substring(const string& key, int last)
{
	queue<Node*> que;
	que.push(&root);

	while (!que.empty())
	{
		Node* current = que.front();
		que.pop();
		for (map<char, Node*>::iterator it = current->children.begin(); it != current->children.end(); it++)
		{
			if (it->second->start_ + it->second->length_ <=last)
			{
				cout << key.substr(it->second->start_, it->second->length_) << endl;
				return;
			}
			que.push(it->second);
		}
	}
}

vector<string> SuffixTree::substrings_leftNodes_to_root(const string&key, vector<Node*>& leftNodes, vector<bool>& left_leaves)
{
	vector<string> un_shared_substring;
	for (int i = 0; i < leftNodes.size(); ++i)
	{
		string sub_str = traverse_leftNode(leftNodes[i],key, left_leaves[i]);
		un_shared_substring.push_back(sub_str);
	}
	return un_shared_substring;
}

int SuffixTree::shortest_non_shared_string(vector<string>& left_strings)
{
	int index = 0;
	int length = INT_MAX;
	for (int i = 0; i < left_strings.size(); i++)
	{
		if (left_strings[i].size() < length)
		{
			length = left_strings[i].size();
			index = i;
		}
	}
	return index;
}
void SuffixTree::print(const string &key)
{
	//print_trie(&root, key);
	//print parent
	print_parent(&root, key);
}

string solve(string p, string q)
{
	string text = p+"#"+q+"$";
	SuffixTree ST;
	vector<Node*> leftNodes;
	vector<bool> left_leaves;
	vector<string> unshared_strings;
	ST.build_trie(text);
	ST.marker_start(p.size() + 1, text.size(), leftNodes, left_leaves);
	unshared_strings = ST.substrings_leftNodes_to_root(text, leftNodes, left_leaves);
	string result;
	result = unshared_strings[ST.shortest_non_shared_string(unshared_strings)];
	reverse(result.begin(), result.end());	

	return result;
}

int main(void)
{
	string p;
	cin >> p;
	string q;
	cin >> q;

	string ans = solve(p, q);

	cout << ans << endl;

	system("pause");
	return 0;
}