/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: frac1
 * File Name : frac1.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Wed 23 Oct 2013 12:46:41 PM EDT
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

const double epsilon = 1e-10;

bool isEqual(const pair<int, int> a, const pair<int,int> b)
{
    double aVal, bVal;
    aVal =  (a.first+0.0)/a.second;
    bVal = (b.first+0.0)/b.second;
    return abs(aVal - bVal) < epsilon;
}

bool isSmaller(pair<int,int> a, pair<int,int> b)
{
    double aVal, bVal;
    aVal =  (a.first+0.0)/a.second;
    bVal = (b.first+0.0)/b.second;
    //~equal
    if(isEqual(a,b)) 
	return a.second < b.second;
    else 
	return aVal < bVal;
}

int main()
{
    int n;
    vector<pair<int,int> > fracs;
    ifstream inf("frac1.in");
    inf >> n;
    inf.close();
    fracs.push_back(make_pair(0,1));
    fracs.push_back(make_pair(1,1));
    for(int i = 2; i <= n; ++i)
    {
	for(int j = 1; j < i; ++j)
	{
	    fracs.push_back(make_pair(j,i));
	}
    }
    //sorted by size and then by size of smaller
    sort(fracs.begin(),fracs.end(),isSmaller);
    //get rid of same fracs by getting rid of one with larger base
    for(vector<pair<int,int> >::iterator it = fracs.begin(); 
	    it != fracs.end(); ++it)
    {
	vector<pair<int,int> >::iterator jt = it + 1;
	while(jt != fracs.end() && isEqual(*it, *jt))
	{
	    fracs.erase(jt);
	    jt = it + 1;
	}
    }
    ofstream outf("frac1.out");
    for(size_t i = 0; i < fracs.size(); ++i)
	outf << fracs[i].first << '/' << fracs[i].second << endl;
    outf.close();
}
