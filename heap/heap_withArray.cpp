/*
Array Representation of min Binary Heap. 
A binary heap is a complete binary tree. The basic is in the following:
1) The root element will be arr[0];
2) Indexes of other nodes for ith node:
	arr[i/2] return the parent node;
	arr[2*i+1] returns the left child node;
	arr[2*i+2] returns the right child node;
*/

#include<iostream>
#include<climits>

using namespace std;

void swap(int* child, int* parent)
{
	
	int temp = *parent;
	*parent = *child;
	*child = temp;	
}

/*-------------------------------------------------
Heap data structure definition
harr: heap array
capacity: maixmum number of elements allowed
heap_size: current number of elements in the heap
---------------------------------------------------*/
class MinHeap
{
public: 
	int *harr; //pointer to array of elements in heap
	int capacity; //maximum possible size of min heap
	int heap_size;

public:
	MinHeap(int capacity);
	//to heapify a subtree with root at given index
	void MinHeapify(int i);

	int parent(int i)
	{
		return (i - 1) / 2;
	}

	//get index of left child of node at index i
	int left(int i)
	{
		return 2 * i + 1;
	}

	int right(int i)
	{
		return 2 * (i + 1);
	}

	//extract the root or the minimum element

	int extractMin();
	
	void insertKey(int k); //insert a key 'k'
	void deleteKey(int i);

	void decreaseKey(int i, int new_val);

	int getMin()
	{
		return harr[0];
	}

};


/*------------------------------------------------------
Heap initialization:
Input: total capacity for the heap array
heap_size: defines the current number of elements in the heap array
*/
MinHeap:: MinHeap(const int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
}

void MinHeap::insertKey(int k)
{
	if (heap_size == capacity)
	{
		cout << "Overflow: Can not insert more keys";
		return;
	}

	//insert a new key at the end 
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;

	//Now fix the minHeap property if it's been violated
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[i], &harr[parent(i)]);
		i = parent(i);
	}
}

//Deletekey basically it means to reduce the value to minus infinity, then then extractMin()

/*-----------------------------------------------------------------------------
KeleteKey() bascially it reduces the value of a key to minus infinity, and then relocate the 
new key value to the beginning of heap array, and finally extract the minimum value while 
maintaining the minHeap property.
Input: heap arry index to indicate which key to delete
output: None

Alternative method is that we can directly replace the element with last element and apply heapify on that index
-----------------------------------------------------------------------------*/
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

/*-----------------------------------------------------------------------------
ExtractMin() is a function to delete the first element in the heapArray. 
And then relocate the last element to the first element and from the top to its 
children to check to maintain the property of a minHeap.
Input: None
output: minmum key value
-----------------------------------------------------------------------------*/
int MinHeap::extractMin()
{
	if (heap_size <= 0)
	{
		cout << "\nHeap is empty"
			<< " and No valid value returned";
		return INT_MIN;
	}	
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}		
	//store the minimum value, and remove it from the heap
	int minValue = harr[0];
	harr[0] = harr[--heap_size];	
	MinHeapify(0);
	return minValue;
}


/*-----------------------------------------------------------------------------
MinHeapify is a recursive method to heapify a subtree with root at given index.
This method assumes that the subtrees are already heapified.
Input: heap arry index
output: None
-----------------------------------------------------------------------------*/
void MinHeap::MinHeapify(int i)
{
	int l_child = left(i);
	int r_child = right(i);

	int smallest = i;

	if (l_child < heap_size && harr[l_child] < harr[i])
	{
		smallest = l_child;
	}
	if (r_child < heap_size && harr[r_child] < harr[smallest])
	{
		smallest = r_child;
	}

	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
		MinHeapify(smallest);
	}
}
int main()
{

	MinHeap h(11);
	h.insertKey(3);
	h.insertKey(2);
	//h.deleteKey(1);
	h.insertKey(15);
	h.insertKey(5);
	h.insertKey(4);
	h.insertKey(45);
	//cout << h.extractMin() << " ";
	//cout << h.getMin() << " ";
	

	cout << "mininum: "<<h.getMin()<<endl;

	h.decreaseKey(2, 0);

	cout << "mininum: " << h.getMin() << endl;

	while (h.heap_size)
	{
		cout << h.extractMin() << " ";
	}

	cout << endl;
	system("pause");
	return 0;
}