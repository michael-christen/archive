/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

      * File Name : 3nplus1.cpp

         * Purpose :

	    * Creation Date : 16-09-2013

	       * Last Modified : Mon 16 Sep 2013 06:05:28 PM EDT

	          * Created By : Michael Christen

		     _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int getCycleLength(int n)
{
    int count = 1;
    while(n != 1)
    {
	count ++;
	if(n%2)
	    n = 3*n + 1;
	else
	    n = n / 2;
    }
    return count;
}

int getMaxCycle(int low, int hi)
{
    int maxCycle = 0;
    int tempCycle;
    for(int i = low; i <= hi; ++i)
    {
	tempCycle = getCycleLength(i);
	if(tempCycle > maxCycle)
	    maxCycle = tempCycle;
    }
    return maxCycle;
}

int main()
{
    int i, j;
    cin >> i >> j;
    while(cin.good())
    {
	cout << i << ' ' << j << ' ' << getMaxCycle(i,j) << endl;
	cin >> i >> j;
    }
}
