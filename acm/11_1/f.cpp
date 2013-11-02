/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : f.cpp

   * Purpose :

   * Creation Date : 01-11-2013

   * Last Modified : Fri 01 Nov 2013 06:15:35 PM EDT

   * Created By : Michael Christen

   _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct Precint {
    int population, curPercentage, maxIncrease, money;
};

double getPercent(Precint p) {
    return p.curPercentage + (p.money/(10.1+p.money))*p.maxIncrease;
}

double getPeople(Precint p) {
    return p.population * getPercent(p)/100.0;
}

int getCount(vector<Precint> precints) {
    int count = 0;
    for(size_t i = 0; i < precints.size(); ++i) {
	count += (int) (getPeople(precints[i])+.5);
    }
    return count;
}

int main() {
    int moneyLeft, numP, caseNum=1;
    vector<Precint> precints;
    cin >> moneyLeft >> numP;
    while(moneyLeft || numP) {
	for(int i = 0; i < numP; ++i) {
	    Precint temp;
	    cin >> temp.population >> temp.curPercentage >> temp.maxIncrease;
	    temp.money = 0;
	    precints.push_back(temp);
	}

	while(moneyLeft) {
	    //search through precints and find one with most increase
	    //per money spent
	    int maxIncrease = 0;
	    int index = 0;
	    for(size_t i = 0; i < precints.size(); ++i) {
		double tempPeople = getPeople(precints[i]);
		precints[i].money += 1;
		int diffPeople = (int)(getPeople(precints[i])+.5) - 
		    (int)(tempPeople+.5);
		if(diffPeople > maxIncrease) {
		    maxIncrease = diffPeople;
		    index = i;
		}
		precints[i].money -= 1;
	    }
	    precints[index].money += 1;
	    moneyLeft --;
	}

	//Get best for 0
	while(true) {
	    break;
	    for(size_t i = 0; i < precints.size(); ++i) {

	    }
	}


	cout << "Case " << caseNum++ << ": " << getCount(precints) << endl;
	cout << 0 << ':' << precints[0].money;
	for(size_t i = 1; i < precints.size(); ++i) {
	    cout << ' ' << i << ':' << precints[i].money;
	}
	cout << endl;

	precints.clear();
	cin >> moneyLeft >> numP;
    }
}
