#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "NewGameDialog.h"
#include "GameHandler.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT;
    
	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
	private:
		Ui::MainWindow *ui;
		NewGameDialog newGameDialog;
		GameHandler* gameHandler;
		
	private slots:
		void showAuthor();
		void showHelp();

};

#endif // MAINWINDOW_H
