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
	
	qDebug("Pierwotna plansza:");
	qDebug(solved.toQString().toStdString().c_str());
	
	for (int i = 1; i <= this->size - 2; ++i) 
		if (!solved.isSolved(i, this->size) ) {
			solved = this->aStar(i, this->size, solved);
			qDebug("Plansza po A*:");
			qDebug(solved.toQString().toStdString().c_str());
		}
		
	for (int i = 1; i < 3; ++i)
	if (!solved.isSolved(this->size, i) ) {
		solved = this->aStar(this->size, i, solved);
		qDebug("Plansza po A*:");
		qDebug(solved.toQString().toStdString().c_str());
	}
	
	if (!solved.isSolved(this->size, this->size) ) {
		solved = this->aStar(this->size, this->size, solved);
		qDebug("Plansza po A*:");
		qDebug(solved.toQString().toStdString().c_str());
	}

}

Board BoardGenerator::aStar (const int level, const int sublevel, const Board board) {
	qDebug("BoardGenerator::aStar(%d, %d)", level, sublevel);
	QSet<QString> prevStates;	//poprzednie stany planszy, bo nie chcemy pętlii można szybko sprawdzić
	set<AStarNode, setCmp> s;
	vector<pair<Point, int> > movesMemory;
	vector<Point> moves;
	
	AStarNode v, u, best;
	v.board = new Board(board);
	v.f = manhattanMetricMultiplier * v.board->getManhattanMetricValue(level);
	v.g = 0;
	v.prevMoveId = -1;
	
	best.g = INT_MAX;
	best.board = NULL;
	best.prevMoveId = 0;
	
	s.insert(v);
	prevStates.insert(v.board->getHash());
	
	
	while (!s.empty() && best.g == INT_MAX) {
		v = *s.begin();
		s.erase(s.begin());
		//qDebug("Wierzchołek w odległości %d od źródła.", v.g + 1);
		
		moves = v.board->getMoves();
		for (vector<Point>::iterator iter = moves.begin(); iter != moves.end(); ++iter) {
			u.board = new Board(*v.board);
			
			u.g = v.g + 1;
			//przygotowywujemy planszę po ruchu
			Point field = *iter;
			
			if (u.g > aStarMaxDistance /*|| (level == 1 && u.g > 40)*/ || u.g > best.g 
				/*|| field.y < level - (level == this->size ? 2 : 1) */) {
				delete u.board;
				continue;
			}
			
			//przygotowywujemy planszę po ruchu
			Point move = u.board->getFreeFieldAround(field);
			u.board->setFieldAt(field + move, u.board->getFieldAt(field.x, field.y));
			u.board->setFieldAt(field, 0);
			

			//qDebug("Hash: %s",  u.board->getHash().toStdString().c_str());
			if (!prevStates.contains(u.board->getHash())) {	//jeśli nie ma powtórzenia
				u.f = u.g + manhattanMetricMultiplier * u.board->getManhattanMetricValue(level);
				
				movesMemory.push_back(make_pair(field, v.prevMoveId));
				u.prevMoveId = movesMemory.size() - 1;
				
				if (u.board->isSolved(level, sublevel)) {
					qDebug("Znaleziono rozwiązanie! Ilość ruchów: %d", v.g + 1);
					//TODO szukać więcej niż do pierwszego
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
	
	assert(best.g != INT_MAX);
	
	int id = best.prevMoveId;
	
	vector<Point> solutionPart;
	
	while (id != -1) {
		solutionPart.push_back(movesMemory[id].first);
		id = movesMemory[id].second;
	}
	
	reverse(solutionPart.begin(), solutionPart.end());
	this->solution.reserve(this->solution.size() + solutionPart.size());
	this->solution.insert(this->solution.end(), solutionPart.begin(), solutionPart.end());
	
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
	
	while (!this->isBoardSolvable()) {
		qDebug("Correcting board!");
		this->generateRandomBoard();
	}
}

bool BoardGenerator::isBoardSolvable() {
	int row = this->initialBoard->getPos(0).y;
	assert(row != -1);
 	row = this->size - row;
	int inv = this->initialBoard->countInversions();
	//( (grid width odd) && (#inversions even) )  ||  ( (grid width even) && ((blank on odd row from bottom) == (#inversions even)) )
	return ((this->size % 2 == 1) && (inv % 2 == 0)) ||
	(this->size % 2 == 0 && ( (row % 2 == 1) == (inv % 2 == 0) ));
}

void BoardGenerator::generateMovesBoard (int movesQty) {
	this->generateSolvedBoard();
	vector<Point> moves;
	//QSet<QString> states;
	Point lastMove;
	
	while (movesQty--) {
		moves.clear();
		moves = initialBoard->getMoves();
		
		assert(!moves.empty());
		
		int id;
		Point dst;
		do {
			id = rand() % moves.size();
			dst = moves[id] + this->initialBoard->getFreeFieldAround(moves[id]);
		} while(moves[id] == lastMove);
			
		dst = initialBoard->getFreeFieldAround(moves[id]) + moves[id];
		qDebug("Generowanie planszy: %d %d -> %d %d (%d %d)", moves[id].x, moves[id].y, dst.x, dst.y, dst.x - moves[id].x,
			dst.y - moves[id].y
		);
		assert(initialBoard->getFieldAt(dst.x, dst.y) == 0);
		initialBoard->setFieldAt(dst, initialBoard->getFieldAt(moves[id].x, moves[id].y));
		initialBoard->setFieldAt(moves[id], 0);
		
		lastMove = moves[id];
		
// 		//nie chcemy powtórzeń:
// 		if (states.contains(initialBoard->getHash())) {
// 			swap(dst, moves[id]);
// 			dst = initialBoard->getFreeFieldAround(moves[id]) + moves[id];
// 			qDebug("Cofanie ruchu: %d %d -> %d %d",  moves[id].x, moves[id].y, dst.x, dst.y);
// 			initialBoard->setFieldAt(dst, initialBoard->getFieldAt(moves[id].x, moves[id].y));
// 			initialBoard->setFieldAt(moves[id], 0);
// 			++movesQty;
// 		} else
// 			states.insert(initialBoard->getHash());
	}
	
	assert(this->isBoardSolvable());
}

void BoardGenerator::generateSolvedBoard() {
	this->reset();
	
	for (int i = 0; i < this->size * this->size - 1; ++i)
		this->initialBoard->setFieldAt(Point(i % this->size, i / this->size), i + 1);
	
	this->initialBoard->setFieldAt(Point(this->size - 1, this->size - 1), 0);
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
