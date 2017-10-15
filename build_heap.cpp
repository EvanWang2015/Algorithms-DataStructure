/*
Turn Array into a Heap

For i from Low(n/2) down to 1
	SiftDown(i)

SiftDown(i)
	minIndex = i
	l = leftChild(i)
	if l<=size and H[l] < H[minIndex]
		minIndex = l;
	if r>=size and H[r] > H[minIndx]
		minIndex = r;
	if(i!=minIndex)
		swap(H[i], H[minIndex])
		siftDown(minIndex);
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;



class HeapBuilder {
private:
	vector<int> data_;
	vector< pair<int, int> > swaps_;

	void WriteResponse() const {
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i) {
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
	}

	void ReadData() {
		int n;
		cin >> n;
		data_.resize(n);
		for (int i = 0; i < n; ++i)
			cin >> data_[i];
	}

	void SiftDown(int i)
	{
		int minIndex = i;
		int l = LeftChild(i);
		if (l < data_.size() && data_[l] < data_[minIndex])
			minIndex = l;
		int r = RightChild(i);
		if (r < data_.size() && data_[r] < data_[minIndex])
			minIndex = r;

		if (i != minIndex)
		{
			swap(data_[minIndex], data_[i]);
			swaps_.push_back(make_pair(i, minIndex));
			SiftDown(minIndex);
		}
	}

	int LeftChild(int i)
	{
		return 2 * i+1;
	}

	int RightChild(int i)
	{
		return 2 * i + 2;
	}

	void GenerateSwaps() {
		swaps_.clear();
		// The following naive implementation just sorts 
		// the given sequence using selection sort algorithm
		// and saves the resulting sequence of swaps.
		// This turns the given array into a heap, 
		// but in the worst case gives a quadratic number of swaps.
		//
		//
		int sizeD = data_.size()/2;
		for (int i = sizeD; i >=0; i--)
			SiftDown(i);

		//for (int i = 0; i < data_.size(); ++i)
			//for (int j = i + 1; j < data_.size(); ++j) {
				//if (data_[i] > data_[j]) {
					//swap(data_[i], data_[j]);
					//swaps_.push_back(make_pair(i, j));
				//}
			//}
	}

public:
	void Solve() {
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	system("pause");
	return 0;
}
