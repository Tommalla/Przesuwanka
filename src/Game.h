/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAME_H
#define GAME_H
#include "BoardGenerator.h"
#include <list>

using namespace std;

class Game {
	private:
		Game();
		Game(const Game& g);
		Game& operator=(const Game& g);
		
		int movesCount, size, nextSolutionMove;
		bool gameInProgress;
		GameState state;
		
		BoardGenerator boardGenerator;
		Board* board;
		list<Point> movesHistory;
		vector<Point> solution;
	public:
		static Game& getInstance();
		
		bool isMoveValid(const Point& move);
		const Point makeMove(const Point& move);
		/**
		 * @brief Zwraca pozycję ostatnio poruszonego pola
		 * @return Point, jeśli jest jakiś ruch w historii, (-1, -1), jeśli nie ma
		 **/
		const Point getLastMoved();
		const Point getNextSolutionMove();
		const Point undoLastMove();
		const Point getMoveFor(const Point& pos);
		
		/**
		 * @brief Przywraca pierwotny stan planszy przed ruchami gracza
		 **/
		void reset(const GameState state);
		void newGame(const GameType& type, const int size);
		
		/**
		 * @brief Sprawdza, czy gra się już skończyła (ustawienie końcowe)
		 **/
		bool isGameFinished();
		int getMovesCount();
		
		int getFieldAt(const int x, const int y);
		
		~Game();
};

#endif // GAME_H
