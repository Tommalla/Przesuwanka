/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cassert>
#include <cmath>

#include "Board.h"

void Board::setFieldAt (const Point& pos, const unsigned int field) {
	assert(field < this->size * this->size);
	assert(pos.x < this->size && pos.y < this->size);
	
	int row = (pos.y * this->size + pos.x) / this->fieldsPerRow;	//TUTAJ PEWNIE BĘDZIE DEBUG
	int leftOver = (pos.y * this->size + pos.x) % this->fieldsPerRow;
	
	unsigned long long int mask = field;
	mask <<= 64 - leftOver / this->bitsQty; 
	
	this->board[row] |= mask;
	return;	//TODO sprawdź tę metodę dobrze!
}

Board::Board (int size) {
	this->size = size;
	
	this->bitsQty = ceil(2.0 * log2(size));
	this->fieldsPerRow = 64 / bitsQty;
	this->board.resize(ceil(double(size * size) / double(this->fieldsPerRow)));
}

int Board::getFieldAt (const Point& pos) {
	assert(pos.x < this->size && pos.y < this->size);
}