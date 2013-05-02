/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include <QGraphicsView>
#include "GraphicsScene.h"
#include "enums.h"
#include "GraphicsTile.h"

class GameHandler {
	private:
		QGraphicsView* graphicsView;
		GraphicsScene* scene;
		GraphicsTile* tiles;
		int size;
	public:
		GameHandler(QGraphicsView* graphicsView);
		
		void newGame(const GameType& type, int size);
		void drawBoard();
		~GameHandler();
};

#endif // GAMEHANDLER_H
