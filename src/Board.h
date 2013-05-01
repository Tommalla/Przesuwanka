/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#ifndef BOARD_H
#define BOARD_H
#include <vector>

#include "Point.h"
#include "BitContainer.h"

using namespace std;

class Board {
	friend class BoardGenerator;
	private:
		int size;
		BitContainer* board;
		
		void copyToSelf(const Board &b);
		void setFieldAt(const Point& pos, const int field);
	public:
		/**
		 * @brief Tworzy nową planszę o boku podanej długości
		 * @param size Długość boku planszy. Domyślnie 4.
		 **/
		Board(int size = 4);
		Board(const Board &b);
		
		int getFieldAt(const Point& pos);
		
		~Board();
		Board& operator=(const Board &b);
};

#endif // BOARD_H
