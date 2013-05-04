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
		void show();
	protected:
		void resizeEvent (QResizeEvent * event);
	private:
		Ui::MainWindow *ui;
		NewGameDialog newGameDialog;
		GameHandler* gameHandler;
		
	private slots:
		void showAuthor();
		void showHelp();
		void newGame();
		void reactToMove();

};

#endif // MAINWINDOW_H
