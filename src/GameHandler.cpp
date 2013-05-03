/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include "GameHandler.h"
#include "Game.h"

GameHandler::GameHandler(QGraphicsView* graphicsView) {
	this->graphicsView = graphicsView;
	
	this->scene = new GraphicsScene();
	qDebug("scene size: %d x %d\n", this->scene->width(), this->scene->height());
	this->graphicsView->setScene(this->scene);
}

void GameHandler::newGame(const GameType& type, int size) {
	qDebug("GameHandler::NewGame\n\ttype = %d, size = %d\n", type, size);
	this->size = size;
	Game::getInstance().newGame(type, size);
	
	this->scene->setSceneRect(QRect(0, 0, this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height()));
	
	qDebug("graphicsView: geometry: %d %d %d %d, viewport: %d %d %d %d, frame: %d %d %d %d\n",
		this->graphicsView->geometry().x(), this->graphicsView->geometry().y(), this->graphicsView->geometry().width(),
	       this->graphicsView->geometry().height(), this->graphicsView->viewport()->x(), this->graphicsView->viewport()->y(),
	       this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height(), this->graphicsView->frameRect().x(),
	       this->graphicsView->frameRect().y(), this->graphicsView->frameRect().width(), this->graphicsView->frameRect().height()
	);
	
	for (int x = 0; x < this->size; ++x)
		for (int y = 0; y < this->size; ++y)
			if (Game::getInstance().getFieldAt(x, y) != 0)
				this->scene->addItem(new GraphicsTile(this, Game::getInstance().getFieldAt(x, y), Point(x, y)));
			
}

const QGraphicsView* GameHandler::getView() const {
	return this->graphicsView;
}

const int GameHandler::getSize() const {
	return this->size;
}
const GraphicsScene* GameHandler::getScene() const {
	return this->scene;
}


GameHandler::~GameHandler() {
	delete this->scene;
}



