/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include <QGraphicsView>
#include <vector>
#include "GraphicsScene.h"
#include "enums.h"
#include "GraphicsTile.h"

using namespace std;

class GameHandler : public QObject {
	Q_OBJECT;
	private:
		QGraphicsView* graphicsView;
		GraphicsScene* scene;
		vector<GraphicsTile* > tiles;
		int size;
		GameState state;
		
		void resetTiles();
		void makeMove(const Point field, const MoveType type);
	public:
		GameHandler(QGraphicsView* graphicsView);
		
		void newGame(const GameType& type, int size);
		void initializeSolutionShow();
		
		const QGraphicsView* getView() const;
		const GraphicsScene* getScene() const;
		const int getSize() const;
		void repaintTiles();
		void registerMove();
		void undoLastMove();
		/**
		 * @brief Wykonuje ruch zgodny z podanym wektorem
		 * @param move Wektor ruchu
		 **/
		void makePossibleMove(const Point move);
		
		const GameState getState();
		void pauseSolution();
		void resumeSolution();
		~GameHandler();
	signals:
		void moveMade();
	public slots:
		void nextSolutionMove();
};

#endif // GAMEHANDLER_H
