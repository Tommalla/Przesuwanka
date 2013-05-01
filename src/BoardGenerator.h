/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#ifndef BOARDGENERATOR_H
#define BOARDGENERATOR_H
#include <vector>
#include "Board.h"
#include "Point.h"
#include "enums.h"

using namespace std;

class BoardGenerator {
	private:
		const int easyBoardMoves = 20;
		const int mediumBoardMoves = 100;
		const int hardBoardMoves = 500;

		Board* initialBoard;
		bool initialized;
		int size;

		vector<Point> solution;
		void calculateSolution();
		void generateRandomBoard();
		bool isBoardSolvable();
		/**
		 * @brief Generuje planszę z pewnej ilości losowych ruchów
		 * @param movesQty Ilość losowych ruchów
		 **/
		void generateMovesBoard (int movesQty);

		void generateSolvedBoard();

		void copyToSelf (const BoardGenerator& b);
	public:
		BoardGenerator();
		BoardGenerator (const GameType& type, int size);
		BoardGenerator (const BoardGenerator& b);

		void init (const GameType& type, int size);

		const vector< Point >& getSolution();
		Board getInitialBoard();

		~BoardGenerator();
		BoardGenerator& operator= (const BoardGenerator& b);

};

#endif // BOARDGENERATOR_H
