#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

const QString VERSION = "Przesuwanka v0.1";
const QString AUTHOR = "Tomasz [Tommalla] Zakrzewski";
const QString AUTHOR_MAIL = "tz336079@students.mimuw.edu.pl";

const QString AUTHOR_MESSAGE = "<center>" + VERSION + "<br/>" +AUTHOR + "<br/><a href=\"mailto:" + AUTHOR_MAIL + "\">" + AUTHOR_MAIL + 
"</a><br/>IPP 2012/2013 <a href=\"http://www.mimuw.edu.pl\">MIMUW</a></center>";
const QString HELP_MESSAGE = QString("<center> Ktoś był na tyle \"sprytny\", żeby wymyślić *genialną* nazwę \"przesuwanka\" na") +
	QString("\"Grę w 15-tkę\" lub \"The game of 15\".<br/> Po krótce: Twoim zadaniem jest doprowadzić planszę do stanu, w ") +
	QString("którym liczby będą kolejno uporządkowane wierszami.<br/>Więcej szczegółów: ") +
	QString("<a href=\"http://pl.wikipedia.org/wiki/Piętnastka_(układanka)\">Wikipedia</a><br/></center>Klawiszologia:<br/>");
	
const QString SOLUTION_MSG = QString("Tryb pokazywania rozwiązania:<br/><b>Spacja</b> - Pauzuj/Kontynuuj Animację<br/>") +
	QString("<b>1 x LPM</b> - Pazuj animację/kolejny krok animacji<br/>") +
	QString("<b>1 x PPM</b> - Poprzedni krok pauzowanej animacji<br/>") +
	QString("<b>2 x LPM</b> - Wznów animację<br/>") +
	QString("<b>Strzałki lewo/prawo</b> - przewijanie pauzowanej animacji");
	
const int boardSize = 4;
const int animationTime = 100;
const int solutionTimerInterval = 500;
const int aStarMaxDistance = 80;

#endif