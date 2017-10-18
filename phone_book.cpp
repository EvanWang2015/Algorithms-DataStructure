#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using std::string;
using std::vector;
using std::cin;
using std::map;

vector<string> read_queries() {
	int n;
	cin >> n;
	vector<string> result;
	map <string,string> query;
	string type;
	map<string, string>::iterator itr;
	int index;
	for (int i = 0; i < n; i++)
	{
		cin >> type;
		//std::cout << type << " "<< type.compare("add")<<std::endl;
		string numStr="";
		string name="";
		if (type.compare("add")==0)
		{
			cin >> numStr >> name;
			//std::cout << numStr << " " <<name << std::endl;
			//int x = stoi(numStr);
			//std::cout << x << " " <<query.size()<< std::endl;
			//query[x] = name;
			query[numStr] = name;
			//std::cout << query.size() << std::endl;
		}
		else 
		{
			cin >> numStr;
			//int x = stoi(numStr);
			itr = query.find(numStr);
			if (type.compare("del") == 0)
				//query[x] = "";
			{
				if (itr != query.end())
				{
					query.erase(itr);
					//std::cout << "after deletion: "<<query.size() << std::endl;
				}
			}
				
					
			else //finding element
			{
				
				if (itr==query.end())
					result.push_back("not found");
				else
					result.push_back(itr->second);

				//std::cout <<"vecotr size: "<< result.size() << std::endl;
			}
		}
	}

	return result;
}

void write_responses(const vector<string>& result) {
	for (size_t i = 0; i < result.size(); ++i)
		std::cout << result[i] << "\n";
}

int main() {
	vector<string> result;
	result = read_queries();
	write_responses(result);
	//system("pause");
	return 0;
}
