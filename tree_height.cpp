/*
Comput tree height:

Input: YOu are given a descrption of a rooted tree. Your task is to compute and ouput its height. 

Recall that the height of a (rooted) tree is the maximum depth of a node, or the maximum distance from a leaf to
the roof. YOu are given an arbitrary tree, not necessarily a binary tree. 

The second line containes n integer numbers from -1 to n-1 parents of nodes. If the i-th one of them is -1, node i is the root, otherwise
it's 0-based index of the parent of i-th node. 
*/

/*
Here we use array to express the tree, and we keep track it's parents. For each node, we keep track locations of its children. And adapted dynamic programming to track 
it's parent height. If the parent's height has been calcualted, then we don't have to reversely find root to calculate the height. 
*/


#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
	int key;
	Node *parent;
	std::vector<Node *> children;

	Node() {
		this->parent = NULL;
	}

	void setParent(Node *theParent) {
		parent = theParent;
		parent->children.push_back(this);
	}
};


int main_with_large_stack_space() {
	std::ios_base::sync_with_stdio(0);
	int n;
	std::cin >> n;

	std::vector<Node> nodes;
	nodes.resize(n);
	for (int child_index = 0; child_index < n; child_index++) {
		int parent_index;
		std::cin >> parent_index;
		if (parent_index >= 0)
			nodes[child_index].setParent(&nodes[parent_index]);
		nodes[child_index].key = child_index;
	}

	int maxHeight = 0;
	std::vector<int> Heights(n);
	std::fill(Heights.begin(), Heights.end(), 0);

	for (int leaf_index = 0; leaf_index < n; leaf_index++) {
		int height = 0;
		int location;
		for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
		{			
			location = v - &nodes[0];
			//std::cout << location << " ";
			if (Heights[location] != 0)
			{				
				break;
			}
			height++;			
		}
		Heights[leaf_index] = height + Heights[location];
		maxHeight = std::max(maxHeight, Heights[leaf_index]);
	}

	//std::cout << std::endl;
	//for (int i = 0; i < n; i++)
	//{
	//	//maxHeight = std::max(maxHeight, Heights[i]);		
	//	std::cout << Heights[i] << " " << std::endl;
	//}

	std::cout << maxHeight << std::endl;

	//system("pause");
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}

#endif
	return main_with_large_stack_space();
}
