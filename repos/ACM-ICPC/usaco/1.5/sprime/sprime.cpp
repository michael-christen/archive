/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: sprime
 * File Name : sprime.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Tue 22 Oct 2013 12:55:22 PM EDT
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

bool isPrime(int n)
{
    int sqrtI = (int) sqrt(n);
    if(n==1) return false;
    if(n==2) return true;
    if(n%2 == 0) return false;
    for(int i = 3; i <= sqrtI; i+=2)
	if(n % i == 0)
	    return false;
    return true;
}
void recursiveSuperPrimes(vector<int> & sprimes,int length,int pos, int num)
{
    if(pos == length)
    {
	sprimes.push_back(num);
	return;
    }
    for(int i = 1; i <= 9; ++i)
    {
	int newNum = (pos == 0) ? i : num*10 + i;
	if(isPrime(newNum))
	    recursiveSuperPrimes(sprimes,length,pos+1,newNum);
    }
}

int main()
{
    vector<int> superprimes;
    int a;
    ifstream inf("sprime.in");
    inf >> a;
    inf.close();
    recursiveSuperPrimes(superprimes,a,0,0);
    ofstream outf("sprime.out");
    for(size_t i = 0; i < superprimes.size(); ++i)
	outf << superprimes[i] << endl;
    outf.close();
}
