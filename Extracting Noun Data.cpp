#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	string line1, line,noun;
	size_t length,start,pos,len;
	int a=0;

	ifstream matchfile;
	matchfile.open("upper.txt");
	ifstream datafile;
	datafile.open("COOCS.txt");
	ofstream new_data;
	new_data.open("new_data.txt");
	
	while (!datafile.eof())
	{
		getline(datafile, line);
		length = line.size();
		start = line.find('\t');
		noun = line.substr(pos = 0, len = start);
		//n_len = noun.size();
		//line = line.substr(pos = n_len + 1, len = length);
		while (!matchfile.eof())
		{
			getline(matchfile, line1);
			if (line1 == noun)
			{
				new_data << line << '\n';
			}
		}
		matchfile.clear();
		matchfile.seekg(0, ios::beg);
		a++;
		cout << a << '\t';
	}

	datafile.close();
	matchfile.close();
	new_data.close();
	return 0;
}
