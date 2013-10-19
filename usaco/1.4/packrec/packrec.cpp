/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
PROB: packrec
LANG: C++

 * File Name : packrec.cpp

 * Purpose :

 * Creation Date : 20-09-2013

 * Last Modified : Mon 22 Dec 2008 10:36:49 PM PST 

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct rect
{
    static int counter;
    int length, width, id;
    rect(int l, int w)
    {
	id = counter ++;
	length = l;
	width = w;
    }
    bool operator< (const rect & otherRect)
    {
	return this->id < otherRect.id;
    }

    int getWidth(bool sideWays=false)
    {
	if(sideWays)
	    return length;
	return width;
    }
    int getLength(bool sideWays=false)
    {
	if(sideWays)
	    return width;
	return length;
    }

    int getArea()
    {
	return length * width;
    }

    void print(ofstream & outf)
    {
	outf << "Length: " << length << " Width: " << width << endl;
    }
    void print()
    {
	cout << "Length: " << length << " Width: " << width << endl;
    }
};
int rect::counter = 0;

//type specifies which of the 6 configs, the rectangles are in
//sideBits is a value [0-15] that encodes which rectangles are sideways
rect getBounding(vector<rect> myRects, int type, int sideBits)
{
    int length=0, width=0, curBit, tempLength;
    int l1, l2, l3, l4, w1, w2, w3, w4;
    l1 = myRects[0].getLength(sideBits & 1);
    l2 = myRects[1].getLength(sideBits & 2);
    l3 = myRects[2].getLength(sideBits & 4);
    l4 = myRects[3].getLength(sideBits & 8);
    w1 = myRects[0].getWidth(sideBits & 1);
    w2 = myRects[1].getWidth(sideBits & 2);
    w3 = myRects[2].getWidth(sideBits & 4);
    w4= myRects[3].getWidth(sideBits & 8);

    switch (type)
    {
	case 0:
	    for(int i = 0; i < 4; ++i)
	    {
		curBit = sideBits & (int)pow(2.0,i);
		tempLength = myRects[i].getLength(curBit);
		width += myRects[i].getWidth(curBit);
		if( tempLength > length)
		    length = tempLength; 
	    }
	    break;
	case 1:
	    //Width
	    for(int i = 0; i < 3; ++i)
	    {
		curBit = sideBits & (int)pow(2.0,i);
		width += myRects[i].getWidth(curBit);
	    }
	    width = max(w4, width);
	    //Length
	    length = max(max(l1,l2),l3)+l4;
	    break;
	case 2:
	    width = max(w1 + w2, w3) + w4;
	    length = max(l4, max(l1, l2) + l3);
	    break;
	case 3:
	    width = w1 + w4 + max(w2, w3);
	    length = max( max(l1, l4), l2 + l3);
	    break;
	case 4:
	    width = max(w1, w2) + w3 + w4;
	    length = max(max(l3, l4), l1 + l2);
	    break;
	case 5:
	    if(l1 > l4)
	    {
		if(l1 > l4 + l3)
		    width = max(max(w3, w4) + w1, w2);
		else
		    width = max(w1+w4, max(w1+w3, w2+w3));
	    }
	    else if(l1 == l4)
	    {
		width = max(w1+w4, w2 + w3);
	    }
	    else
	    {
		if(l4 > l1 + l2)
		    width = max(max(w1, w2) + w4, w3);
		else
		    width = max(w4+w1, max(w4+w2, w3+w2));
	    }
	    length = max( l1+ l2,l3 + l4);
	    if(width == 8 && length == 8)
	    {
		for(size_t i = 0; i < 4; ++i)
		    myRects[i].print();
		cout << sideBits << endl;
	    }
	    //width = 200;
	    //width = max(w1,w2) + max(w3, w4);
	    break;
	default:
	    cout << "Error " << endl;
	    break;
    }
    return rect(length, width);
}

void rmDups(vector<pair<int, int> > & myVec)
{
    if(myVec.empty())
	return;
    pair<int, int> lastVal = myVec[0];
    for(int i = 1; i < (int) myVec.size(); ++i)
    {
	if(myVec[i].first == lastVal.first &&
		myVec[i].second == lastVal.second)
	{
	    myVec.erase(myVec.begin()+i);
	    --i;
	}
	else
	    lastVal = myVec[i];
    }
}

int main()
{
    int l, w;
    ifstream inf("packrec.in");
    vector<rect> myRects;
    vector<pair<int, int> > solns;
    for(int i = 0; i < 4; ++i)
    {
	inf >> l >> w;
	myRects.push_back(rect(l,w));
    }
    inf.close();
    //Try the 6 different forms
    for(int i = 0; i < 6; ++i)
    {
	//Have each rectangle take each position
	while(next_permutation(myRects.begin(), myRects.end()))
	{
	    //Make them sideways or not
	    //2^4 = 16 possibilities
	    for(int j = 0; j < 16; ++j)
	    {
		rect tempRect = getBounding(myRects, i, j);
		if(solns.empty())
		{
		    solns.push_back(make_pair(
				min(tempRect.length, tempRect.width),
				max(tempRect.length, tempRect.width)));
		}
		else
		{ 
		    int minArea = solns[0].first * solns[0].second;
		    if(tempRect.getArea() < minArea)
		    {
			solns.clear();
			solns.push_back(make_pair(
				min(tempRect.length, tempRect.width),
				max(tempRect.length, tempRect.width)));
		    }
		    else if(tempRect.getArea() == minArea)
		    {
			solns.push_back(make_pair(
				min(tempRect.length, tempRect.width),
				max(tempRect.length, tempRect.width)));
		    }
		}
	    }
	}
    }
    sort(solns.begin(), solns.end());
    rmDups(solns);

    ofstream outf("packrec.out");
    //Print stuff
    outf << solns[0].first * solns[0].second << endl;
    for(size_t i = 0; i < solns.size(); ++i)
	outf << solns[i].first << ' ' << solns[i].second << endl;
    outf.close();

}
