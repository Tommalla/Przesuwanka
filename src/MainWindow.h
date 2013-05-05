#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
		QTimer solutionTimer;
		
	private slots:
		void showAuthor();
		void showHelp();
		void newGame();
		void reactToMove();
		void showSolution();
		void pauseSolution();
		void resumeSolution();

};

#endif // MAINWINDOW_H
