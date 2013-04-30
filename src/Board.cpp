/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cassert>
#include <cmath>

#include "Board.h"

void Board::copyToSelf (const Board& b) {
	this->size = b.size;
	this->board = new BitContainer(*b.board);
}


void Board::setFieldAt (const Point& pos, const int field) {
	assert(field < this->size * this->size);
	assert(pos.x < this->size && pos.y < this->size);
	
	this->board->setValue(this->size * pos.y + pos.x, field);
}

Board::Board (int size) {
	this->size = size;
	this->board = new BitContainer(size * size, size);
}

Board::Board (const Board& b) {
	this->copyToSelf(b);
}

Board::~Board() {
	delete this->board;
}

Board& Board::operator= (const Board& b) {
	this->copyToSelf(b);
	return *this;
}


int Board::getFieldAt (const Point& pos) {
	assert(pos.x < this->size && pos.y < this->size);
	
	return this->board->getValue(this->size * pos.y + pos.x);
}