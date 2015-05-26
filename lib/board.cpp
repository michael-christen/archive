/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : board.cpp

 * Purpose :

 * Creation Date : 26-05-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<algorithm>

#include "board.h"

Board::Board()
	:layout("01234567_"), pos(9){
		 movesMade = std::vector<Move>();
}

Board::Board(char * initString){
	Board();
	layout = initString;
	pos = strstr(layout, "_") - layout;
	if(pos < 0) { 
		throw InvalidBoardError();
	}
	//TODO: Verify good input
}

bool Board::operator ==(const Board &b) {
	return strcmp(b.layout,layout) == 0;
}

std::string Board::serialize() {
	return std::string(layout);
}
std::string Board::print() {
	std::string s = "";
	int x = 0, y = 0;
	for(int i = 0; i < 9; ++i) {
		if(i != 0 && i%3 == 0) {
			s += '\n';
		}
		s += layout[i];
	}
	return s;
}

std::vector<Board::Move> Board::getPossibleMoves() {
	std::vector<Move> moves = std::vector<Move>();
	if(pos/3 > 0) {
		moves.push_back(U);
	} if(pos/3 < 2) {
		moves.push_back(D);
	} if(pos%3 > 0) {
		moves.push_back(L);
	} if(pos%3 < 2) {
		moves.push_back(R);
	}
	return moves;
}

void Board::makeMove(Move m) {
	//TODO: check for invalid moves
	if(m == U) {
		posSwap(pos-3);
	} else if(m == D) {
		posSwap(pos+3);
	} else if(m == L) {
		posSwap(pos-1);
	} else if(m == R) {
		posSwap(pos+1);
	}
}

void Board::posSwap(int newPos) {
	char temp = layout[pos];
	layout[pos] = layout[newPos];
	layout[newPos] = temp;
	pos = newPos;
}

const char * const Board::MoveNames[] = {"U", "R", "D", "L"}; 
