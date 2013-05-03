/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <QPainter>
#include <ctime>
#include "GraphicsTile.h"
#include "GameHandler.h"

void GraphicsTile::generatePixmap() {
	qDebug("generatePixmap for number %d\n", number);
	int tileSize = min(parent->getScene()->width(), parent->getScene()->height());
	tileSize /= parent->getSize();
	
	qDebug("\tsceneSize: %i x %i => tileSize = %d\n\ttile: %d, %d, %d %d\n", parent->getScene()->width(), parent->getScene()->height(), 
	       tileSize, 
	       tileSize * this->relativePosition.x, tileSize * this->relativePosition.y,
	       tileSize * (this->relativePosition.x + 1), tileSize * (this->relativePosition.y + 1) );
	
	QPixmap pixmap(tileSize, tileSize);
	QPainter painter(&pixmap);
	
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	qDebug("\tColor: %d %d %d\n", r, g, b);
	
	painter.fillRect(QRect(0, 0, tileSize, tileSize), 
			       QColor(r, g, b));
	QString text = QString::number(number);
	//TODO center!
	painter.drawText(tileSize / 2 - 6, tileSize / 2 + 4, text);
	
	qDebug("\tText: %s\n", text.toStdString().c_str());
	
	this->setPixmap(pixmap);
	this->setOffset(this->relativePosition.x * tileSize, this->relativePosition.y * tileSize);
}


GraphicsTile::GraphicsTile (GameHandler* parent, const int number, const Point relativePosition) : QGraphicsPixmapItem() {
	this->parent = parent;
	this->number = number;
	this->relativePosition = relativePosition;
	
	this->generatePixmap();
}






