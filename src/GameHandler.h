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
		vector<GraphicsTile> tiles;
		int size;
	public:
		GameHandler(QGraphicsView* graphicsView);
		
		void newGame(const GameType& type, int size);
		
		const QGraphicsView* getView() const;
		const GraphicsScene* getScene() const;
		const int getSize() const;
		void registerMove();
		~GameHandler();
	signals:
		void moveMade();
};

#endif // GAMEHANDLER_H
