/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSTILE_H
#define GRAPHICSTILE_H
#include <QGraphicsPixmapItem>

class GameHandler;

class GraphicsTile : public QGraphicsPixmapItem {
	private:
		int number;
		GameHandler* parent;
		
		void generatePixmap();
	public:
		GraphicsTile(GameHandler* parent, const int number);
};

#endif // GRAPHICSTILE_H
