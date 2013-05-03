/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene {
	//QOBJECT;
	protected:
		virtual void keyReleaseEvent (QKeyEvent* event);
		virtual void mousePressEvent (QGraphicsSceneMouseEvent * event);
};

#endif // GRAPHICSSCENE_H
