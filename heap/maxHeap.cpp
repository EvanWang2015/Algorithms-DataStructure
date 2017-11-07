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
class MaxHeap
{
public:
	vector<pair<Key, Value>> harr;
	int heap_size;

public:
	MaxHeap() : heap_size(0) {};
	~MaxHeap();
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

	pair<Key, Value> extractMax();
	void insertKey(Key key, Value value);
	void modifyKey(Key key, Value value);
	void modifyValue(Value value, Value new_value);
	void increaseKey(Key key, Value value);
	void SiftDown(int i);
	void SiftUp(int i);
	void deleteNode(Value value);
	bool empty()
	{
		if (heap_size == 0)
			return true;
		else
			return false;
	}
	Value getMax()
	{
		return harr[0].second;
	}
};

template<typename Key, typename Value>
MaxHeap<Key, Value> :: ~MaxHeap()
{
	harr.clear();
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::insertKey(Key key, Value value)
{
	harr.push_back(make_pair(key, value));
	heap_size++;
	int i = heap_size - 1;
	SiftUp(i);
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::SiftUp(int i)
{
	int maxIndex = i;
	int par = parent(i);
	if (par >= 0 && harr[par].second < harr[maxIndex].second)
	{
		swap(harr[par], harr[i]);
		SiftUp(par);
	}
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::SiftDown(int i)
{
	int maxIndex = i;
	int left = left_child(i);
	int right = right_child(i);

	if ((left<heap_size) && (harr[left].second > harr[maxIndex].second))
		maxIndex = left;

	if ((right<heap_size) && (harr[right].second > harr[maxIndex].second))
		maxIndex = right;

	if (i != maxIndex)
	{
		swap(harr[i], harr[maxIndex]);
		SiftDown(maxIndex);
	}
}

template<typename Key, typename Value>
pair<Key, Value> MaxHeap<Key, Value>::extractMax()
{
	pair<Key, Value> max_pair = harr[0];
	swap(harr[0], harr[heap_size - 1]);
	harr.erase(harr.begin() + heap_size - 1);
	heap_size -= 1;
	SiftDown(0);
	return max_pair;
}

/*
Find the element by value
*/
template<typename Key, typename Value>
void MaxHeap<Key, Value>::modifyKey(Key size, Value value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].second == value)
			break;
	}

	harr[i].first = size;

	if (harr[i].first <= 0)
	{
		harr[i].second = getMax() + 1;
		SiftUp(i);
		extractMax();
	}

}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::increaseKey(Key size, Value value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].second == value)
			break;
	}

	harr[i].first += size;
	if (harr[i].first <= 0)
	{
		harr[i].second = getMax() + 1;
		SiftUp(i);
		extractMax();
	}
}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::modifyValue(Value value, Value new_value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].first == value)
			break;
	}
	Value ori = harr[i].second;
	harr[i].second = value;

	if (ori > harr[i].second)
	{
		SiftDown(i);
	}
	else
	{
		SiftUp(i);
	}

}

template<typename Key, typename Value>
void MaxHeap<Key, Value>::deleteNode(Value value)
{
	int i = 0;
	for (; i < heap_size; i++)
	{
		if (harr[i].first == value)
			break;
	}
	harr[i].second = getMax() + 1;
	SiftUp(i);
	ExtractMax();
}

int main()
{
	MaxHeap<int, double> h;


	h.insertKey(50, 50);
	h.insertKey(80, 80.8);
	h.insertKey(19, 120);
	h.insertKey(70, 60);
	h.modifyKey(30, 60);
	h.increaseKey(-30, 60);
	h.insertKey(45, 100.1);
	while (!h.empty())
	{
		pair<int, double> largest = h.extractMax();
		cout << largest.first <<" and " <<largest.second  << endl;
	}
	
	system("pause");

	return 0;

}