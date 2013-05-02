/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSTILE_H
#define GRAPHICSTILE_H
#include <QGraphicsPixmapItem>
#include "Point.h"

class GameHandler;

class GraphicsTile : public QGraphicsPixmapItem {
	private:
		int number;
		GameHandler* parent;
		Point relativePosition;
		
		void generatePixmap();
	public:
		GraphicsTile(GameHandler* parent, const int number, const Point relativePosition);
};

#endif // GRAPHICSTILE_H
