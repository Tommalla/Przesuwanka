#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>
#include <string>

using namespace std;

const QString VERSION = "Przesuwanka v0.1";
const QString AUTHOR = "Tomasz [Tommalla] Zakrzewski";
const QString AUTHOR_MAIL = "tz336079@students.mimuw.edu.pl";

const QString AUTHOR_MESSAGE = "<center>" + VERSION + "<br/>" +AUTHOR + "<br/><a href=\"mailto:" + AUTHOR_MAIL + "\">" + AUTHOR_MAIL + 
"</a><br/>IPP 2012/2013 <a href=\"http://www.mimuw.edu.pl\">MIMUW</a></center>";
const QString HELP_MESSAGE = QString::fromUtf8((QString("<center> Ktoś był na tyle \"sprytny\", żeby wymyślić *genialną* nazwę \"przesuwanka\" na") +
	QString("\"Grę w 15-tkę\" lub \"The game of 15\".<br/> Po krótce: Twoim zadaniem jest doprowadzić planszę do stanu, w ") +
	QString("którym liczby będą kolejno uporządkowane wierszami.<br/>Więcej szczegółów: ") +
	QString("<a href=\"http://pl.wikipedia.org/wiki/Piętnastka_(układanka)\">Wikipedia</a><br/></center>Klawiszologia:<br/>")).toStdString().c_str());
	
const QString SOLUTION_MSG = QString::fromUtf8(
	(QString("Tryb pokazywania rozwiązania:<br/><b>Spacja</b> - Pauzuj/Kontynuuj Animację<br/>") +
	QString("<b>1 x LPM</b> - Pazuj animację/kolejny krok animacji<br/>") +
	QString("<b>1 x PPM</b> - Poprzedni krok pauzowanej animacji<br/>") +
	QString("<b>2 x LPM</b> - Wznów animację<br/>") +
	QString("<b>Strzałki lewo/prawo</b> - przewijanie pauzowanej animacji")).toStdString().c_str()
	);

//GUI
const int boardSize = 4;
const int lowerColorLimit = 15;
const int animationTime = 100;
const int solutionTimerInterval = 500;

//obliczanie rozwiązania
const int aStarMaxDistance = 80;
const int manhattanMetricMultiplier = 4;

#endif