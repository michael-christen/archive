/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: holstein
 * File Name : holstein.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Wed 23 Oct 2013 02:07:09 PM EDT
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

vector<int> vitamins;
vector<vector<int> >feed;
vector<int> scoops;
vector<int> bestScoops;
int v, g, temp;

bool feedsEm()
{
    vector<int> value(vitamins.size(), 0);
    for(size_t i = 0; i < scoops.size(); ++i)
    {
	for(size_t j = 0; j < feed[scoops[i]].size(); ++j)
	{
	    value[j] += feed[scoops[i]][j];
	}
    }
    for(size_t i = 0; i < vitamins.size(); ++i)
    {
	if(value[i] < vitamins[i])
	    return false;
    }
    return true;
}

void updateBest()
{
    if(bestScoops.empty() || bestScoops.size() > scoops.size())
	bestScoops = scoops;
    else if(bestScoops.size() == scoops.size())
    {
	sort(bestScoops.begin(), bestScoops.end());
	sort(scoops.begin(), scoops.end());
	if(scoops < bestScoops)
	    bestScoops = scoops;
    }
}

void getBestScoops(int lvl)
{
    if(feedsEm())
	updateBest();
    if(lvl >= (int)feed.size())
	return;
    //off
    getBestScoops(lvl+1);
    //on
    scoops.push_back(lvl);
    getBestScoops(lvl+1);
    scoops.pop_back();
}

int main()
{
    ifstream inf("holstein.in");
    inf >> v;
    for(int i = 0; i < v; ++i)
    {
	inf >> temp;
	vitamins.push_back(temp);
    }
    inf >> g;
    for(int i = 0; i < g; ++i)
    {
	feed.push_back(vector<int>());
	for(int j = 0; j < v; ++j)
	{
	    inf >> temp;
	    feed[feed.size()-1].push_back(temp);
	}
    }
    inf.close();
    //Could just try 2^g combinations of feed, with branch and bound
    //which would cut down considerably, and saving min Solns that
    //satisfy constraints
    getBestScoops(0);
    sort(bestScoops.begin(), bestScoops.end());
    ofstream outf("holstein.out");
    outf << bestScoops.size();
    for(size_t i = 0; i < bestScoops.size(); ++i)
	outf << ' ' << bestScoops[i] + 1;
    outf << endl;
    outf.close();
}
