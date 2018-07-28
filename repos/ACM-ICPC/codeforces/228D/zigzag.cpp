/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : zigzag.cpp

 * Purpose :

 * Creation Date : 17-09-2013

 * Last Modified : Tue 17 Sep 2013 09:20:10 AM EDT

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
long long zigSeq(int i, int z)
{
    long long result = i % (2*(z-1));
    if(result > z)
	return 2*z - result;
    else if(result > 0)
	return result;
    else
	return 2;
}

long long zigZag(const vector<long long>& arr, int l, int r, int z)
{
    long long total = 0;
    for(int i = l-1; i < r; ++i)
    {
	total += arr[i] * zigSeq(i+2-l, z);
    }
    return total;
}

int main()
{
    int n;
    vector<long long> myArr;
    long long temp;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
	cin >> temp;
	myArr.push_back(temp);
    }
    cin >> n;
    int optype, l, r, z;
    long long p, v;
    //Now n represents # operations
    for(int i = 0; i < n; ++i)
    {
	cin >> optype;
	//Assignment
	if(optype == 1)
	{
	    cin >> p >> v;
	    myArr[p-1] = v;
	}
	//ZigZag
	else
	{
	    cin >> l >> r >> z;
	    cout << zigZag(myArr, l, r, z) << endl; 
	}
    }

}
