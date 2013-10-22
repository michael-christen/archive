/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: checker
 * File Name : checker.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Tue 22 Oct 2013 02:41:34 PM EDT
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
	vector<int> & cols, vector<int> & diagonalUR, 
	vector<int> & diagonalDL, int n)
{
    if((int)curSol.size() == n)
    {
	solns.push_back(curSol);
	return;
    }
    
    for(int i = 0; i < n; ++i)
    {
	//bool isValid = true;
	int ddl, dur;
	ddl = n*2 - 2 - (curSol.size() - i + n - (n+1)%2);
	dur = curSol.size() + i;
	if(!cols[i] && !diagonalDL[ddl] && !diagonalUR[dur])
	{
	    curSol.push_back(i);
	    cols[i] = true;
	    diagonalDL[ddl] = true;
	    diagonalUR[dur] = true;
	    solveBoard(solns,curSol,cols,diagonalUR,diagonalDL,n);
	    diagonalUR[dur] = false;
	    diagonalDL[ddl] = false;
	    cols[i] = false;
	    curSol.pop_back();
	}
    }
}

vector<vector<int> > getBoardSolns(int n)
{
    vector<vector<int> > solns;
    vector<int> cols(n,false);
    vector<int> dUR(2*n,false);
    vector<int> dDL(2*n,false);
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
	    outf << solns[i][j]+1;
	    if(j != solns[i].size() - 1)
		outf << ' ';
	}
	outf << endl;
    }
    outf << solns.size() << endl;
    outf.close();
}
