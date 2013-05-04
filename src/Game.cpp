/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cassert>
#include <cstddef>
#include <QDebug>
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

const Point Game::makeMove (const Point& move) {
	Point res = board->getFreeFieldAround(move);
	qDebug("Move %d %d -> %d %d", move.x, move.y, move.x + res.x, move.y + res.y);
	
	assert(board->getFieldAt(move.x + res.x, move.y + res.y) == 0);
	
	int tmp = board->getFieldAt(move.x, move.y);
	board->setFieldAt(move, 0);
	board->setFieldAt(move + res, tmp);

	if (this->state == PLAYING)
		this->movesHistory.push_back(move + res);
	else
		this->nextSolutionMove++;	//Założenie - jeśli ruch w trybie odtwarzania to 
		//Game przewija ruchy

	this->movesCount++;
	this->isGameFinished();

	return res;
}

const Point Game::getLastMoved() {
	if (this->state == PLAYING) {
		if (movesHistory.empty())
			return Point(-1, -1);
		return this->movesHistory.back(); 
	}
	
	return (this->nextSolutionMove == 0) ? Point(-1, -1) : this->solution[nextSolutionMove - 1];
}

const Point Game::getNextSolutionMove() {
	assert(this->nextSolutionMove < this->solution.size());
	return this->solution[this->nextSolutionMove];
}


const Point Game::undoLastMove () {
	Point dbgPoint = this->movesHistory.back();
	qDebug("Undo move: %d %d ->", this->movesHistory.back().x, this->movesHistory.back().y);
	assert(!movesHistory.empty());
	
	this->movesCount -= 2;
	Point res = this->makeMove(this->movesHistory.back());
	qDebug("%d %d", dbgPoint.x + res.x, dbgPoint.y + res.y);
	movesHistory.pop_back();
	movesHistory.pop_back();
	return res;
}



const Point Game::getMoveFor (const Point& pos) {
	return board->getFreeFieldAround(pos);
}

const Point Game::getPos (const int number) {
	return board->getPos(number);
}


void Game::reset(const GameState state) {
	delete this->board;
	this->board = new Board(this->boardGenerator.getInitialBoard());
	this->movesCount = 0;
	this->movesHistory.clear();
	this->state = state;
	
	if (state == SHOWING_SOLUTION) {
		this->nextSolutionMove = 0;
		this->solution = this->boardGenerator.getSolution();
	}
}


void Game::newGame (const GameType& type, const int size) {
	this->size = size;
	boardGenerator.init(type, size);
	this->reset(PLAYING);
	
	this->gameInProgress = true;
}

int Game::getMovesCount() {
	return this->movesCount;
}

bool Game::isGameFinished() {
	if (this->gameInProgress)
		return !(this->gameInProgress = !board->isSolved(this->size));
	
	return true;
}

int Game::getFieldAt (const int x, const int y) {
	assert(this->gameInProgress);
	return board->getFieldAt(x, y);
}

Game::~Game() {
	delete this->board;
}







