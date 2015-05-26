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

const char * const Board::MoveNames[] = {"U", "R", "D", "L"}; 
