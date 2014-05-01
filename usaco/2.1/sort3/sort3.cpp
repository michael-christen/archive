/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: sort3
 * File Name : sort3.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Wed 23 Oct 2013 01:29:52 PM EDT
 * Created By : Michael Christen
 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

int printVector(const vector<int> & list)
{
    for(size_t i = 0; i < list.size(); ++i)
	cerr << list[i] << endl;
    return 0;
}

void mort(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int n, num1, num2, num3, temp, exchanges;
    num1 = num2 = num3 = exchanges = 0;
    vector<int> list;
    ifstream inf("sort3.in");
    inf >> n;
    for(int i = 0; i < n; ++i)
    {
	inf >> temp;
	if(temp == 1)
	    num1 ++;
	else if(temp == 2)
	    num2 ++;
	else
	    num3 ++;
	list.push_back(temp);
    }
    inf.close();

    //0 -> num1 should be 1's
    //num1 -> num1 + num2 should be 2's
    //num1 + num2 -> num1+num2+num3 should be 3's
    for(int i = 0; i < num1; ++i)
    {
	if(list[i] == 2)
	{
	    for(int j = num1; j < num1+num2+num3; ++j)
	    {
		if(list[j] == 1)
		{
		    exchanges ++;
		    mort(&list[i], &list[j]);
		    break;
		}
	    }
	}
	else if(list[i] == 3)
	{
	    for(int j = num3+num2+num1-1; j >= num1; --j)
	    {
		if(list[j] == 1)
		{
		    exchanges ++;
		    mort(&list[i], &list[j]);
		    break;
		}
	    }
	}
    }
    for(int i = num1; i < num1+num2; ++i)
    {
	if(list[i] != 2)
	{
	    for(int j = num3+num2+num1-1; j >= num1+num2; --j)
	    {
		if(list[j] == 2)
		{
		    exchanges ++;
		    mort(&list[i], &list[j]);
		    break;
		}
	    }
	}
    }
    //printVector(list);
    ofstream outf("sort3.out");
    outf << exchanges << endl;
    outf.close();
}
