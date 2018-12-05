#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

float top(vector <float> t)
{
	int t_len, i, position_len, p, j;
	t_len = t.size();
	float a, b = 0;
	vector <float> position;

	position_len = position.size();

	for (i = 0; i < t_len; i++)
	{
		a = t[i];
		if (t[i] > b)
		{
			b = t[i];
		}
	}

	for (j = 0; j < t_len; j++)
	{
		a = t[j];
		if (b == t[j])
		{
			p = j;
			break;
		}
	}


	return (p);
}

int main()
{
	//=================================================== DECLARATION ==============================================================

	char n1[30], n_main[30];
	string noun, line, con, main_con, main_noun, m_noun, con_match, con_1,con1,con2,trusted_noun,f_member,n3,n2;
	size_t length, start, pos, len, n_len, start1, con_len, noun_len, c1_len, m_len, i, m_con_len, number, j, counter = 0;
	vector <string>c;	vector<string>n;	vector<string>c1;	vector<string>m; vector<string>new_trusted; vector<float>membership; vector <float> fuz_mem; vector<string>fuz_noun; vector<string>final_noun; vector<float>final_score;
	//clock_t t1, t2;
	float seconds, diff, threshold,counter2 = 0, p,q,f_mem,score;
	int a = 0,membership_len,location,lower_n,upper_n;
	// ============================================= INPUT/OUTPUT FILES ================================================================

	ifstream datafile;
	datafile.open("COOCS.txt");
//	ofstream matched;
//	matched.open("matched_context.txt");
	//ifstream matchfile;
	//matchfile.open("upper.txt");
	ofstream lower;
	lower.open("lower.txt");
	ifstream new_data;
	new_data.open("new_data.txt");
	ifstream fuzzy;
	fuzzy.open("fuzzy_score.txt");

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
			{
				break;
			}
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

	for (i = 0; i < number; i++)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "enter the Noun:";
		cin.getline(n1, sizeof(n1));
		string n_1(n1);

		main_noun = n_1;
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
			{
				break;
			}
			con = line.substr(pos = 0, len = start1);
			con_len = con.find('-#-');
			con = con.substr(pos = 0, len = con_len - 1);

			for (j = 0; j < m_con_len; j++)
			{
				con_1 = c[j];
				if (con == con_1)
				{
					counter++;
				}
			}
			if (counter <= 0)
			{
				c.push_back(con);
			}
			counter = 0;
			line = line.substr(start1 + 1);
		}

		datafile.clear();
		datafile.seekg(0, ios::beg);
	}
	con_len = c.size();
	p = con_len;
	threshold = (p * 10) / 100;
	
	string line1;

	while (!new_data.eof())
	{
		getline(new_data, line);
		if (line == "")
		{
			break;
		}
		length = line.size();
		start = line.find('\t');
		noun = line.substr(pos = 0, len = start);
		n_len = noun.size();
		line = line.substr(pos = n_len + 1, len = length);
		
		while (line != "/0")
		{
			start1 = line.find('\t');
			if (line == "")
			{
				break;
			}
			con = line.substr(pos = 0, len = start1);
			con_len = con.find('-#-');
			con = con.substr(pos = 0, len = con_len - 1);
			c1.push_back(con);
			line = line.substr(start1 + 1);
		}
		c1_len = c1.size();
		for (i = 0; i < p; i++)
		{
			con1 = c[i];
			for (j = 0; j < c1_len; j++)
			{
					con2 = c1[j];
					if (con1 == con2)
					{
						counter2++;
					}
				}
			}

			if (counter2 >= threshold)
			{
				new_trusted.push_back(noun);
				membership.push_back(counter2);
			}

			counter2 = 0;
			cout << a << '\t';
			a++;
			c1.clear();
		}
		

	while (!fuzzy.eof())
	{
		getline(fuzzy, line);
		if (line == "")
		{
			break;
		}
		length = line.size();
		start = line.find('\t');
		noun = line.substr(pos = 0, len = start);
		n_len = noun.size();
		f_member = line.substr(pos = n_len + 1, len = length);
		f_mem = stof(f_member);
		fuz_noun.push_back(noun);
		fuz_mem.push_back(f_mem);
	}

	lower_n = new_trusted.size();
	upper_n = fuz_noun.size();

	for (i = 0; i < upper_n; i++)
	{
		n3 = fuz_noun[i];
		for (j = 0; j < lower_n; j++)
		{
			n2 = new_trusted[j];
			if (n3 == n2)
			{
				score = membership[j] + fuz_mem[i];
				final_noun.push_back(n2);
				final_score.push_back(score);
			}
		}
	}







	/*while (!datafile.eof())
	{
		getline(datafile, line);
		if (line == "")
		{
			break;
		}
		length = line.size();
		start = line.find('\t');
		noun = line.substr(pos = 0, len = start);
		n_len = noun.size();
		line = line.substr(pos = n_len + 1, len = length);

		while (!matchfile.eof())
		{
			getline(matchfile, line1);
			if (noun == line1)
			{
				while (line != "/0")
				{
					start1 = line.find('\t');
					if (line == "")
					{
						break;
					}
					con = line.substr(pos = 0, len = start1);
					con_len = con.find('-#-');
					con = con.substr(pos = 0, len = con_len - 1);
					c1.push_back(con);
					line = line.substr(start1 + 1);
				}
				c1_len = c1.size();
				for (i = 0; i < p; i++)
				{
					con1 = c[i];
					for (j = 0; j < c1_len; j++)
					{
						con2 = c1[j];
						if (con1 == con2)
						{
							counter2++;
						}
					}
				}

				if (counter2 >= threshold)
				{
					new_trusted.push_back(noun);
					membership.push_back(counter2); 
				}
				
				counter2 = 0;
			}
		}
		matchfile.clear();
		matchfile.seekg(0, ios::beg);
		cout << a<<'\t';
		a++;
	}
	*/


	membership_len = final_score.size();
	for (i = 0; i < membership_len;)
	{
		location = top(final_score);
		trusted_noun = final_noun[location];
		score = final_score[location];
		lower << trusted_noun << '\t'<< score<<'\n';
		final_score[location] = 0;
		i++;
	}

	datafile.close();
//	matched.close();
	lower.close();
//	matchfile.close();
	new_data.close();

	return 0;
}


