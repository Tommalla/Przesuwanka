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
	if (parent->getState() == SHOWING_SOLUTION || parent->getState() == SHOWING_PAUSED ) {
		qDebug("TODO: Showing playout (scene)");
		return;
	}
	
	qDebug("mousePress at Scene");
	
	if (event->button() == Qt::RightButton) {
		qDebug("RightButton at Scene");
		Point last = Game::getInstance().getLastMoved();
		if (last == Point(-1, -1)) {
			qDebug("Próba cofnięcia ruchu przy pustej kolejce!");
			return;
		}
		
		GraphicsTile* it;
		for (QList<QGraphicsItem *>::iterator iter = this->items().begin(); iter != this->items().end(); ++iter) {
			it = dynamic_cast<GraphicsTile*>(*iter);
			if (it != NULL && it->getRelativePosition() == last) {
				it->mousePressEvent(event);
				return;
			}
		}
	} else if (event->button() == Qt::LeftButton)
		QGraphicsScene::mousePressEvent(event);
}

GraphicsScene::GraphicsScene (GameHandler* parent) : QGraphicsScene() {
	this->parent = parent;
}



