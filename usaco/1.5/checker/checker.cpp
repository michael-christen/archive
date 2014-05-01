/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: checker
 * File Name : checker.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Wed 23 Oct 2013 12:15:09 AM EDT
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

//vector<vector<int> > solns;
vector<int> curSol;
vector<int> cols;
vector<int> diagonalUR;
vector<int> diagonalDL;
int n;
int normCount;
int extraCount;
ofstream outf;

void solveBoard(int max)
{
    if((int)curSol.size() == n)
    {
	normCount ++;
	if(normCount <= 3)
	{
	    for(size_t j = 0; j < curSol.size(); ++j)
	    {
		outf << curSol[j]+1;
		if(j != curSol.size() - 1)
		    outf << ' ';
	    }
	    outf << endl;
	}
	/*
	else
	{
	    cerr << normCount << ": ";
	    for(size_t j = 0; j < curSol.size(); ++j)
	    {
		cerr << curSol[j]+1;
		if(j != curSol.size() - 1)
		    cerr << ' ';
	    }
	    cerr << endl;
	}
	*/

	if(n > 6 && curSol[0] < n/2)
	{
	    //cerr << "copying\n";
	    extraCount++;
	}
	return;
    }
    
    for(int i = 0; i < max; ++i)
    {
	int ddl, dur;
	ddl = n*2 - 1 - (curSol.size() - i + n);
	dur = curSol.size() + i;
	assert(ddl >= 0);
	if(ddl < 0)
	    ddl = 0;

	if(!cols[i] && !diagonalDL[ddl] && !diagonalUR[dur])
	{
	    curSol.push_back(i);
	    cols[i] = diagonalDL[ddl] = diagonalUR[dur] = true;
	    solveBoard(n);
	    diagonalUR[dur] = diagonalDL[ddl] = cols[i] = false;
	    curSol.pop_back();
	}
    }
}

void getBoardSolns()
{
    cols = vector<int>(n,false);
    diagonalUR = vector<int>(2*n,false);
    diagonalDL = vector<int>(2*n,false);
    curSol = vector<int>();
    //cerr << "Calling solveboard first\n";
    solveBoard(n > 6 ? (n+1)/2 : n);
    //cerr << "finished solveboard with val: " << extraCount << " and "
//	<< normCount << " for: " << extraCount + normCount << endl; 
}

//This is basically the n queens problem
int main()
{
    extraCount = normCount = 0;
    ifstream inf("checker.in");
    inf >> n;
    //cerr << n << endl;
    inf.close();
    outf.open("checker.out");
    getBoardSolns();
    outf << extraCount + normCount<< endl;
    outf.close();
}
