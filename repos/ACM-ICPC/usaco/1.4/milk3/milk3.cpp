/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
PROB: milk3
LANG: C++

      * File Name : milk3.cpp

 * Purpose :

 * Creation Date : 18-09-2013

 * Last Modified : Wed 18 Sep 2013 02:55:31 PM EDT

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<fstream>
using namespace std;
int capacities[3];
set<int> visited;
set<int> solns;
struct Buckets{
    int vals[3];
    Buckets()
    {
	for(int i = 0; i < 2; ++i)
	    vals[i] = 0;
	vals[2] = capacities[2];
    }
    Buckets(int a,  int b, int c)
    {
	vals[0] = a;
	vals[1] = b;
	vals[2] = c;
    }
    Buckets(const int arr[3])
    {
	for(int i = 0; i < 3; ++i)
	    vals[i] = arr[i];
    }
    Buckets(Buckets * const myBucket)
    {
	for(int i = 0; i < 3; ++i)
	    vals[i] = myBucket->vals[i];
    }

    Buckets pour(int from, int to)
    {
	int amount = min(capacities[to] - vals[to], vals[from]);
	Buckets tempBucket(this);
	tempBucket.vals[from] -= amount;
	tempBucket.vals[to] += amount;
	return tempBucket;
    }

    int identify()
    {
	return vals[0] + 20*vals[1] + 400*vals[2];
    }

    void const visit()
    {
	visited.insert(this->identify());
    }

    bool const isSolved()
    {
	return vals[0] == 0;
    }
};
void solveBuckets(Buckets myBucket)
{
    if(visited.find(myBucket.identify()) != visited.end())
	return;
    myBucket.visit();
    if(myBucket.isSolved())
	solns.insert(myBucket.vals[2]);
    for(int i = 0; i < 3; ++i)
    {
	for(int j = 0; j < 3; ++j)
	{
	    if(i == j || myBucket.vals[i] == 0 || myBucket.vals[j] == capacities[j])
		continue;
	    else
	    {
		solveBuckets(myBucket.pour(i,j));
	    }
	}
    }
}
int main()
{
    ifstream inf("milk3.in");
    inf >> capacities[0] >> capacities[1] >> capacities[2];
    inf.close();
    Buckets first;
    solveBuckets(first);
    ofstream outf("milk3.out");
    set<int>::iterator it = solns.begin();
    outf << *it;
    ++it;
    for(; it != solns.end(); ++it)
	outf << ' ' << *it;
    outf << endl;
    outf.close();
    return 0;
}

