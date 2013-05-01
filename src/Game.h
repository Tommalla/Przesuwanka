/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAME_H
#define GAME_H
#include "BoardGenerator.h"

class Game {
	private:
		Game();
		Game(const Game& g);
		Game& operator=(const Game& g);
		
		int movesCount, size;
		bool gameInProgress;
		
		BoardGenerator boardGenerator;
		Board* board;
	public:
		Game& getInstance();
		
		bool isMoveValid(const Point& move);
		const Point& makeMove(const Point& move);
		
		/**
		 * @brief Przywraca pierwotny stan planszy przed ruchami gracza
		 **/
		void reset();
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
