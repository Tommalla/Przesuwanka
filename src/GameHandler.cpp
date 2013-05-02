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
}

void GameHandler::drawBoard() {

}

GameHandler::~GameHandler() {
	delete this->scene;
}



