struct node
{
	int key_value;
	node* left;
	node* right;
};

class btree
{
public: 
	btree();
	~btree();

	void insert(int key);
	node* search(int key);
	void destroy_tree();

private:
	void destroy_tree(node* leaf);
	void insert(int key, node* leaf);
	node* search(int key, node* leaft);

	node *root;
};

btree::btree()
{
	root = nullptr;
}

btree:: ~btree(){
	destroy_tree();
}

void btree::destroy_tree(node* leaf)
{
	if (leaf != nullptr)
	{
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(int key, node* leaf)
{
	if (key < leaf->key_value)
	{
		if(leaf->left!=nullptr)		
			insert(key, leaf->left);
		else
		{
			leaf->left = new node;
			leaf->left->key_value = key;
			leaf->left->left = nullptr;
			leaf->left->right = nullptr;
		}
	}
	else if(key>=leaf->key_value)
	{
		if (leaf->right != nullptr)
			insert(key, leaf->right);
		else
		{
			leaf->right = new node;
			leaf->right->key_value = key;
			leaf->right->left = nullptr;
			leaf->right->right = nullptr;
		}
	}
}

node *btree::search(int key, node* leaf)
{
	if (leaf != nullptr)
	{
		if (key == leaf->key_value)
		{
			return leaf;
		}
		if (key < leaf->key_value)
			return search(key, leaf->left);
		else
			return search(key, leaf->right);
	}
	else
		return nullptr;
}

void btree::insert(int key)
{
	if (root != nullptr)
	{
		insert(key, root);
	}
	else
	{
		root = new node;
		root->key_value = key;
		root->left = nullptr;
		root->right = nullptr;
	}
}

node* btree::search(int key)
{
	return search(key, root);
}

void btree::destroy_tree()
{
	destroy_tree(root);
}