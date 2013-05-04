/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <QString>

#include "Point.h"
#include "BitContainer.h"

using namespace std;

class Board {
	//friend class BoardGenerator;
	private:
		int size;
		BitContainer* board;
		
		void copyToSelf(const Board &b);
	public:
		/**
		 * @brief Tworzy nową planszę o boku podanej długości
		 * @param size Długość boku planszy. Domyślnie 4.
		 **/
		Board(int size = 4);
		Board(const Board &b);
		
		void setFieldAt(const Point& pos, const int field);
		int getFieldAt(const int x, const int y) const;
		/**
		 * @brief Zwraca puste pole z otoczenia pos.
		 * @param pos ...
		 * @return const Point& Point(0,0), jeśli nie ma, wektor przesunięcia na którego końcu leży wolne pole w innym przypadku
		 **/
		const Point getFreeFieldAround(const Point& pos);
		/**
		 * @brief Zwraca ruchy dostępne z obecnej planszy
		 **/
		const vector<Point> getMoves();
		const Point getPos(const int number);
		const int countInversions() const;
		/**
		 * @brief Zwraca sumę odległości wszystkich klocków od ich docelowego położenia w metryce Manhattan
		 **/
		const int getManhattanMetricValue() const;
		
		bool isSolved(const int rows) const;
		const QString getHash();
		
		~Board();
		Board& operator=(const Board &b);
};

#endif // BOARD_H
