#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QDialog>
#include "enums.h"

namespace Ui {
	class NewGameDialog;
}

class NewGameDialog : public QDialog
{
	Q_OBJECT;
	
	public:
		explicit NewGameDialog(QWidget *parent = 0);
		~NewGameDialog();
		const GameType getGameType();
    
	private:
		Ui::NewGameDialog *ui;
};

#endif // NEWGAMEDIALOG_H
