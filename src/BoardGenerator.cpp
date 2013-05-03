/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cstddef>
//#include <ctime>
#include <QDebug>
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
	
	if (!this->isBoardSolvable()) {
		qDebug("Correcting board!");
		int x, y, tmp;
		do {
			x = rand() % this->size;
			y = rand() % this->size;
		} while (tmp = this->initialBoard->getFieldAt(x, y) != 0);
		
		int x2, y2;
		do {
			x2 = rand() % this->size;
			y2 = rand() % this->size;
		} while ( !(x2 == x && y2 == y) && this->initialBoard->getFieldAt(x2, y2) != 0);
		
		this->initialBoard->setFieldAt(Point(x, y), this->initialBoard->getFieldAt(x2, y2));
		this->initialBoard->setFieldAt(Point(x2, y2), tmp);
	}
}

bool BoardGenerator::isBoardSolvable() {
	return this->initialBoard->countInversions() % 2 == 0;
}

void BoardGenerator::generateMovesBoard (int movesQty) {
	this->generateSolvedBoard();
	vector<Point> moves;
	QSet<QString> states;
	
	while (movesQty--) {
		moves.clear();
		for (int x = 0; x < this->size; ++x)
			for (int y = 0; y < this->size; ++y)
				if (initialBoard->getFreeFieldAround(Point(x, y)) != Point(0, 0))
					moves.push_back(Point(x,y));
				
		int id = rand() % moves.size();
		Point dst;
		dst = initialBoard->getFreeFieldAround(moves[id]) + moves[id];
		initialBoard->setFieldAt(dst, initialBoard->getFieldAt(moves[id].x, moves[id].y));
		initialBoard->setFieldAt(moves[id], 0);
		
		//nie chcemy powtórzeń:
		if (states.contains(initialBoard->getHash())) {
			swap(dst, moves[id]);
			dst = initialBoard->getFreeFieldAround(moves[id]) + moves[id];
			initialBoard->setFieldAt(dst, initialBoard->getFieldAt(moves[id].x, moves[id].y));
			initialBoard->setFieldAt(moves[id], 0);
			++movesQty;
		} else
			states.insert(initialBoard->getHash());
	}
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
