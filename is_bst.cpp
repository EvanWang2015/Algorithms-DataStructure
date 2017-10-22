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
#include <climits>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
	long key;
	int left;
	int right;
	int branch;
	Node() : key(0), left(-1), right(-1) {}
	Node(long key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool isBSTUtil(vector<Node> &tree, int i, long min, long max)
{
	/* an empty tree is BST */
	if (i == -1)
		return true;

	/* false if this node violates the min/max constraint */
	if (tree[i].key <= min || tree[i].key >= max)
		return false;

	/* otherwise check the subtrees recursively,
	tightening the min or max constraint */
	return
		isBSTUtil(tree, tree[i].left, min, tree[i].key) &&  // Allow only distinct values
		isBSTUtil(tree, tree[i].right, tree[i].key, max);  // Allow only distinct values
}

bool IsBinarySearchTree(vector<Node>& tree)
{
	long min = LONG_MIN;
	long max = LONG_MAX;
	if (tree.size() == 0)
		return true;
	return isBSTUtil(tree, 0, min, max);
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
	//system("pause");
	return 0;
}
