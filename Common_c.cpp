#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	//=================================================== DECLARATION ==============================================================

	char n1[30], n_main[30];
	string noun, line, con, main_con, main_noun, m_noun, con_match;
	size_t length, start, pos, len, n_len, start1, con_len, noun_len, c1_len, m_len, i, m_con_len, number;
	vector <string>c;	vector<string>n;	vector<string>c1;	vector<string>m;
	clock_t t1, t2;
	float seconds, diff;


	// ============================================= INPUT/OUTPUT FILES ================================================================

	ifstream datafile;
	datafile.open("COOCS.txt");
	ofstream matched;
	matched.open("matched_context.txt");

	//================================================== GETTING THE FIRST NOUN =========================================================

	cout << "Enter the first noun:";
	cin.getline(n_main, sizeof(n_main));
	string n_main1(n_main);
	


	//================================================= GETTING ALL THE CONTEXTS ==========================================================

	if (datafile.is_open())
	{
		while (noun != n_main1)
		{
			getline(datafile, line);
			length = line.size();
			start = line.find('\t');
			noun = line.substr(pos = 0, len = start);
			n_len = noun.size();
			line = line.substr(pos = n_len + 1, len = length);
		}

		while (line != "/0")
		{
			start1 = line.find('\t');
			if (line == "")
			{	break;	}
			con = line.substr(pos = 0, len = start1);
			con_len = con.find('-#-');
			con = con.substr(pos = 0, len = con_len - 1);
			c.push_back(con);
			line = line.substr(start1 + 1);
		}

		datafile.clear();
		datafile.seekg(0, ios::beg);
	}

	//========================================================= FINDING COMMON CONTEXT WITH OTHER NOUNS ===========================================

	cout << "Enter number of nouns left:";
	cin >> number;

	for (i = 0; i <= number; i++)
	{
		cout << "enter the Noun:";
		cin.getline(n1, sizeof(n1));
		string n_1(n1);
		n.push_back(n_1);																	// GETTING NOUNS IN A VECTOR 'n'
	}
	noun_len = n.size();
	
	t1 = clock();
	
	for (size_t j = 1; j < noun_len; j++)
	{
		main_noun = n[j];
		m_con_len = c.size();
		while (noun != main_noun)
		{
			getline(datafile, line);
			length = line.size();
			start = line.find('\t');
			noun = line.substr(pos = 0, len = start);
			n_len = noun.size();
			line = line.substr(pos = n_len + 1, len = length);
		}

		while (line != "/0")
		{
			start1 = line.find('\t');
			if (line == "")
			{	break;	}
			con = line.substr(pos = 0, len = start1);
			con_len = con.find('-#-');
			con = con.substr(pos = 0, len = con_len - 1);
			c1.push_back(con);
			line = line.substr(start1 + 1);
		}

		datafile.clear();
		datafile.seekg(0, ios::beg);
		c1_len = c1.size();
		for (size_t b = 0; b < c1_len; b++)
		{
			for (size_t a = 0; a < m_con_len; a++)
			{
				if (c[a] == c1[b])
				{	m.push_back(c[a]);	}
			}
		}

		c.clear();
		m_len = m.size(); 
			
		for (size_t d = 0; d < m_len; d++)
		{	c.push_back(m[d]);	}																										// VECTOR WITH ALL THE CONTEXTS
			
		m.clear();
		c1.clear();
	}

	con_len = c.size();																									// LENGTH OF CONTEXT VECTOR
	
	for (i = 0; i < con_len; i++)
	{
		con_match = c[i];
		matched << con_match << '\n';
	}

	t2 = clock();
	diff = t2 - t1;
	seconds = diff / CLOCKS_PER_SEC;

	matched << seconds;

	datafile.close();
	matched.close();


	return 0;
}


