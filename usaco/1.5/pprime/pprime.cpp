/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: pprime
 * File Name : pprime.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Tue 22 Oct 2013 12:01:53 AM EDT
 * Created By : Michael Christen
 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

bool isPrime(int n)
{
    int sqrtI = (int) sqrt(n);
    if(n%2 == 0) return false;
    for(int i = 3; i <= sqrtI; i+=2)
	if(n % i == 0)
	    return false;
    return true;
}

int sizeOfInt(int n)
{
    int i = 0;
    while(n != 0)
    {
	n /= 10;
	i++;
    }
    return i;
}

vector<int> genPrimePalindromes(int a,int b)
{
    vector<int> palindromes;
    //generate palindromes recursively
    //start with size 1,then grow on outside
    //easy for odd, what about even, grow off of previous even
    for(int i = 1; i <= 9; ++i)
	palindromes.push_back(i);
    for(int i = 1; i <= 9; ++i)
	palindromes.push_back(10*i + i);
    int curVal = 99;
    int oldSize = 0;
    bool firstRun;
    for(int j = 0; sizeOfInt(curVal) <= sizeOfInt(b); ++j)
    {
	int size = sizeOfInt(palindromes[j]);
	if(size != oldSize)
	{
	    oldSize = size;
	    firstRun = true;
	}
	for(int i = 1; i <= 9; ++i)
	{
	    if(firstRun)
	    {
		//0's 
		curVal = (int)(pow(10,size+1))*i + i;
		palindromes.push_back(curVal);
	    }

	    curVal = (int)(pow(10,size+1))*i + 10*palindromes[j] + i;
	    palindromes.push_back(curVal);
	    if(sizeOfInt(curVal) > sizeOfInt(b))
		break;
	}
	firstRun = false;
    }
    //generated all palindromes
    //now filter if > b, < a or !prime
    sort(palindromes.begin(), palindromes.end());
    vector<int> results;
    for(size_t i = 0; i < palindromes.size(); ++i)
    {
	curVal = palindromes[i];
	if(curVal >= a && curVal <= b && isPrime(curVal))
	    results.push_back(curVal);
    }


    for(size_t i = 0; i < results.size(); ++i)
	cerr << results[i] << endl;
    return results;
}

int main()
{
    int a, b;
    vector<int> palindromes;
    ifstream inf("pprime.in");
    inf >> a >> b;
    inf.close();
    palindromes = genPrimePalindromes(a,b);
    ofstream outf("pprime.out");
    for(size_t i = 0; i < palindromes.size(); ++i)
	outf << palindromes[i] << endl;
    outf.close();
}
