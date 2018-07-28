/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

      * File Name : b.cpp

         * Purpose :

	    * Creation Date : 04-10-2013

	       * Last Modified : Fri 04 Oct 2013 12:14:09 PM EDT

	          * Created By : Michael Christen

		     _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int n, temp;
    cin >> n;
    vector<vector<int> > numPos(10020,vector<int>());
    for(int i = 0; i < n; ++i)
    {
	cin >> temp;
	numPos[temp].push_back(i);
    }
    int commonDiff, lastPos;
    vector<pair<int,int> > output;
    for(int i = 0; i < 10010; ++i)
    {
	commonDiff = 0;
	lastPos = -1;
	for(size_t j = 0; j < numPos[i].size(); ++j)
	{
	    if(lastPos != -1)
	    {
		if(commonDiff == 0)
		    commonDiff = numPos[i][j] - lastPos;
		else if(numPos[i][j] - lastPos != commonDiff)
		{
		    commonDiff = -1;
		    break;
		}
	    }
	    lastPos = numPos[i][j];
	}
	if(lastPos != -1 && commonDiff != -1)
	    output.push_back(make_pair(i,commonDiff));
    }
    cout << output.size() << endl;
    for(size_t i = 0; i < output.size(); ++i)
	cout << output[i].first << ' ' << output[i].second << endl;
    
    /*
    for(int i = 0; i < n; ++i)
    {
	cout << i << ": ";
	for(int j = 0; j < numPos[i].size(); ++j)
	{
	    cout << numPos[i][j] << ' ';
	}
	cout << endl;
    }
    */
}
