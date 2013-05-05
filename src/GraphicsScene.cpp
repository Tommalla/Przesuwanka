/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cstdio>
#include <QGraphicsSceneEvent>
#include <cassert>

#include "GraphicsScene.h"
#include "Game.h"
#include "GraphicsTile.h"
#include "GameHandler.h"

void GraphicsScene::keyReleaseEvent (QKeyEvent* event) {
	QGraphicsScene::keyReleaseEvent (event);
	qDebug("TODO: Strzałki");
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



