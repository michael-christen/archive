/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
LANG: C++
PROG: pprime
 * File Name : pprime.cpp
 * Purpose :
 * Creation Date : 03-10-2013
 * Last Modified : Tue 22 Oct 2013 10:05:29 AM EDT
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
    if(n==2) return true;
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
void genPalFromVars(vector<int> &pals, int length, int position, int number)
{
    int numVars = (length - 1) / 2 + 1;
    if(position > numVars-1)
    {
	pals.push_back(number);
	return;
    }
    //number doesn't matter at zero, we're creating it
    if(position == 0)
    {
	//Special case
	if(length == 1)
	{
	    for(int i = 1; i <= 9; ++i)
		pals.push_back(i);
	    return;
	}
	for(int i = 1; i <= 9; ++i)
	    genPalFromVars(pals,length,position+1,
		    i*(int)pow(10,length-(position+1))+i);
    }
    else
    {
	//if middle
	if(length % 2 && position == length /2)
	    for(int i = 0; i <= 9; ++i)
		genPalFromVars(pals,length,position+1,
			number+ i*(int)pow(10,position));
	//if 2 vars
	else
	    for(int i = 0; i <= 9; ++i)
		genPalFromVars(pals,length,position+1,
			number+ i*(int)pow(10,length-(position+1))+
			i*(int)pow(10,position));
    }
}


//Generates palindromes with length digits
vector<int> genPalindromes(int length)
{
    vector<int> palindromes;
    assert(length >= 1);
    genPalFromVars(palindromes, length,0,0);
    return palindromes;
}

vector<int> genPrimePalindromes(int a,int b)
{
    vector<int> palindromes;
    vector<int> tempVect;
    for(int i = sizeOfInt(a); i <= sizeOfInt(b); ++i)
    {
	tempVect = genPalindromes(i);
	palindromes.insert(palindromes.end(),tempVect.begin(), tempVect.end());  
    }
/*    
      for(size_t i = 0; i < palindromes.size(); ++i)
	cerr << palindromes[i] << endl;
	*/
    //generated all palindromes
    //now filter if > b, < a or !prime
    //sort(palindromes.begin(), palindromes.end());
    vector<int> results;
    int curVal;
    for(size_t i = 0; i < palindromes.size(); ++i)
    {
	curVal = palindromes[i];
	if(curVal >= a && curVal <= b && isPrime(curVal))
	    results.push_back(curVal);
    }


    return results;
}

int main()
{
    vector<int> palindromes;
    int a, b;
    ifstream inf("pprime.in");
    inf >> a >> b;
    inf.close();
    palindromes = genPrimePalindromes(a,b);
    ofstream outf("pprime.out");
    for(size_t i = 0; i < palindromes.size(); ++i)
	outf << palindromes[i] << endl;
    outf.close();
}
