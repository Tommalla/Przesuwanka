/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include <cstddef>
//#include <ctime>
#include <QDebug>
#include <algorithm>
#include <set>
#include <climits>
#include "BoardGenerator.h"
#include "constants.h"

struct AStarNode {
	Board* board;
	int f, g, prevMoveId;
	
	AStarNode& operator=(const AStarNode& a) {
		board = a.board;
		f = a.f;
		g = a.g;
		prevMoveId = a.prevMoveId;
	}
};

struct setCmp {
	inline bool operator() (const AStarNode &a, const AStarNode& b) {
		if (a.f != b.f)
			return a.f < b.f;
		if (a.g != b.g)
			return a.g < b.g;
		return a.prevMoveId < b.prevMoveId;
	}
};

void BoardGenerator::calculateSolution() {
	qDebug("BoardGenerator::calculateSolution");
	this->solution.clear();
	Board solved = *this->initialBoard;
	
	for (int i = 1; i <= this->size; ++i)
		this->aStar(i, solved);
}

Board BoardGenerator::aStar (const int level, const Board board) {
	qDebug("BoardGenerator::aStar(%d)", level);
	QSet<QString> prevStates;	//poprzednie stany planszy, bo nie chcemy pętlii można szybko sprawdzić
	set<AStarNode, setCmp> s;
	vector<pair<Point, int> > movesMemory;
	vector<Point> moves;
	
	AStarNode v, u, best;
	v.board = new Board(board);
	v.f = v.board->getManhattanMetricValue();
	v.g = 0;
	v.prevMoveId = -1;
	
	best.g = INT_MAX;
	best.board = NULL;
	
	s.insert(v);
	prevStates.insert(v.board->getHash());
	
	
	while (!s.empty() && best.g == INT_MAX) {
		v = *s.begin();
		s.erase(s.begin());
		
		//assert(!prevStates.contains(v.board->getHash()));
		
		//qDebug("Wierzchołek w odległości %d od źródła.", v.g + 1);
		
		moves = v.board->getMoves();
		for (vector<Point>::iterator iter = moves.begin(); iter != moves.end(); ++iter) {
			u.board = new Board(*v.board);
			
			//przygotowywujemy planszę po ruchu
			Point field = *iter;
			Point move = u.board->getFreeFieldAround(field);
			u.board->setFieldAt(field + move, u.board->getFieldAt(field.x, field.y));
			u.board->setFieldAt(field, 0);
			
			//qDebug("Hash: %s",  u.board->getHash().toStdString().c_str());
			
			if (!prevStates.contains(u.board->getHash())) {	//jeśli nie ma powtórzenia
				u.g = v.g + 1;
				u.f = u.g + u.board->getManhattanMetricValue();
				
				if (u.g > aStarMaxDistance || u.g > best.g /*|| u.f - u.g > v.f - v.g*/) {
					delete u.board;
					continue;
				}
				
				movesMemory.push_back(make_pair(move, v.prevMoveId));
				u.prevMoveId = movesMemory.size() - 1;
				
				if (u.board->isSolved(level)) {
					qDebug("Znaleziono rozwiązanie! Ilość ruchów: %d", v.g + 1);
					//TODO
					if (best.g > u.g) {
						delete best.board;
						best = u;
					} else
						delete u.board;
					
					break;
				} else {
					s.insert(u);
					prevStates.insert(u.board->getHash());
				}
			} else {
				//qDebug("RAWR! ERROR! Ten hasz już był!");
				delete u.board;
			}
		}
		
		delete v.board;
	}
	
	while (!s.empty()) {
		delete s.begin()->board;
		s.erase(s.begin());
	}
	
	qDebug("Pozostaje odzyskać rozwiązanie i posprzątać");
	
	int id = best.prevMoveId;
	
	while (id != -1) {
		this->solution.push_back(movesMemory[id].first);
		id = movesMemory[id].second;
	}
	
	reverse(this->solution.begin(), this->solution.end());
	
	return *best.board;
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
	this->calculateSolution();
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
