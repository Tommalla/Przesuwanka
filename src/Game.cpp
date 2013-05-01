/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cstddef>
#include "Game.h"

Game::Game() {
	this->gameInProgress = false;
	this->movesCount = 0;
	this->board = NULL;
}

Game& Game::getInstance() {
	static Game instance;
	return instance;
}

bool Game::isMoveValid (const Point& move) {
	assert(this->gameInProgress);
	return this->board->getFreeFieldAround(move) != Point(0, 0);
}

const Point& Game::makeMove (const Point& move) {
	Point res = board->getFreeFieldAround(move);
	
	assert(board->getFieldAt(move.x + res.x, move.y + res.y) == 0);
	
	int tmp = board->getFieldAt(move.x, move.y);
	board->setFieldAt(move, 0);
	board->setFieldAt(move + res, tmp);

	this->isGameFinished();
}

void Game::reset() {
	delete this->board;
	this->board = new Board(this->boardGenerator.getInitialBoard());
	this->movesCount = 0;
}

void Game::newGame (const GameType& type, const int size) {
	this->size = size;
	boardGenerator.init(type, size);
	this->reset();
	
	this->gameInProgress = true;
}

int Game::getMovesCount() {
	return this->movesCount;
}

bool Game::isGameFinished() {
	if (this->gameInProgress) {
		for (int i = 0; i < this->size * this->size - 1; ++i)
			if (board->getFieldAt(i % this->size, i / this->size) != i + 1)
				return false;
	
		this->gameInProgress = false;
	}
	
	return true;
}

int Game::getFieldAt (const int x, const int y) {
	assert(this->gameInProgress);
	return board->getFieldAt(x, y);
}

Game::~Game() {
	delete this->board;
}







