/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : 1.cpp

 * Purpose :

 * Creation Date : 26-05-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/

#include<vector>
#include<map>
#include<iostream>
#include<string>
#include<getopt.h>

#include "board.h"

Board solveBDepth(Board b, const Board & correct, int curDepth, int targetDepth, std::map<std::string,int> &boardSeen) {
	if(b == correct || curDepth > targetDepth) {
		return b;
	}
	std::vector<Board::Move> moves = b.getPossibleMoves();
	for(auto it = moves.begin(); it != moves.end(); ++it) {
		b.move(*it);
		if(boardSeen.find(b.serialize()) == boardSeen.end() ||
				boardSeen[b.serialize()] > curDepth) {
			boardSeen[b.serialize()] = curDepth;
			Board newB = solveBDepth(b,correct,curDepth+1,targetDepth,boardSeen);
			if(newB == correct) {
				return newB;
			}
		}
		//Recursive call
		b.undoLastMove();
	}
	return b;
}

Board solveBoard(Board b, const Board & correct) {
	int depth = 0;
	std::map<std::string,int> boardSeen = std::map<std::string,int>();
	//IDDFS search
	while(!(b == correct)) {
		depth ++;
		boardSeen[b.serialize()] = depth;
		b = solveBDepth(b,correct,0,depth,boardSeen);
		boardSeen.clear();
		std::cerr << depth << std::endl;
	}
	return b;
}

int main(int argc, char **argv) {
	//Options
	static const char *optString = "hsb:";
	static const char *hlpString = "--help, -h: Do this\n--solve, -s: Solve the given puzzle\n--board, -b: Supply the board in this format ie) 12345607_\n";
	static const option longOpts[] = {
		{"solve", no_argument, NULL, 's'},
		{"board", required_argument, NULL, 'b'},
		{"help", no_argument, NULL, 'h'}
	};
	int longIndex;
	std::string tempInput;
	int opt; 
	bool solve = false;
	Board b;
	do {
		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
		switch(opt) {
			case 'h':
				std::cerr << hlpString; 
				exit(0);
				break;
			case 'b':
				b =  Board(optarg);
				break;
			case 's':
				solve = true;
				break;
		}
	}while(opt != -1);
	if(solve) {
		b = solveBoard(b, Board("01234567_"));
		std::cout << b.serializeMovesMade() << std::endl;
	}
	return 0;
}
