/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cstdio>
#include <QGraphicsSceneEvent>
#include <QKeyEvent>
#include <cassert>

#include "GraphicsScene.h"
#include "Game.h"
#include "GraphicsTile.h"
#include "GameHandler.h"

void GraphicsScene::keyPressEvent (QKeyEvent* event) {
	//QGraphicsScene::keyPressEvent (event);
	qDebug("Key press!");
	Point move;
	switch (event->key()) {
		case Qt::Key_Up:
			move = Point(0, -1);
			break;
		case Qt::Key_Down:
			move = Point(0, 1);
			break;
		case Qt::Key_Right:
			if (this->parent->getState() != PLAYING) {
				this->parent->nextSolutionMove();
				return;
			}
			move = Point(1, 0);
			break;
		case Qt::Key_Left:
			if (this->parent->getState() != PLAYING) {
				this->parent->undoLastMove();
				return;
			}
			move = Point(-1, 0);
			break;
		case Qt::Key_Backspace:
			this->parent->undoLastMove();
			return;
		case Qt::Key_Space:
			switch (this->parent->getState()) {
				case SHOWING_SOLUTION:
					emit this->pauseSolution();
					return;
				case SHOWING_PAUSED:
					emit this->resumeSolution();
					return;
				default:
					return;
			}
		default:
			return;
	}
	
	if (this->parent->getState() == PLAYING)
		parent->makePossibleMove(move);
}

void GraphicsScene::mousePressEvent (QGraphicsSceneMouseEvent* event) {
	if (parent->getState() == SHOWING_SOLUTION) {
		if (event->button() == Qt::LeftButton) {
			emit this->pauseSolution();
			qDebug("Scene: Pauza");
		}
		return;
	}
	
// 	if (parent->getState() == SHOWING_PAUSED)
// 		return;	//TODO generowanie rozwiązania w tle
	qDebug("mousePress at Scene");
	
	if (event->button() == Qt::RightButton)
		this->parent->undoLastMove();
	else if (event->button() == Qt::LeftButton) {
		if (this->parent->getState() == PLAYING)
			QGraphicsScene::mousePressEvent(event);
		else
			this->parent->nextSolutionMove();
	}
}

void GraphicsScene::mouseDoubleClickEvent (QGraphicsSceneMouseEvent* event) {
	//QGraphicsScene::mouseDoubleClickEvent (event);
	if (event->buttons() == Qt::LeftButton && this->parent->getState() == SHOWING_PAUSED) {
		qDebug("Resume!");
		emit this->resumeSolution();
	}
	
	qDebug("dblClk");
}

GraphicsScene::GraphicsScene (GameHandler* parent) : QGraphicsScene() {
	this->parent = parent;
}



