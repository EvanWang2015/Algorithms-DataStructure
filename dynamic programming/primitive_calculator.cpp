/*
Problem introduction:
You are given a primitive calculator that can perform the following three operations with the current number x:
multiply x by 2, multiply x by 3, or add 1 to x. Your goal is given a positive integer n, find the minimum number
of opertions needed to obtain the number n starting from the number 1. 
*/

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence(int n) {
	std::vector<int> sequence(n+1);
	sequence[1] = 0;

	/*
	loop to fill the vector Sequence from 2 to n. sequence[0..1] = 0;
	find minimum operation values base on three case:
	a = sequence[m-1]+1;
	b = sequence[m/2]+1, if(m%2==0)
	c = sequence[m/3]+1, if(m%3==0)
	sequence[m] = min(a, b, c);
	*/
	for (int m = 2; m <= n; m++)
	{
		sequence[m] = INT_MAX;
		int num;
		if (m % 3 == 0 )
		{
			num = sequence[m / 3] + 1;
			if (num < sequence[m])
			{
				sequence[m] = num;
			}				
		}
		
		if (m % 2 == 0)
		{
			num = sequence[m / 2] + 1;
			if (num < sequence[m])
			{
				sequence[m] = num;
			}
				
		}
		
		num = sequence[m - 1] + 1;
		if (num < sequence[m])
		{
			sequence[m] = num;
		}		
	}

	std::vector<int> res(sequence[n]+1);
	//int i=n;
	int count = 0;
	res[sequence[n]] = 1;
	/*
	using backtracking algorithm to find track back which operations were used to get sequence[n].
	The key here is making use the fact sequence[i] is minimum. 
	i - > i/2 or i/3 or i-1 based on min(sequence[i/2] sequence[i/3] sequence[i-1])
	*/
	while (n > 1)
	{
		res[count++] = n;
		if (n % 3 == 0 && n % 2 != 0)
		{
			if (sequence[n / 3] > sequence[n - 1])
				n = n - 1;
			else
				n = n / 3;
		}
		else if (n % 3 != 0 && n % 2 == 0)
		{
			if (sequence[n / 2] > sequence[n - 1])
				n = n - 1;
			else
				n = n / 2;
		}
		else if (n % 3 != 0 && n % 2 != 0)
		{
			n = n - 1;
		}
		else //three cases
		{
			int flag;

			if (sequence[n / 2] > sequence[n / 3])
			{
				flag = 3;
			}
			else
			{
				flag = 2;
			}

			if (flag == 2)
			{
				if (sequence[n / 2] > sequence[n - 1])
					flag = 1;
			}

			if (flag == 3)
			{
				if (sequence[n / 3] > sequence[n - 1])
					flag = 1;
			}

			switch (flag)
			{
			case 1:
				n = n - 1; 
				break;
			case 2: 
				n = n / 2;
				break;
			case 3: 
				n = n / 3; 
			default:
				std::cout << "mistake";
			}				
		}
	}	
	std::reverse(begin(res), end(res));
	return res;
}

int main() {
	int n;
	std::cin >> n;
	vector<int> sequence = optimal_sequence(n);
	std::cout << sequence.size() - 1 << std::endl;
	for (size_t i = 0; i < sequence.size(); ++i) 
	{	
	std::cout << sequence[i] << " ";
	}
	system("pause");
	return 0;
}
