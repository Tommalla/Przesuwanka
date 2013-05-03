#include "NewGameDialog.h"
#include "ui_NewGameDialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewGameDialog) {
    ui->setupUi(this);
}

const GameType NewGameDialog::getGameType() {
	if (ui->EasyRadioButton->isChecked())
		return EASY;
	if (ui->MediumRadioButton->isChecked())
		return MEDIUM;
	if (ui->HardRadioButton->isChecked())
		return HARD;
	
	return RANDOM;
}


NewGameDialog::~NewGameDialog() {
    delete ui;
}
