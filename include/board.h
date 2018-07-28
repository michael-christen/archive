#ifndef __BOARD__H__
#define __BOARD__H__

#include<string>
#include<cstring>
#include<vector>

class Board {
	public:
		enum Move { U = 0, R = 1, D = 2, L = 3};
		static const char * const MoveNames[]; 
		static int const MoveVals[];

		class InvalidMoveError{};
		class InvalidBoardError{};

		Board();
		Board(char * initString);
		//TODO
		Board(const Board &b);
		Board & operator =(const Board &b);
		//NOTODO

		~Board();

		bool operator ==(const Board &b);

		std::string serialize();
		void print();

		std::vector<Move> getPossibleMoves();
		void move(Move m);
		bool undoLastMove();

		std::vector<Move> getMovesMade();
		std::string serializeMovesMade();

		int getPosition();

	private:
		int pos;
		char *layout;
		std::vector<Move> movesMade;

		void posSwap(int newPos);
		void init();
};
#endif
