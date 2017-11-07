#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <regex>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

template<typename Key, typename Value>
class MinHeap
{
public:
	vector<pair<Key, Value>> harr;
	int heap_size;

public:
	MinHeap() : heap_size(0) {};
	~MinHeap();
	int parent(int i) {
		return (i - 1) / 2;
	}

	int left_child(int i)
	{
		return 2 * i + 1;
	}

	int right_child(int i)
	{
		return 2 * i + 2;
	}
	bool empty()
	{
		if (heap_size == 0)
			return true;
		else
			return false;
	}
	pair<Key, Value> extractMin();
	void insertKey(Key key, Value value);
	void modifyKey(Key key, Value value);
	void SiftDown(int i);
	void SiftUp(int i);
	void deleteNode(Value value);
	void modifyValue(Value value, Value new_value);
	void increaseKey(Key key, Value value);
	Value getMin()
	{
		return harr[0].second;
	}
};

template<typename Key, typename Value>
MinHeap<Key, Value> :: ~MinHeap()
{
	harr.clear();
}

template<typename Key, typename Value>
void MinHeap<Key, Value>::insertKey(Key key, Value value)
{
	harr.push_back(make_pair(key, value));
	heap_size++;
	int i = heap_size - 1;
	SiftUp(i);
}

template<typename Key, typename Value>
void MinHeap<Key, Value>::SiftUp(int i)
{
	int par = parent(i);
	if (par >= 0 && harr[par].second > harr[i].second)
	{
		swap(harr[par], harr[i]);
		SiftUp(par);
	}
}

template<typename Key, typename Value>
void MinHeap<Key, Value>::SiftDown(int i)
{
	int MinIndex = i;
	int left = left_child(i);
	int right = right_child(i);

	if ((left<heap_size) && (harr[left].second < harr[MinIndex].second))
		MinIndex = left;

	if ((right<heap_size) && (harr[right].second < harr[MinIndex].second))
		MinIndex = right;

	if (i != MinIndex)
	{
		swap(harr[i], harr[MinIndex]);
		SiftDown(MinIndex);
	}
}

template<typename Key, typename Value>
pair<Key, Value> MinHeap<Key, Value>::extractMin()
{
	pair<Key, Value> Min_pair = harr[0];
	swap(harr[0], harr[heap_size - 1]);
	harr.erase(harr.begin() + heap_size - 1);
	heap_size -= 1;
	SiftDown(0);
	return Min_pair;
}

/*
Find the element by key, or id
*/
template<typename Key, typename Value>
void MinHeap<Key, Value>::modifyKey(Key key, Value value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].second == value)
			break;
	}

	harr[i].first = key;
	if (harr[i].first <= 0)
	{
		harr[i].second = getMin() - 1;
		extractMin();
	}
}

template<typename Key, typename Value>
void MinHeap<Key, Value>::increaseKey(Key key, Value value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].second == value)
			break;
	}

	harr[i].first += key;

	if (harr[i].first <= 0)
	{
		harr[i].second = getMin() - 1;
		extractMin();
	}
}
template<typename Key, typename Value>
void MinHeap<Key, Value>::deleteNode(Value value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].second == value)
			break;
	}

	harr[i].first = getMin() - 1;
	SiftUp(i);
	extractMin();
}

template<typename Key, typename Value>
void MinHeap<Key, Value>::modifyValue(Value value, Value new_value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].second == value)
			break;
	}
	Value ori = harr[i].second;
	harr[i].second = new_value;
	if (ori < harr[i].second)
	{
		SiftDown(i);
	}
	else if (ori>harr[i].second)
	{
		SiftUp(i);
	}


}

int main()
{
	MinHeap<int, double> h;


	h.insertKey(50, 50.2);
	h.insertKey(80, 80);
	h.insertKey(19, 120);
	h.insertKey(70, 60);
	h.modifyKey(30, 60);

	h.insertKey(45, 100);
	h.increaseKey(-45, 100);
	while (!h.empty())
	{
		pair<int, double> largest = h.extractMin();
		cout << largest.first << " and " << largest.second << endl;
	}

	system("pause");

	return 0;

}