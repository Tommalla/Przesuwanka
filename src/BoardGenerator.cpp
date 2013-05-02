/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cstddef>
#include <ctime>
#include <algorithm>
#include "BoardGenerator.h"

void BoardGenerator::calculateSolution() {
	//TODO A*
}

void BoardGenerator::generateRandomBoard() {
	this->reset();
	
	int t[this->size * this->size];
	for (int i = 0; i < this->size * this->size; ++i)
		t[i] = i;
	random_shuffle(t, t + this->size * this->size);
	
	for (int i = 0; i < this->size * this->size; ++i)
		this->initialBoard->setFieldAt(Point(i % this->size, i / this->size), t[i]);
	//TODO poprawianie jeśli nierozwiązywalna
}

bool BoardGenerator::isBoardSolvable() {
	//TODO czy permutacja parzysta?
}

void BoardGenerator::generateMovesBoard (int movesQty) {
	this->generateSolvedBoard();
	//TODO dodać movesQty losowych ruchów
}

void BoardGenerator::generateSolvedBoard() {
	this->reset();
	
	for (int i = 0; i < this->size * this->size - 1; ++i)
		this->initialBoard->setFieldAt(Point(i % this->size, i / this->size), i + 1);
}

void BoardGenerator::copyToSelf (const BoardGenerator& b) {
	this->initialized = b.initialized;
	this->initialBoard = new Board(*b.initialBoard);
}

void BoardGenerator::reset() {
	srand(time(NULL));
	delete this->initialBoard;
	this->initialBoard = new Board(this->size);
}


BoardGenerator::BoardGenerator() {
	this->initialized = false;
	this->initialBoard = NULL;
}

BoardGenerator::BoardGenerator (const GameType& type, int size) {
	this->size = size;
	this->init(type, size);
}

BoardGenerator::BoardGenerator (const BoardGenerator& b) {
	this->copyToSelf(b);
}

void BoardGenerator::init (const GameType& type, int size) {
	this->size = size;
	
	switch(type) {
		case RANDOM:
			this->generateRandomBoard();
			break;
		case EASY:
			this->generateMovesBoard(this->easyBoardMoves);
			break;
		case MEDIUM:
			this->generateMovesBoard(this->mediumBoardMoves);
			break;
		default:
			this->generateMovesBoard(this->hardBoardMoves);
			break;
	}
	
	this->initialized = true;
}

Board BoardGenerator::getInitialBoard() {
	assert(this->initialized);
	return *this->initialBoard;
}

const vector< Point >& BoardGenerator::getSolution() {
	assert(this->initialized);
	return (this->solution);
}

BoardGenerator::~BoardGenerator() {
	delete this->initialBoard;
}

BoardGenerator& BoardGenerator::operator= (const BoardGenerator& b) {
	this->copyToSelf(b);
	return *this;
}






