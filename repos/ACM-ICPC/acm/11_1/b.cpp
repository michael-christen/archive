/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : b.cpp

   * Purpose :

   * Creation Date : 01-11-2013

   * Last Modified : Fri 01 Nov 2013 06:50:11 PM EDT

   * Created By : Michael Christen

   _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct Cards {
    vector<int> cards;
    Cards flip() {
	for(size_t i = 0; i < cards.size(); ++i) {
	    cards[i] *= -1;
	}
	reverse(cards.begin(), cards.end());
	return *this;
    }
    void insert(Cards otherCards) {
	for(size_t i = 0; i < otherCards.cards.size(); ++i) {
	   cards.push_back(otherCards.cards[i]);
	} 
     }
    void print() {
	for(size_t i = 0; i < cards.size(); ++i) {
	    if(cards[i] > 0) {
		cout << " " << cards[i];
	    }
	} 
    }
};

void topFlip( vector<vector<Cards> > & cardBoard, int & t, 
	int & b, int & l, int & r) {
    for(int i = l; i <= r; ++i) {
	cardBoard[t+1][i].insert(cardBoard[t][i].flip());
    }
    t ++;
}
void botFlip( vector<vector<Cards> > & cardBoard, int & t, 
	int & b, int & l, int & r) {
    for(int i = l; i <= r; ++i) {
	cardBoard[b-1][i].insert(cardBoard[b][i].flip());
    }
    b --;
}
void leftFlip( vector<vector<Cards> > & cardBoard, int & t, 
	int & b, int & l, int & r) {
    for(int i = t; i <= b; ++i) {
	cardBoard[i][l+1].insert(cardBoard[i][l].flip());
    }
    l ++;
}
void rightFlip( vector<vector<Cards> > & cardBoard, int & t, 
	int & b, int & l, int & r) {
    for(int i = t; i <= b; ++i) {
	cardBoard[i][r-1].insert(cardBoard[i][r].flip());
    }
    r--;
}

int main() {
    int n, m, caseNum = 1;
    vector<vector<Cards> > cardBoard;
    cin >> n >> m;
    while(n || m) {

	//Init cardBoard
	for(int i = 0; i < n; ++i) {
	    cardBoard.push_back(vector<Cards>());
	    for(int j = 0; j < m; ++j) {
		Cards aCard;
		int temp;
		cin >> temp;
		aCard.cards.push_back(temp);
		cardBoard[i].push_back(aCard);
	    }
	}
	int t=0,b=n-1,l=0,r=m-1;
	//Do flips
	for(int i = 0; i < n+m-2; ++i) {
	    char temp;
	    cin >> temp;
	    switch(temp) {
		case 'T':
		    topFlip(cardBoard,t,b,l,r);
		    break;
		case 'B':
		    botFlip(cardBoard,t,b,l,r);
		    break;
		case 'L':
		    leftFlip(cardBoard,t,b,l,r);
		    break;
		case 'R':
		    rightFlip(cardBoard,t,b,l,r);
		    break;
	    }
	}

	//Print deck
	cout << "Case " << caseNum ++ << ':';
	cardBoard[t][l].print();
	cout << endl;

	cardBoard.clear();
	cin >> n >> m;
    }
}
