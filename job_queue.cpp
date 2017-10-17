/*
This program simulate Parallel Processing

Task: Threads take jobs in the order they are given in the input. If there is a free thread, 
it immediately takes the next job from the list. If a thread has started processing a job, it 
doesn't interrupt or stop until it finishes processing the job. If several threads try to take jobs from
the list simutaneously, the thread with smaller index takes the job. For each job you know exactly how long 
it takes any thread to processng this job, and this time is the same for all the threads. You need to determine for
which job which thread will process it and when will it start processing. 

output: output exactly m lines. i-th line should contain two space-separated integers-the 0-based index of the thread which
will process the i-th job and the time in seconds when it will start processing that job. 

Author: Haitang Wang
Time: 10/17/20017
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::pair;
using std::make_pair;
using std::swap;

/*
Data structure for each heap node. 
*/
struct WorkerJob
{
	pair<int, long long> worker_finish_time;
	int jobs_index; //track the time duration of a job
};

/*
priority queue is used to find which job will be executed first.

To find it, return which job finish first (with minimum worker index). 
*/
class JobQueue {
private:
	int num_workers_;
	vector<long long> jobs_;
	int job_nums;
	vector<int> assigned_workers_;
	vector<long long> start_times_;
	vector<WorkerJob> heap;
	int current_job_index;
	int heap_size;
	void WriteResponse() const {
		for (int i = 0; i < assigned_workers_.size(); ++i) {
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
		}
	}

	void ReadData() {
		int job_nums;
		cin >> num_workers_ >> job_nums;
		jobs_.resize(job_nums);
		current_job_index = 0;
		heap_size = 0;
		for (int i = 0; i < job_nums; ++i)
			cin >> jobs_[i];
	}

	int LeftChild(int i)
	{
		return 2 * i + 1;
	}

	int RightChild(int i)
	{
		return 2 * i + 2;
	}

	void ShiftDown(int i)
	{
		int minIndex = i;

		int l = LeftChild(i);
		if (l < heap_size && heap[l].worker_finish_time.second <= heap[i].worker_finish_time.second)
		{
			if (heap[l].worker_finish_time.second < heap[i].worker_finish_time.second)
				minIndex = l;
			else
			{
				//if they have same finishing time, then we choose the one with lower index
				if (heap[l].worker_finish_time.first < heap[i].worker_finish_time.first)
					minIndex = l;
			}
		}
		int r = RightChild(i);
		if (r < heap_size && heap[r].worker_finish_time.second <= heap[minIndex].worker_finish_time.second)
		{
			if (heap[r].worker_finish_time.second < heap[minIndex].worker_finish_time.second)
				minIndex = r;
			else
			{
				//if they have same finishing time, then we choose the one with lower index
				if (heap[r].worker_finish_time.first < heap[minIndex].worker_finish_time.first)
					minIndex = r;
			}
		}

		if (i != minIndex)
		{
			swap(heap[minIndex], heap[i]);
			ShiftDown(minIndex);
		}
	}

	/*
	This function is not necessary in this function. 
	However, if we want to delete all the heap, then we need it.
	*/
	WorkerJob ExtractMin()
	{
		WorkerJob rest = heap[0];
		heap[0] = heap[heap_size - 1];
		heap_size--;
		ShiftDown(0);
		return rest;
	}


	/*
	This function, we find minHeap and update the next job added to the thread.	
	*/
	void WriteMin_UpdateMin()
	{
		WorkerJob minJob;
		int finish_index = 0;
		int duration_index;
		//cout << "first minmum: ";
		//cout << heap_size << " " << heap[0].jobs_index << " " << heap[0].worker_finish_time.first << " " << heap[0].worker_finish_time.second <<" "<< std::endl;
		while (current_job_index < jobs_.size())
		{
			minJob = heap[0];
			duration_index = minJob.jobs_index;
			//cout << "current job index: " << current_job_index << std::endl;
			//cout << "min job index: " << duration_index << "\t time: " << jobs_[duration_index] << std::endl;			
			assigned_workers_.push_back(minJob.worker_finish_time.first);
			start_times_.push_back(heap[0].worker_finish_time.second);
			heap[0].worker_finish_time.second = heap[0].worker_finish_time.second + jobs_[current_job_index];
			heap[0].jobs_index = current_job_index;
			//cout << "worker: " << minJob.worker_finish_time.first << "\t starting time: "<< minJob.worker_finish_time.second - jobs_[duration_index];
			//cout << std::endl;
			current_job_index++;
			ShiftDown(0);
		}

		/*
		if we extract min from the heap, and delete all info, then 
		uncomment the following code. 
		*/

		//while (heap_size)
		//{
			//minJob = ExtractMin();

			//duration_index = minJob.jobs_index;
			//assigned_workers_.push_back(minJob.worker_finish_time.first);
			//start_times_.push_back(minJob.worker_finish_time.second - jobs_[duration_index]);
		//}
	}

	void BuildHeap()
	{
		//building array of heap
		for (int i = 0; i < jobs_.size() && i < num_workers_; i++)
		{
			WorkerJob temp;
			temp.worker_finish_time = make_pair(i, jobs_[i]);
			temp.jobs_index = current_job_index;
			heap.push_back(temp);
			current_job_index++;
			heap_size++;

			assigned_workers_.push_back(current_job_index);
			start_times_.push_back(0);
		}
		//cout << "current job index after BuildHeap: " << current_job_index << " jobs.size(): " << jobs_.size() << std:: endl;
		int sizeD = heap_size / 2;
		//cout << sizeD << std::endl;
		for (int i = sizeD; i >= 0; i--)
			ShiftDown(i);

	}
	void AssignJobs() {
		//output the minheap
		WriteMin_UpdateMin();
	}

public:
	void Solve() {
		ReadData();
		BuildHeap();
		AssignJobs();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();
	system("pause");
	return 0;
}
