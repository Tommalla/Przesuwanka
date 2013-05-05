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

	if (this->state != PLAYING)
		
	//else
		this->nextSolutionMove++;	//Założenie - jeśli ruch w trybie odtwarzania to 
		//Game przewija ruchy

	this->movesHistory.push_back(move + res);
	this->movesCount++;
	this->isGameFinished();
	
	qDebug("nextSolutionMove: %d", this->nextSolutionMove);

	return res;
}

const Point Game::getLastMoved() {
	//if (this->state == PLAYING) {
		if (movesHistory.empty())
			return Point(-1, -1);
		return this->movesHistory.back(); 
	//}
	
	//if (this->nextSolutionMove == 0)
	//	return Point(-1, -1);
	//Point tmp = this->getMoveFor(this->solution[nextSolutionMove - 1]);
	//qDebug("%d %d + %d %d", this->solution[this->nextSolutionMove - 1].x, this->solution[this->nextSolutionMove - 1].y, tmp.x, tmp.y);
	//return this->solution[this->nextSolutionMove - 1] + this->getMoveFor(this->solution[nextSolutionMove - 1]);
}

const Point Game::getNextSolutionMove() {
	assert(this->nextSolutionMove < this->solution.size());
	return this->solution[this->nextSolutionMove];
}

const Point Game::undoLastMove () {
	//if (this->state == PLAYING)
		assert(!movesHistory.empty());
	//else
		//assert(this->nextSolutionMove > 0);
	
	Point last = this->getLastMoved();
	//Point dbgPoint = this->movesHistory.back();
	qDebug("Undo move: %d %d ->", last.x, last.y);
	
	this->movesCount -= 2;
	Point res = this->makeMove(last);
	qDebug("%d %d", last.x + res.x, last.y + res.y);
	//if (this->state == PLAYING) {
	movesHistory.pop_back();
	movesHistory.pop_back();
	
	if (this->state != PLAYING)
		this->nextSolutionMove -= 2;
	
	qDebug("nextSolutionMove: %d", this->nextSolutionMove);
	//}
	return res;
}



const Point Game::getMoveFor (const Point& pos) {
	return board->getFreeFieldAround(pos);
}

const Point Game::getPos (const int number) {
	return board->getPos(number);
}

const vector< Point > Game::getAvailableMoves() {
	return this->board->getMoves();
}



void Game::reset(const GameState state) {
	delete this->board;
	this->board = new Board(this->boardGenerator.getInitialBoard());
	this->movesCount = 0;
	this->movesHistory.clear();
	this->state = state;
	this->gameInProgress = true;
	
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







