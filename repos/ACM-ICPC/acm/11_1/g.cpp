/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

   * File Name : g.cpp

   * Purpose :

   * Creation Date : 01-11-2013

   * Last Modified : Fri 01 Nov 2013 08:18:51 PM EDT

   * Created By : Michael Christen

   _._._._._._._._._._._._._._._._._._._._._.*/
#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int v, o, m, caseNum = 1;

    cin >> v >> o >> m;
    while(v || o || m) {
	vector<vector<int> > board(110,vector<int>(110,0));
	vector<pair<int,int> > vampires;
	vector<vector<int> > vampEmb(v,vector<int>());
	//Setup vampires
	for(int i = 0; i < v; ++i) {
	    int x, y;
	    cin >> x >> y;
	    vampires.push_back(make_pair(x,y));
	}
	//Fill in humans
	for(int i = 0; i < o; ++i) {
	    int x, y;
	    cin >> x >> y;
	    board[x][y] = -1;
	}
	//Fill in mirrors
	for(int i =0; i < m; ++i) {
	    int x1, y1, x2, y2;
	    char tc;
	    cin >> tc;
	    int dirVal=0;
	    switch(tc) {
		case 'N':
		    dirVal = 1;
		    break;
		case 'E':
		    dirVal = 2;
		    break;
		case 'S':
		    dirVal = 3;
		    break;
		case 'W':
		    dirVal = 4;
		    break;
	    }
	    //cerr << tc << " generated " << dirVal << endl;
	    cin >> x1 >> y1 >> x2 >> y2;
	    for(int xi = min(x1,x2); xi <= max(x1,x2); ++xi) {
		for(int yi = min(y1,y2); yi <= max(y1,y2); ++yi) {
		    board[xi][yi] = dirVal;
		}
	    }
	}
	//Look for each vampire
	for(size_t i = 0; i < vampires.size(); ++i) {
	    int xBase = vampires[i].first;
	    int yBase = vampires[i].second;
	    //Look in opposite dir of dirVal
	    //ie) look 3 (S) will actually go north
	    for(int dir = 1; dir <= 4; ++dir) {
		int x = xBase;
		int y = yBase;
		while(x >= 0 && x < (int)board.size() &&
			y >= 0 && y < (int)board[x].size() &&
			board[x][y] == 0) {
		    switch(dir) {
			case 1:
			    --y;
			    break;
			case 2:
			    --x;
			    break;
			case 3:
			    ++y;
			    break;
			case 4:
			    ++x;
			    break;
		    }
		}

		/*
		if(x >= 0 && x < (int)board.size() &&
			y >= 0 && y < (int)board[x].size()) {
		    cerr << "Vampire " << i << " stopped at " << 
			x << " " << y << " with dir " << dir <<
			" and board " << board[x][y] << endl;
		}
		*/
		if(x >= 0 && x < (int)board.size() &&
			y >= 0 && y < (int)board[x].size() &&
			board[x][y] == dir) {
		    vampEmb[i].push_back((dir+1)%4+1);
		}
	    }
	}

	//Output
	cout << "Case " << caseNum++ << ":\n";
	bool anyVamps = false;
	for(size_t i = 0; i < vampEmb.size(); ++i) {
	    if(!vampEmb[i].empty()) {
		anyVamps = true;
		vector<string> output;
		for(size_t j = 0; j < vampEmb[i].size(); ++j) {
		    switch(vampEmb[i][j]) {
			case 1:
			    output.push_back("north");
			    break;
			case 2:
			    output.push_back("east");
			    break;
			case 3:
			    output.push_back("south");
			    break;
			case 4:
			    output.push_back("west");
			    break;
		    }
		}
		sort(output.begin(), output.end());
		cout << "vampire " << i+1;
		for(size_t j = 0; j < output.size(); ++j) {
		    cout <<  ' ' << output[j];
		}
		cout << endl;
	    }
	}
	if(!anyVamps) {
	    cout << "none\n";
	}
	cin >> v >> o >> m;
    }
}
