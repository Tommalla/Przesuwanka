/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#include <cassert>
#include "GameHandler.h"
#include "Game.h"

void GameHandler::resetTiles() {
	for(vector<GraphicsTile*>::iterator iter = this->tiles.begin(); iter != this->tiles.end(); ++iter)
		(*iter)->syncWithGame();
}


GameHandler::GameHandler(QGraphicsView* graphicsView) {
	this->graphicsView = graphicsView;
	
	this->scene = new GraphicsScene(this);
	qDebug("scene size: %d x %d\n", this->scene->width(), this->scene->height());
	this->graphicsView->setScene(this->scene);
}

void GameHandler::newGame(const GameType& type, int size) {
	qDebug("GameHandler::NewGame\n\ttype = %d, size = %d\n", type, size);
	
	this->size = size;

	this->scene->setSceneRect(QRect(0, 0, this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height()));
	
	Game::getInstance().newGame(type, size);
	
	this->scene->clear();
	this->tiles.clear();
	
	for (int x = 0; x < this->size; ++x)
		for (int y = 0; y < this->size; ++y)
			if (Game::getInstance().getFieldAt(x, y) != 0) {
				tiles.push_back(new GraphicsTile(this, Game::getInstance().getFieldAt(x, y), Point(x, y)));
				this->scene->addItem(tiles.back());
			}
			
	qDebug("graphicsView: geometry: %d %d %d %d, viewport: %d %d %d %d, frame: %d %d %d %d\n",
		this->graphicsView->geometry().x(), this->graphicsView->geometry().y(), this->graphicsView->geometry().width(),
	       this->graphicsView->geometry().height(), this->graphicsView->viewport()->x(), this->graphicsView->viewport()->y(),
	       this->graphicsView->viewport()->width(), this->graphicsView->viewport()->height(), this->graphicsView->frameRect().x(),
	       this->graphicsView->frameRect().y(), this->graphicsView->frameRect().width(), this->graphicsView->frameRect().height()
	);
	
			
	this->state = PLAYING;
}

void GameHandler::initializeSolutionShow() {
	Game::getInstance().reset(SHOWING_SOLUTION);
	
	this->resetTiles();
	this->state = SHOWING_SOLUTION;
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

void GameHandler::repaintTiles() {
	for(vector<GraphicsTile*>::iterator iter = this->tiles.begin(); iter != this->tiles.end(); ++iter)
		(*iter)->generatePixmap();
}


void GameHandler::registerMove() {
	emit moveMade();
	if (Game::getInstance().isGameFinished())
		qDebug("Wygrana!");
}

const GameState GameHandler::getState() {
	return state;
}


GameHandler::~GameHandler() {
	delete this->scene;
}

void GameHandler::nextSolutionMove() {
	assert(this->state != PLAYING);
	
	qDebug("Wybity kolejny ruch z rozwiązania!");
	
	Point move = Game::getInstance().getNextSolutionMove();
	for(vector<GraphicsTile*>::iterator iter = this->tiles.begin(); iter != this->tiles.end(); ++iter)
		if ((*iter)->getRelativePosition() == move) {
			(*iter)->moveTile(Game::getInstance().getMoveFor(move));
			return;
		}
}




