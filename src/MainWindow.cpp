#include <QDesktopWidget>
#include <QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	
	//podpinanie sygnałów
	QObject::connect(ui->ActionZakoncz, SIGNAL(triggered()), this, SLOT(close()));
	QObject::connect(ui->ActionAutor, SIGNAL(triggered()), this, SLOT(showHelp()));
	QObject::connect(ui->ActionNowa, SIGNAL(triggered()), &newGameDialog, SLOT(exec()));
	
	//Wygląd - wyśrodkowanie, tytuł itd.
	this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
	this->setWindowTitle(VERSION);
	//TODO: Poprawić buttony i align na oknie nowej gry
	this->newGameDialog.setWindowFlags(Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::showHelp() {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Autor");
	msgBox.setText(VERSION + " by " + AUTHOR + "\n" + AUTHOR_MAIL + " 2013");
	msgBox.exec();
}



