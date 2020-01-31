#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace::std;

int NWP(int a_len, int b_len, int a[], int b[], int** tab);
void NWP_Write(int a_len, int b_len, int a[], int b[], int** tab);


bool NWP3(vector<string> a, vector<string> b, int ai_len, int bj_len, vector<int>& save);
void NWP3_Write(vector<string> a, vector<string> b, vector<int> save);

int main()
{
	/*
	#########################################
	######### Rozwiazanie + podciag #########
	#########################################
	*/
	/*
	int size_a;
	int size_b;

	printf("Podaj dlugosc 1 ciagu: ");
	cin >> size_a;
	int* a = new int[size_a];

	printf("Podaj dlugosc 2 ciagu: ");
	cin >> size_b;
	int* b = new int[size_b];
		
	printf("\nPodaj elementy 1 ciagu:\n");
	for (int i = 0; i < size_a; i++)
		cin >> a[i];

	printf("\nPodaj elementy 2 ciagu:\n");
	for (int i = 0; i < size_b; i++)
		cin >> b[i];

	int** tab;

	tab = new int* [size_a + 1];

	for (int i = 0; i <= size_a; i++)
		tab[i] = new int[size_b + 1];

	printf("Najdluzszy wspolny podciag: %d\n", NWP(size_a, size_b, a, b, tab));
	printf("Podciag: ");
	NWP_Write(size_a, size_b, a, b, tab);
	*/

	/*
	#########################################
	################# Diff ##################
	#########################################
	*/
	
	string path1 = "1.txt";
	string path2 = "2.txt";

	vector<string> line1;
	vector<string> line2;
	string temp;

	bool check;


	ifstream file1;
	ifstream file2;

	file1.open(path1, ios::in);
	file2.open(path2, ios::in);

	vector<int> save;

	if (file1.is_open() && file2.is_open())
	{
		while (!file1.eof())
		{
			getline(file1, temp);
			line1.push_back(temp);
		}

		while (!file2.eof())
		{
			getline(file2, temp);
			line2.push_back(temp);
		}

		for (int i = 0; i < line1.size(); i++)
		{
			for (int j = i; j < line2.size(); j++)
			{
				check = NWP3(line1, line2, i, j, save);
				
				if (check)
					break;
			}
		}

		NWP3_Write(line1, line2, save);

		printf("\n\n");
		for (int i = 0; i < save.size() - 1; i += 2)
			printf("%d - %d\n", save.at(i), save.at(i + 1));
	}
	else
		printf("\nNie udalo sie otworzyc pliku.\n");

	file1.close();
	file2.close();
	

	printf("\n");
	system("pause");
	return 0;
}




































int NWP(int a_len, int b_len, int a[], int b[], int** tab)
{
	for (int i = 0; i <= a_len; i++)
	{
		for (int j = 0; j <= b_len; j++)
		{
			if (i == 0 || j == 0)
				tab[i][j] = 0;
			else if (a[i - 1] == b[j - 1])
				tab[i][j] = tab[i - 1][j - 1] + 1;
			else
				tab[i][j] = max(tab[i][j - 1], tab[i - 1][j]);
		}
	}

	return tab[a_len][b_len];
}

void NWP_Write(int n, int k, int a[], int b[], int** tab)
{
	stack<int> v;

	while (n != 0 && k != 0)
	{
		if (a[n - 1] == b[k - 1])
		{
			v.push(a[n - 1]);

			n = n - 1;
			k = k - 1;
		}
		else if (tab[n][k] == tab[n - 1][k])
			n = n - 1;
		else
			k = k - 1;
	}

	while (!v.empty())
	{
		printf("%d, ", v.top());
		v.pop();
	}
}




















bool NWP3(vector<string> a, vector<string> b, int ai_len, int bj_len, vector<int>& save)
{
	int** tab;

	int n;
	int k;

	bool check = false;

	if (a.at(ai_len).size() > 0)
		n = a.at(ai_len).size() - 1;
	else
		n = a.at(ai_len).size();

	if (b.at(bj_len).size() > 0)
		k = b.at(bj_len).size() - 1;
	else
		k = b.at(bj_len).size();

	tab = new int* [n + 1];
	for (int i = 0; i <= n; i++)
		tab[i] = new int[k + 1];

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= k; j++)
		{
			if (i == 0 || j == 0)
				tab[i][j] = 0;
			else if (a.at(ai_len)[i - 1] == b.at(bj_len)[j - 1])
			{
				tab[i][j] = tab[i - 1][j - 1] + 1;
			}
			else
			{
				tab[i][j] = max(tab[i][j - 1], tab[i - 1][j]);
			}
		}
	}

	if (a.at(ai_len) == b.at(bj_len))
	{
		if (save.size() > 0)
		{
			for (int i = 0; i < save.size() - 1; i++)
			{
				if (save.at(i) == ai_len || save.at(i + 1) == bj_len)
					check = true;
			}
		}

		if (!check)
		{
			save.push_back(ai_len);
			save.push_back(bj_len);
			return true;
		}
	}

	return false;
}

void NWP3_Write(vector<string> a, vector<string> b, vector<int> save)
{
	int n = 0;
	int k = 0;

	for (int i = 0; i < save.size() - 1; i += 2)
	{
		for (int j = n; j < save.at(i); j++)
		{
			bool check = false;

			for (int l = 0; l < save.size(); l += 2)
				if (j == save.at(l))
					check = true;

			if (check)
			{
				n = save.at(i);
				continue;
			}

			printf("- %s\n", a.at(j).c_str());
			n = save.at(i);
		}

		for (int j = k; j < save.at(i + 1); j++)
		{
			bool check = false;
			for (int l = 1; l < save.size(); l += 2)
				if (j == save.at(l))
					check = true;

			if (check)
			{
				k = save.at(i + 1);
				continue;
			}

			printf("+ %s\n", b.at(j).c_str());
			k = save.at(i + 1);
		}

		printf("%s\n", b.at(save.at(i + 1)).c_str());
	}

	for (int i = n + 1; i < a.size(); i++)
		printf("- %s\n", a.at(i).c_str());

	for (int i = k + 1; i < b.size(); i++)
		printf("+ %s\n", b.at(i).c_str());
}












/*

0.	This part of the						0.	This is an important
1.	document has stayed the					1.	notice! It should
2.	same from version to					2.	therefore be located at
3.	version.  It shouldn't					3.	the beginning of this
4.	be shown if it doesn't					4.	document!
5.	change.  Otherwise, that				5.	
6.	would not be helping to					6.	This part of the
7.	compress the size of the				7.	document has stayed the
8.	changes.								8.	same from version to
9.											9.	version.  It shouldn't
10.	This paragraph contains					10.	be shown if it doesn't
11.	text that is outdated.					11.	change.  Otherwise, that
12.	It will be deleted in the				12.	would not be helping to
13.	near future.							13.	compress the size of the
14.											14.	changes.
15.	It is important to spell				15.	
16.	check this dokument. On					16.	It is important to spell
17.	the other hand, a						17.	check this document. On
18.	misspelled word isn't					18.	the other hand, a
19.	the end of the world.					19.	misspelled word isn't
20.	Nothing in the rest of					20.	the end of the world.
21.	this paragraph needs to					21.	Nothing in the rest of
22.	be changed. Things can					22.	this paragraph needs to
23.	be added after it.						23.	be changed. Things can
											24.	be added after it.
											25.	
											26.	This paragraph contains
											27.	important new additions
											28.	to this document.
*/


/*
0.	Aa										0.	X
1.	B										1.	B
2.	C										2.	Y
3.	Ad										3.	C
											4.	Ad
											5.	Z
*/

/*
	-	Aa			A: 0
	+	X			B: 0
		B			A/B: 1
	+	Y			B: 2
		C			A: 2 B: 3
		Ad			A: 3 B: 4
	+	Z			B: 5
*/


/*
0.	1		1.	1
2.	2		3.	3
4.	3		5.	4
*/