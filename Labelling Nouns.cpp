#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

float lower, base = 0, number_2;

//--------------------------------------------------------------------- S-function ------------------------------------------------------------------

float s_function(float y1)
{
	float alpha = 0.001, beta = 0.02;

	if (y1 > 0.5)
	{
		y1 = 1;
	}

	else if (y1 < 0.5 && y1 > 0.05)
	{
		y1 = (y1 - beta) / (beta - alpha);	if (y1 > 1)
		{
			y1 = 1;
		}
		else
		{
			y1 = y1;
		}
	}

	else if (y1 <0.05 && y1 >0.005)
	{
		y1 = (y1 - alpha) / (beta - alpha);
		if (y1 > 1)
		{
			y1 = 1;
		}
		else
		{
			y1 = y1;
		}
	}

	else
	{
		y1 = 2;
	}
	return y1;
}

//------------------------------------------ getting the lowset membership from the trusted set -------------------------------------------------------

float lower_f(vector <float> low)
{
	int i, low_len;
	float low_1;

	low_len = low.size();
	lower = 0;

	for (i = 0; i < low_len; i++)
	{
		low_1 = low[i];
		{	lower = low_1 + lower;	}
	}

	lower = lower / number_2;
	lower = (lower * 70) / 100;

	return(lower);
}

//------------------------------------- finding the top seeds ---------------------------------------------------------

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


//--------------------------------------------- MAIN CODE ----------------------------------------------------------------
int main()
{
	//------------------------------------------ Declarations -------------------------------------------------------------

	string n1, main_n, main_c, line, length, newline, sum, c2, value, trusted_noun, t_noun, t, used_noun;
	int i, noun_len, j, a = 0, k, mem_len, count = 0, con2_len, number_1, location, membership_len, z = 0, used_trusted_len, w = 0, h = 0;
	char c[100], n[100];
	size_t start, pos, len, length1, start1, delim;
	vector <string> noun1; vector <string> con1; vector <float> membership; vector <string> new_trusted_noun; vector <string> con2; vector <string> used_trusted; vector <string> new_trusted;
	float s, val, x, m1 = 0.0, m, position_len = 0, con_len, seconds, diff, fuzzy_mem;
	clock_t t1, t2;

	//-------------------------------------- Opening of the Files ------------------------------------------------------

	ifstream datafile;
	datafile.open("COOCS.txt");
	ifstream col_sum;
	col_sum.open("col_sum.txt");
	ifstream nounfile;
	nounfile.open("NOUNS.txt");
	ofstream trusted;
	trusted.open("trsuted_noun.txt");
	ifstream used;
	used.open("used.txt");
	ofstream new_noun;
	new_noun.open("new nouns.txt");
	ofstream fuzzy;
	fuzzy.open("fuzzy_score.txt");


	/*	while (!used.eof())																						//loading used truested nouns
	{
	getline(used, t);
	used_trusted.push_back(t);
	}*/
	used_trusted_len = used_trusted.size();

	cout << "Enter the number of context:";																	//getting number of common context
	cin >> number_1;

	for (i = 0; i < number_1; i++)																			//getting common context
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "enter the context:";
		cin.getline(c, sizeof(c));
		string con(c);
		con1.push_back(con);
	}
	con_len = con1.size();

	cout << "Enter the number of Nouns:";
	cin >> number_2;
	for (i = 1; i <= number_2; i++)																				//getting common nouns
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Enter noun :";
		cin.getline(n, sizeof(n));
		string noun(n);
		noun1.push_back(noun);
	}
	noun_len = noun1.size();

	t1 = clock();

	//------------------------------------ Calculating membership for the trusted nouns ----------------------------------------

	for (j = 0; j < noun_len; j++)
	{

		main_n = noun1[j];


		if (datafile.is_open())
		{
			while (main_n != n1)
			{
				getline(datafile, line);
				length = line.size();
				start = line.find('\t');
				n1 = line.substr(pos = 0, len = start);
				a++;
				length1 = n1.size();
				line = line.substr(length1 + 1);
				newline = line;
			}
			if (col_sum.is_open())
			{
				for (k = 1; k <= a; k++)
				{
					getline(col_sum, sum);
				}

				col_sum.clear();
				col_sum.seekg(0, ios::beg);
				s = stof(sum);
			}

			while (newline != "\0")
			{
				start1 = newline.find('\t');
				c2 = newline.substr(pos = 0, len = start1);
				con2.push_back(c2);
				newline = newline.substr(start1 + 1);
			}
			con2_len = con2.size();

			for (i = 0; i < con_len; i++)
			{
				main_c = con1[i];
				for (k = 0; k < con2_len; k++)
				{
					c2 = con2[k];
					delim = c2.find("-#-");
					value = c2.substr(delim + 3);
					c2 = c2.substr(pos = 0, len = delim);
					if (main_c == c2)

						//----------------------- calaculating membership --------------------------------------
					{
						val = stof(value);
						x = val / s;
						m = s_function(x);
						if (m == 2)
						{
							m = 0;
						}
						m1 = m1 + m;
					}
				}
			}
			membership.push_back(m1);
			datafile.clear();
			datafile.seekg(0, ios::beg);
			a = 0;	m = 0;	m1 = 0;	con2.clear();
		}
	}
	mem_len = membership.size();
	lower = lower_f(membership);
	membership.clear();

	//-------------------------------------------------------------------------- for the complete dataset ----------------------------------------------------------------------------------------
	while (!datafile.eof())
	{
		getline(datafile, line);
		if (line == "\0")
		{
			break;
		}

		length = line.size();
		start = line.find('\t');
		n1 = line.substr(pos = 0, len = start);
		a++;
		length1 = n1.size();
		line = line.substr(length1 + 1);
		newline = line;

		if (col_sum.is_open())
		{
			for (k = 1; k <= a; k++)
			{
				getline(col_sum, sum);
			}

			col_sum.clear();
			col_sum.seekg(0, ios::beg);
			s = stof(sum);
		}

		while (newline != "\0")
		{
			start1 = newline.find('\t');
			c2 = newline.substr(pos = 0, len = start1);
			con2.push_back(c2);
			newline = newline.substr(start1 + 1);
		}
		con2_len = con2.size();

		for (i = 0; i < con_len; i++)
		{
			main_c = con1[i];
			for (k = 0; k < con2_len; k++)
			{
				c2 = con2[k];
				delim = c2.find("-#-");
				value = c2.substr(delim + 3);
				c2 = c2.substr(pos = 0, len = delim);
				if (main_c == c2)
				{
					val = stof(value);															// calculating membership for matched context
					x = val / s;
					m = s_function(x);
					if (m == 2)
					{
						m = 0;
					}
					m1 = m1 + m;																// getting the sum 
				}
			}
		}
		if (m1 > lower)																	// finding if the sum satisfies the condition to be trusted
		{
			membership.push_back(m1);
			new_trusted_noun.push_back(n1);
		}
		con2.clear();	m1 = 0;	z++;
		cout << z << '\t';
	}

	membership_len = membership.size();



	//----------------------------------- trusted nouns --------------------------------------------------------------

	/*	while (position_len < 30 || w < 15)
	{
	location = top(membership);
	trusted_noun = new_trusted_noun[location];
	if (position_len < 30)
	{	trusted << trusted_noun << '\n';	}
	membership[location] = 0;
	position_len++;

	for (i = 0; i < used_trusted_len; i++)
	{
	used_noun = used_trusted[i];
	if (trusted_noun == used_noun)
	{	h++;	}
	}

	if (h <= 0)
	{
	if (w < 15)
	{	new_trusted.push_back(trusted_noun);	}
	}
	w = new_trusted.size();
	h = 0;
	}


	for (i = 0; i < w; i++)
	{
	used_noun = new_trusted[i];
	new_noun << used_noun << '\n';
	} */

	for (i = 0; i < membership_len;)
	{
		location = top(membership);
		trusted_noun = new_trusted_noun[location];
		fuzzy_mem = membership[location];
		fuzzy << trusted_noun << '\t' << fuzzy_mem << '\n';
		trusted << trusted_noun << '\n';
		membership[location] = 0;
		i++;
	}



	/*------------------------------------ Closing all the files ----------------------------------------------------*/


	t2 = clock();
	diff = t2 - t1;
	seconds = diff / CLOCKS_PER_SEC;

	trusted << seconds;

	datafile.close();
	col_sum.close();
	nounfile.close();
	trusted.close();
	used.close();


	return 0;
}








