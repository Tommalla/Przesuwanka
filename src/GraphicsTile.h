/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSTILE_H
#define GRAPHICSTILE_H
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include "Point.h"

class GameHandler;

class GraphicsTile : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT;
	Q_PROPERTY(QPointF offset
	READ offset
	WRITE setOffset);
	private:
		int number, tileSize;
		GameHandler* parent;
		Point relativePosition;
		QPropertyAnimation animation;
		
		void generatePixmap();
		void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	public:
		GraphicsTile(GameHandler* parent, const int number, const Point relativePosition);
};

#endif // GRAPHICSTILE_H
