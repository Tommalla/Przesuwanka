/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cstddef>
#include "BoardGenerator.h"

void BoardGenerator::calculateSolution() {
	//TODO A*
}

void BoardGenerator::generateRandomBoard() {
	//TODO tworzenie losowej planszy i poprawianie jej jeśli nierozwiązywalna
}

bool BoardGenerator::isBoardSolvable() {
	//TODO czy permutacja parzysta?
}

void BoardGenerator::generateMovesBoard (int movesQty) {
	this->generateSolvedBoard();
	//TODO dodać movesQty losowych ruchów
}

void BoardGenerator::generateSolvedBoard() {
	this->initialBoard = new Board(this->size);
	
	for (int i = 0; i < this->size * this->size - 1; ++i)
		this->initialBoard->setFieldAt(Point(i % this->size, i / this->size), i + 1);
}

void BoardGenerator::copyToSelf (const BoardGenerator& b) {
	this->initialized = b.initialized;
	this->initialBoard = new Board(*b.initialBoard);
}

BoardGenerator::BoardGenerator() {
	this->initialized = false;
	this->initialBoard = NULL;
}

BoardGenerator::BoardGenerator (const GameType& type, int size) {
	this->size = size;
	this->Init(type);
}

BoardGenerator::BoardGenerator (const BoardGenerator& b) {
	this->copyToSelf(b);
}

void BoardGenerator::Init (const GameType& type) {
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






