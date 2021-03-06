#include <QDesktopWidget>
#include <QMessageBox>
#include <ctime>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "constants.h"
#include "Game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	srand(time(NULL));
	
	ui->setupUi(this);

	//Wygląd - wyśrodkowanie, tytuł itd.
	this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
	this->setWindowTitle(VERSION);

	//TODO: Poprawić buttony i align na oknie nowej gry
	//this->newGameDialog.setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	
	gameHandler = new GameHandler(ui->GraphicsView);
	
	//podpinanie sygnałów
	QObject::connect(ui->ActionZakoncz, SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(ui->ActionPomoc, SIGNAL(triggered()), this, SLOT(showHelp()));
	QObject::connect(ui->ActionAutor, SIGNAL(triggered()), this, SLOT(showAuthor()));
	QObject::connect(ui->ActionNowa, SIGNAL(triggered()), &newGameDialog, SLOT(exec()));
	QObject::connect(&newGameDialog, SIGNAL(accepted()), this, SLOT(newGame()));
	QObject::connect(this->gameHandler, SIGNAL(moveMade()), this, SLOT(reactToMove()));
	QObject::connect(ui->ActionPokazRozwiazanie, SIGNAL(triggered()), this, SLOT(showSolution()));
	QObject::connect(&this->solutionTimer, SIGNAL(timeout()), gameHandler, SLOT(makeNextSolutionMove()));
	QObject::connect(this->gameHandler->getScene(), SIGNAL(pauseSolution()), this, SLOT(pauseSolution()));
	QObject::connect(this->gameHandler->getScene(), SIGNAL(resumeSolution()), this, SLOT(resumeSolution()));
	
	solutionTimer.setInterval(solutionTimerInterval);
	solutionTimer.setSingleShot(false);
}

void MainWindow::show() {
	QMainWindow::show();
	this->gameHandler->newGame(EASY, boardSize);
}

void MainWindow::resizeEvent (QResizeEvent* event) {
	QWidget::resizeEvent (event);
	this->ui->GraphicsView->scene()->setSceneRect(0, 0, this->ui->GraphicsView->viewport()->width(), 
						      this->ui->GraphicsView->viewport()->height());
	
	this->gameHandler->repaintTiles();
}


MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::showAuthor() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Autor");
	msgBox.setText(AUTHOR_MESSAGE);
	msgBox.exec();
}

void MainWindow::showHelp() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Pomoc");
	msgBox.setText(HELP_MESSAGE);
	msgBox.exec();
}

void MainWindow::newGame() {
	qDebug("MainWindow::newGame()\n");
	
	solutionTimer.stop();
	GameType type = newGameDialog.getGameType();
	
	qDebug("\ttype = %d\n", type);
	this->ui->GraphicsView->setEnabled(true);
	gameHandler->newGame(type, boardSize);
}

void MainWindow::reactToMove() {
	QString prev;
	QString post = (Game::getInstance().isGameFinished()) ? " Plansza ułożona!" : "";
	
	if (this->gameHandler->getState() == PLAYING || this->gameHandler->getState() == FINISHED)
		prev = "";
	else
		prev = "Wyświetlanie rozwiązania: ";
	
	this->statusBar()->showMessage(prev + "Ilość ruchów: " + QString::number(Game::getInstance().getMovesCount()) + post);
	
	if (Game::getInstance().isGameFinished()) {
		if (this->gameHandler->getState() == PLAYING || this->gameHandler->getState() == FINISHED) {
			QMessageBox msgBox;
			msgBox.setWindowTitle("Wygrana!");
			msgBox.setText(QString("Wygrałeś w ") + QString::number(Game::getInstance().getMovesCount()) + " ruchach!");
			this->ui->GraphicsView->setEnabled(false);
			msgBox.exec();
		} else {
			this->solutionTimer.stop();
		}
		
	}
}

void MainWindow::showSolution() {
	gameHandler->initializeSolutionShow();
	
	QMessageBox msgBox;
	msgBox.setWindowTitle("Pokazywanie rozwiązania");
	msgBox.setText(SOLUTION_MSG);
	msgBox.exec();
	
	this->resumeSolution();
	//this->solutionTimer.start();
}

void MainWindow::pauseSolution() {
	this->solutionTimer.stop();
	this->gameHandler->pauseSolution();
}

void MainWindow::resumeSolution() {
	this->gameHandler->resumeSolution();
	this->solutionTimer.start();
}






