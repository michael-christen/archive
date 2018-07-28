/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: numtri
 * File Name : numtri.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Fri 04 Oct 2013 12:09:34 AM EDT
 * Created By : Michael Christen
 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

void sumTriangle(vector<vector<int> > & triangle)
{
    int left, right;
    for(int i = 1; i < triangle.size(); ++i)
    {
	for(int j = 0; j < triangle[i].size(); ++j)
	{
	    left = right = 0;
	    if(j-1 >= 0)
	       left = triangle[i-1][j-1];
    	    if(j < triangle[i-1].size())
		right = triangle[i-1][j];
	    triangle[i][j] += max(left, right);
	}
    }
}
void printTriangle(vector<vector<int> > & triangle)
{
    for(int i = 0; i < triangle.size(); ++i)
    {
	for(int j = 0; j < triangle[i].size(); ++j)
	    cerr << triangle[i][j] << ' ';
	cerr << endl;
    }
}

int main()
{
    vector<vector<int> > triangle;
    int r, temp;
    ifstream inf("numtri.in");
    inf >> r;
    for(int i = 0; i < r; ++i)
    {
	triangle.push_back(vector<int>());
	for(int j = 0; j <= i; ++j)
	{
	    inf >> temp;
	    triangle[i].push_back(temp);
	}
    }
    inf.close();
//  printTriangle(triangle);
    sumTriangle(triangle);
//  printTriangle(triangle);
    ofstream outf("numtri.out");
    int maxElt = 0; 
    for(int i = 0; i < triangle[r-1].size(); ++i)
    {
	if(triangle[r-1][i] > maxElt)
	    maxElt = triangle[r-1][i];
    }
    //outf << *max(triangle[r-1].begin(), triangle[r-1].end()) << endl;
    outf << maxElt << endl;
    outf.close();
}
