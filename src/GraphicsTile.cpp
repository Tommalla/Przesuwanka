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
	
	if (event->button() == Qt::LeftButton && this->parent->getState() == PLAYING) {	//jeśli lewy przycisk i gra
		if (Game::getInstance().isMoveValid(this->relativePosition))
			this->makeMove(NORMAL);
		else {
			qDebug("Niepoprawny ruch!");
			return;
		}
	} else if (event->button() == Qt::RightButton) {	//jeśli prawy - cofamy ruch niezależnie czy gra czy pokazywanie rozwiązania
		qDebug("Right button at tile %d %d", this->relativePosition.x, this->relativePosition.y);
		if (Game::getInstance().getLastMoved() == Point(-1, -1))	//nie ma co pokazać
			return;
		if (Game::getInstance().getLastMoved() != this->relativePosition) {	//Qt dało nam nieswojego eventa, odsyłamy do sceny
			event->ignore();
			return;
		}
		this->makeMove(UNDO);
	}
}

void GraphicsTile::makeMove (const MoveType type) {
	Point move;
	switch (type) {
		case NORMAL:
			move = Game::getInstance().makeMove(this->relativePosition);
			break;
		case UNDO:
			move = Game::getInstance().undoLastMove();
			break;
	}
	
	this->moveTile(move);
}

void GraphicsTile::moveTile (const Point move) {
	qDebug("Ruch %d %d -> %d %d", this->relativePosition.x, this->relativePosition.y, this->relativePosition.x + move.x,
	       this->relativePosition.y + move.y);
	this->relativePosition = this->relativePosition + move;
	
	this->animation.setDuration(animationTime);
	this->animation.setEndValue(QPoint(relativePosition.x * tileSize, relativePosition.y * tileSize));
	this->animation.start();
	
	this->parent->registerMove();
}


void GraphicsTile::generatePixmap() {
	this->tileSize = min(parent->getScene()->width(), parent->getScene()->height());
	this->tileSize /= parent->getSize();	//rozmiar sceny/ilość klocków
	
	QPixmap pixmap(tileSize, tileSize);
	QPainter painter(&pixmap);
	
	painter.fillRect(QRect(0, 0, tileSize, tileSize), this->color);
	QString text = QString::number(number);

	int fontSize = tileSize / 4;

	QFont font;
	font.setPixelSize(fontSize);
	painter.setFont(font);
	painter.drawText(0, 0, tileSize, tileSize, Qt::AlignCenter, text);
	
	this->setPixmap(pixmap);
	this->setOffset(this->relativePosition.x * tileSize, this->relativePosition.y * tileSize);
}

void GraphicsTile::syncWithGame() {
	Point pos = Game::getInstance().getPos(this->number);
	this->relativePosition = pos;
	this->setOffset(pos.x * this->tileSize, pos.y * this->tileSize);
}


GraphicsTile::GraphicsTile (GameHandler* parent, const int number, const Point relativePosition) : QGraphicsPixmapItem() {
	this->parent = parent;
	this->number = number;
	this->relativePosition = relativePosition;
	
	int r = rand() % (256 - lowerColorLimit) + lowerColorLimit;
	int g = rand() % (256 - lowerColorLimit) + lowerColorLimit;
	int b = rand() % (256 - lowerColorLimit) + lowerColorLimit;
	qDebug("%d %d %d", r, g, b);
	
	this->color = QColor(r, g, b);
	
	this->generatePixmap();
	
	this->animation.setTargetObject(this);
	this->animation.setPropertyName("offset");
}







