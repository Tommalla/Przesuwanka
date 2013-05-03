#include <QDesktopWidget>
#include <QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "constants.h"
#include "Game.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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
	QObject::connect(this->gameHandler, SIGNAL(moveMade()), this, SLOT(updateCounter()));
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
	
	GameType type = newGameDialog.getGameType();
	
	qDebug("\ttype = %d\n", type);
	gameHandler->newGame(type, boardSize);
}

void MainWindow::updateCounter() {
	this->statusBar()->showMessage("Ilość ruchów: " + QString::number(Game::getInstance().getMovesCount()));
}





