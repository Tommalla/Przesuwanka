/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include "GameHandler.h"
#include "Game.h"

GameHandler::GameHandler(QGraphicsView* graphicsView) {
	this->graphicsView = graphicsView;
	
	this->scene = new GraphicsScene();
	this->graphicsView->setScene(this->scene);
}

void GameHandler::newGame(const GameType& type, int size) {
	this->size = size;
	Game::getInstance().newGame(type, size);
	
	for (int x = 0; x < this->size; ++x)
		for (int y = 0; y < this->size; ++y)
			if (Game::getInstance().getFieldAt(x, y) != 0)
				this->scene->addItem(new GraphicsTile(this, Game::getInstance().getFieldAt(x, y)));
}

void GameHandler::drawBoard() {

}

const QGraphicsView* GameHandler::getView() const {
	return this->graphicsView;
}

const int GameHandler::getSize() const {
	return this->size;
}

GameHandler::~GameHandler() {
	delete this->scene;
}



