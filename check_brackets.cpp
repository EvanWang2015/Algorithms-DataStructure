/*
This code is used to check brackets using stack operations

Input contains one string S which consists of big and small latin letters, digits, punctuation marks and brackets from the set [] {} ()

Constraints: the length of S is at least 1 and at most 10^5

Output: if the code in S uses brackets correctly, output "Success". Otherwise, output the 1-based index of the first unmatched closing 
bracket, and if there no unmatched closing brackets, output the 1-based index of the first unmatched opening bracket. 
*/

#include <iostream>
#include <stack>
#include <string>
#include <fstream>

using std::stack;

/*
Define data type of Bracket, including current position, and type of Bracket: '(', '{', '['
*/
struct Bracket {
	Bracket(char type, int position) :
		type(type),
		position(position)
	{}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() {
	std::string text;

	/*std::ifstream file("54");

	if (file)
	{
		std::cout << "find";
		getline(file, text,'\0');
	}
	*/
	getline(std::cin, text);
	/*
	when flag =1, find the first unmatched closing bracket
	when flag =2, find the first unmatched opening bracket
	default flag = 0;
	*/
	int flag = 0;
	std::stack <Bracket> opening_brackets_stack;
	int position;
	for (position = 0; position < text.length(); ++position) {
		char next = text[position];

		if (next == '(' || next == '[' || next == '{') {
			Bracket tem(next, position);
			opening_brackets_stack.push(tem);
		}

		if (next == ')' || next == ']' || next == '}') {

			if (!opening_brackets_stack.empty())
			{
				Bracket tem = opening_brackets_stack.top();
				if (tem.Matchc(next))
					opening_brackets_stack.pop();
				else
				{
					//out put the first unmatched closing bracket
					flag = 1;
					std::cout << position + 1 << std::endl;
					break;
				}
			}
			else {
				flag = 1;
				std::cout << position + 1 << std::endl;
				break;
			}

			
			
		}
	}

	if (flag == 0 && opening_brackets_stack.empty())
	{
		std::cout << "Success" << std::endl;
	}
	else if(flag==0 && !opening_brackets_stack.empty())
	{
		Bracket tem = opening_brackets_stack.top();

		while (!opening_brackets_stack.empty())
		{
			tem = opening_brackets_stack.top();
			opening_brackets_stack.pop();
		}
			
		std::cout << tem.position + 1 << std::endl;
	}
	else
	{
		//nothing happen here, since we have ouputed the position of the unmatched closing bracket
	}
	
	//system("pause");

	return 0;
}
