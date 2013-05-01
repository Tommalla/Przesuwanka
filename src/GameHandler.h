/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H
#include <QGraphicsView>
#include "enums.h"

class GameHandler {
	private:
		QGraphicsView* graphicsView;
		QGraphicsScene* scene;
		int size;
	public:
		GameHandler(QGraphicsView* graphicsView);
		
		void newGame(const GameType& type, int size);
		void drawBoard();
		~GameHandler();
		//TODO handlery do kliknięć i keyEventów
};

#endif // GAMEHANDLER_H
