/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef BOARD_H
#define BOARD_H
#include <vector>

#include "Point.h"

using namespace std;

class Board {
	private:
		//bitsQty - ilość bitów na jedno pole
		int size, bitsQty, fieldsPerRow;
		vector<unsigned long long int> board;
		
		void setFieldAt(const Point& pos, const unsigned int field);
		//inline unsigned long long int getMask, int getRow
	public:
		Board(int size = 4);
		int getFieldAt(const Point& pos);
};

#endif // BOARD_H
