/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
//#include "GameHandler.h"

class GameHandler;

class GraphicsScene : public QGraphicsScene {
	//QOBJECT;
	private:
		GameHandler* parent;
	protected:
		virtual void keyReleaseEvent (QKeyEvent* event);
		virtual void mousePressEvent (QGraphicsSceneMouseEvent * event);
	public:
		GraphicsScene (GameHandler* parent);
};

#endif // GRAPHICSSCENE_H
