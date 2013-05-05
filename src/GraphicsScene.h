/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
//#include "GameHandler.h"

class GameHandler;

class GraphicsScene : public QGraphicsScene {
	Q_OBJECT;
	private:
		GameHandler* parent;
	protected:
		virtual void keyPressEvent (QKeyEvent* event);
		virtual void mousePressEvent (QGraphicsSceneMouseEvent* event);
		virtual void mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event);
	public:
		GraphicsScene (GameHandler* parent);
	signals:
		void pauseSolution();
		void resumeSolution();
};

#endif // GRAPHICSSCENE_H
