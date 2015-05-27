/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : board.cpp

 * Purpose :

 * Creation Date : 26-05-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<algorithm>
#include<iostream>

#include "board.h"

void Board::init() {
		layout = new char[10];
		strcpy(layout, "01234567_"); 
		movesMade = std::vector<Move>();
}

Board::Board()
	:pos(8){
	init();
}

Board::Board(char * initString){
	init();
	strcpy(layout,initString);
	/*
	for(int i = 0; i < 9; ++i) {
		layout[i] = initString[i];
	}
	*/
	pos = strstr(layout, "_") - layout;
	if(pos < 0) { 
		throw InvalidBoardError();
	}
	//TODO: Verify good input
}

Board::Board(const Board &b) {
	init();
	strcpy(layout,b.layout);
	pos = b.pos;
	movesMade = b.movesMade;
}

Board::~Board() {
	delete [] layout;
}

bool Board::operator ==(const Board &b) {
	return strcmp(b.layout,layout) == 0;
}


Board & Board::operator =(const Board &b) {
	strcpy(layout,b.layout);
	pos = b.pos;
	movesMade = b.movesMade;
	return *this;
}

std::string Board::serialize() {
	return std::string(layout);
}
void Board::print() {
	std::string s = "";
	int x = 0, y = 0;
	for(int i = 0; i < 9; ++i) {
		if(i != 0 && i%3 == 0) {
			s += '\n';
		}
		s += layout[i];
	}
	s += "\n\n";
	std::cout << s;
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

void Board::move(Move m) {
	int v = pos + MoveVals[m];
	if(v < 0 || v > 8) {
		throw InvalidMoveError();
	}
	posSwap(v);
	movesMade.push_back(m);
}

bool Board::undoLastMove() {
	if(movesMade.empty()) {
		return false;
	} else {
		Move m = movesMade.back();
		posSwap(pos - MoveVals[m]);
		movesMade.pop_back();
		return true;
	}
}

std::vector<Board::Move> Board::getMovesMade() {
	return movesMade;
}

std::string Board::serializeMovesMade() {
	std::string s = "";
	bool first = true;
	for(auto it = movesMade.begin(); it != movesMade.end(); it++) {
		if(!first) {
			s += ' ';
		}
		s += MoveNames[*it];
		first = false;
	}
	return s;
}

int Board::getPosition() {
	return pos;
}

void Board::posSwap(int newPos) {
	char temp = layout[pos];
	layout[pos] = layout[newPos];
	layout[newPos] = temp;
	pos = newPos;
}

const char * const Board::MoveNames[] = {"U", "R", "D", "L"}; 
int const Board::MoveVals[] = {-3, 1, 3, -1}; 
