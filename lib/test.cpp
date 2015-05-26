/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : 1.cpp

 * Purpose :

 * Creation Date : 26-05-2015

 * Created By : Michael Christen

 _._._._._._._._._._._._._._._._._._._._._.*/
#include<vector>
#include<iostream>

#include "board.h"

int main() {
	Board b;
	b.print();
	b.move(Board::U);
	b.print();
	b.move(Board::L);
	b.print();
	std::cout << b.serializeMovesMade() << '\n';
	return 0;
}
