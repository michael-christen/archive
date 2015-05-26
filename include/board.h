#ifndef __BOARD__H__
#define __BOARD__H__

#include<string>
#include<vector>

class Board {
	public:
		Board();
		Board(char * initString);
		Board(const Board &b);
		Board & operator =(const Board b);

		bool operator ==(Board b);

		std::string serialize();
		enum Move { U = 0, R = 1, D = 2, L = 3};
		static const char * const MoveNames[]; 

		class InvalidMoveError;
		class InvalidBoardError;

		std::vector<Move> getPossibleMoves();
		void makeMove(Move m);
		bool undoLastMove();
		std::vector<Move> getMovesMade();

		int getPosition();

	private:
		int pos;
		char *layout;
		std::vector<Move> movesMade;
};
#endif
