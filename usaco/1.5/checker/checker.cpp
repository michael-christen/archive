/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: checker
 * File Name : checker.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Tue 22 Oct 2013 01:53:54 PM EDT
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

struct VectorComparator {
      bool operator() (vector<int> a,vector<int> b) { 
	  return (a.size()<b.size());
      }
} vComp;

//Checking if placing checker at [board.size()][place] 
//is valid (rows, columns, diagonals)
//Way we are placing, don't need to check rows
//cols (if any # is same)
//diagonal (same slope, kind of)
/*
bool validPlace(const vector<int> & board, int place)
{
    
}
*/

//vector<bool> columns, vector<bool> diagonal/, vector<bool> diagonalUpRight
void solveBoard(vector<vector<int> > &solns, vector<int> curSol,
	vector<bool> & cols, vector<bool> & diagonalUR, 
	vector<bool> & diagonalDL, int n)
{
    if((int)curSol.size() == n)
    {
	solns.push_back(curSol);
	return;
    }
    
    for(int i = 1; i <= n; ++i)
    {
	bool isValid = true;
	for(int k = curSol.size() - 1, j = 1; k >= 0; --k, ++j)
	{
	    //same column, \,  /
	    if(curSol[k] == i || curSol[k] == i -j || curSol[k] == i + j)
	    {
		isValid = false;
		break;
	    }
	}
	if(isValid)
	{
	    curSol.push_back(i);
	    solveBoard(solns,curSol,cols,diagonalUR,diagonalDL,n);
	    curSol.pop_back();
	}
    }
}

vector<vector<int> > getBoardSolns(int n)
{
    vector<vector<int> > solns;
    vector<bool> cols(n,false);
    vector<bool> dUR(n,false);
    vector<bool> dDL(n,false);
    solveBoard(solns, vector<int>(), cols, dUR, dDL, n);
    return solns;
}
//This is basically the n queens problem
int main()
{
    int n;
    ifstream inf("checker.in");
    inf >> n;
    inf.close();
    vector<vector<int> > solns = getBoardSolns(n);
    ofstream outf("checker.out");
//    sort(solns.begin(),solns.end(), vComp);
    for(size_t i = 0; i < solns.size() && i < 3; ++i)
    {
	for(size_t j = 0; j < solns[i].size(); ++j)
	{
	    outf << solns[i][j];
	    if(j != solns[i].size() - 1)
		outf << ' ';
	}
	outf << endl;
    }
    outf << solns.size() << endl;
    outf.close();
}
