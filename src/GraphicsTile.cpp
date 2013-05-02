/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <QPainter>
#include "GraphicsTile.h"
#include "GameHandler.h"

void GraphicsTile::generatePixmap() {
	QPixmap pixmap(parent->getView()->width() / parent->getSize(), parent->getView()->height() / parent->getSize());
	QPainter painter(&pixmap);
	
	painter.fillRect(QRect(0, 0, pixmap.width(), pixmap.height()), QColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256));
	
	painter.end();
	
	this->setPixmap(pixmap);
}


GraphicsTile::GraphicsTile (GameHandler* parent, const int number) : QGraphicsPixmapItem() {
	this->parent = parent;
	this->number = number;
	
	this->generatePixmap();
}






