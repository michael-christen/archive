/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

      * File Name : a.cpp

         * Purpose :

	    * Creation Date : 04-10-2013

	       * Last Modified : Fri 04 Oct 2013 02:53:42 PM EDT

	          * Created By : Michael Christen

		     _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int getVal(vector<int> & pos5)
{
    long long total = 0; 
    for(size_t i = 0; i < pos5.size(); ++i)
	total += (int) (pow(10,pos5[i]) )*5;
    return total;
}

int getHighest(int num5, int num0)
{
    vector<int> num5Pos(num5, 0);
    for(int i = 0; i < num5; ++i)
	num5Pos[i] = (num0+num5-1) - i;
    int curVal = getVal(num5Pos);
    if(curVal % 90 == 0)
	return curVal;
    //Moving 5 around, except for first
    for(int i = num5-1; i >= 1; i--)
    {
	for(int j = num5Pos[i]-1;j>=0;--j)
	{
	    if(i < num5-1 && j <= num5Pos[i+1])
		break;
	    num5Pos[i] = j;
	    curVal = getVal(num5Pos);
	    if(curVal % 90 == 0)
		return curVal;
	}
    }
    if(num0 > 0)
	curVal = getHighest(num5, num0-1);
    else
	return -1;
    if(num5 > 0)
	curVal = max(curVal, getHighest(num5-1, num0));
    else if(num0 > 0)
        return 0;
    return curVal;
}

int main()
{
    int n, num5=0, num0=0, temp;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
	cin >> temp;
	if(temp == 5)
	    num5 ++;
	else
	    num0 ++;
    }
    cout << getHighest(num5, num0) << endl;
}
