/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <ctime>
#include <cassert>
#include "GraphicsTile.h"
#include "GameHandler.h"
#include "Game.h"
#include "constants.h"


const Point GraphicsTile::getRelativePosition() {
	return relativePosition;
}

void GraphicsTile::mousePressEvent (QGraphicsSceneMouseEvent* event) {
	Point move;
	if (event->button() == Qt::LeftButton) {
		if (Game::getInstance().isMoveValid(this->relativePosition))
			move = Game::getInstance().makeMove(this->relativePosition);
		else {
			qDebug("Niepoprawny ruch!");
			return;
		}
	} else if (event->button() == Qt::RightButton) {
		qDebug("Right button at tile %d %d", this->relativePosition.x, this->relativePosition.y);
		Point p = Game::getInstance().getLastMoved();
		if (Game::getInstance().getLastMoved() == Point(-1, -1))
			return;
		if (Game::getInstance().getLastMoved() != this->relativePosition) {
			event->ignore();
			return;
		}
		move = Game::getInstance().undoLastMove();
	} else
		return;
	
	this->relativePosition  = this->relativePosition + move;
	
	this->animation.setDuration(animationTime);
	this->animation.setEndValue(QPoint(relativePosition.x * tileSize, relativePosition.y * tileSize));
	this->animation.start();
	
	this->parent->registerMove();
}

void GraphicsTile::generatePixmap() {
	qDebug("generatePixmap for number %d\n", number);
	tileSize = min(parent->getScene()->width(), parent->getScene()->height());
	tileSize /= parent->getSize();	//rozmiar sceny/ilość klocków
	
	qDebug("\tsceneSize: %i x %i => tileSize = %d\n\ttile: %d, %d, %d %d\n", parent->getScene()->width(), parent->getScene()->height(), 
	       tileSize, 
	       tileSize * this->relativePosition.x, tileSize * this->relativePosition.y,
	       tileSize * (this->relativePosition.x + 1), tileSize * (this->relativePosition.y + 1) );
	
	QPixmap pixmap(tileSize, tileSize);
	QPainter painter(&pixmap);
	
	qDebug("Color: %d %d %d\n", this->color.red(), this->color.green(), this->color.blue());
	painter.fillRect(QRect(0, 0, tileSize, tileSize), this->color);
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
	
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	qDebug("\tColor: %d %d %d\n", r, g, b);
	this->color = QColor(r, g, b);
	
	this->generatePixmap();
	
	this->animation.setTargetObject(this);
	this->animation.setPropertyName("offset");
}







