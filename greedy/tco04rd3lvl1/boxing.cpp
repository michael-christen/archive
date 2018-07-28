/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

      * File Name : boxing.cpp

         * Purpose :

	    * Creation Date : 21-10-2013

	       * Last Modified : Mon 21 Oct 2013 04:05:08 PM EDT

	          * Created By : Michael Christen

		     _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Boxing {
    private:
	vector<vector<int>::iterator> iterators;
	vector<vector<int> > vectors;
	//Returns min, -1 if no interval
	pair<int,int> getInterval()
	{
	    int start = -1, end = -1, count=0;
	    //Establish minimum
	    for(size_t i = 0; i < iterators.size(); ++i)
	    {
		if(iterators[i] != vectors[i].end())
		    if(*iterators[i] < start || start == -1)
			start = *iterators[i];
	    }
	    //Check if all within 1000 from min
	    vector<int> solns;
	    for(size_t i = 0; i < iterators.size(); ++i)
	    {
		if(iterators[i] != vectors[i].end())
		{
		    if(*iterators[i] - start  < 1000)
		    {
			solns.push_back(*iterators[i]);
			count ++;
		    }
		}
	    }
	    if(count >= 3)
	    {
		sort(solns.begin(), solns.end());
		end = solns[2];
	    }
	    return make_pair(start, end);
	}
	bool atItsEnd()
	{
	    int numAtEnd = 0;
	    for(size_t i = 0; i < iterators.size(); ++i)
	    {
		if(iterators[i] == vectors[i].end())
		    numAtEnd ++;
	    }
	    return numAtEnd == (int)iterators.size();
	}

	//Moves all iterators so value greater than a
	void movePast(int a)
	{
	    for(size_t i = 0; i < iterators.size(); ++i)
	    {
		while(iterators[i] != vectors[i].end() && 
			*iterators[i] <= a)
		    iterators[i] ++;
	    }
	}
    public:
	int maxCredit(vector<int> a, vector<int> b, vector<int>
		c,vector<int> d, vector<int> e)
	{
	    //Initialization
	    iterators.clear();
	    vectors.clear();
	    vectors.push_back(a);
	    iterators.push_back(vectors[0].begin());
	    vectors.push_back(b);
	    iterators.push_back(vectors[1].begin());
	    vectors.push_back(c);
	    iterators.push_back(vectors[2].begin());
	    vectors.push_back(d);
	    iterators.push_back(vectors[3].begin());
	    vectors.push_back(e);
	    iterators.push_back(vectors[4].begin());
	    pair<int,int> interval;
	    int punches = 0;
	    while(!atItsEnd())
	    {
		interval = getInterval();
		cerr << interval.first << ' ' << interval.second << endl;
		if(interval.second != -1)
		{
		    punches ++;
		    movePast(interval.second);
		}
		else
		    movePast(interval.first);
	    }
	    return punches;
	}
};

int main()
{
    vector<int> a = {1,2,3,4,5,6};
    vector<int> b = {1,2,3,4,5,6,7};
    vector<int> c = {1,2,3,4,5,6};
    vector<int> d = {0,1,2};
    vector<int> e = {1,2,3,4,5,6,7,8};
    Boxing box;
    cout << box.maxCredit(a,b,c,d,e) << endl;
}
