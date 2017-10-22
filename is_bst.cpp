/*
The definition of the binary search tree is the following:

for any node of the tree, if its key is x, then for any node in its left subtree must be strictly less than x, and for any node
in its right subtree its key must be strictly greater than x. In other words, smaller elements are to the left, and bigger elements are
to the right. 

Input format: the first line contains the number of vertices n. the vertices of the tree are numbered from 0 to n-1. Vertex 0 is the root. 

the next n-1 lines contian information about vertices 0, 1, ..., n-1 in order. Each of these lines contains three integers key_i, left_i, right_i. 

Author: Haitang
Time: 10/22/2017

*/
#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
	long key;
	int left;
	int right;

	Node() : key(0), left(-1), right(-1) {}
	Node(long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void PreOrderSearch(const vector<Node>& tree, int i, bool& flag)
{
	if (i == -1)
	{
		return;
	}
	PreOrderSearch(tree, tree[i].left, flag);
	
	if (tree[i].left != -1)
	{
		long left_key = tree[tree[i].left].key;
		if (tree[i].key <= left_key)
		{
			flag = false;
			return;
		}
			
	}
		
	if (tree[i].right != -1)
	{
		long right_key = tree[tree[i].right].key;
		if (tree[i].key >= right_key)
		{
			flag = false;
			return;
		}
			
	}
			
	PreOrderSearch(tree, tree[i].right, flag);
}
bool IsBinarySearchTree(const vector<Node>& tree) {
	// Implement correct algorithm here
	bool flag = true;

	if (tree.size() == 0)
		return flag;
	PreOrderSearch(tree, 0, flag);

	return flag;
}

int main() {
	int nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; ++i) 
	{
		long key;
		int left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (IsBinarySearchTree(tree)) 
	{
		cout << "CORRECT" << endl;
	}
	else 
	{
		cout << "INCORRECT" << endl;
	}
	system("pause");
	return 0;
}
