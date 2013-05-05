/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef GRAPHICSTILE_H
#define GRAPHICSTILE_H
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include "Point.h"
#include "enums.h"

class GameHandler;

class GraphicsTile : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT;
	Q_PROPERTY(QPointF offset
	READ offset
	WRITE setOffset);
	private:
		int number, tileSize;
		GameHandler* parent;
		Point relativePosition;
		QPropertyAnimation animation;
		QColor color;
	public:
		void generatePixmap();
		const Point getRelativePosition();
		void mousePressEvent (QGraphicsSceneMouseEvent * event);
		void makeMove(const MoveType type);
		void moveTile(const Point move);
		/**
		 * @brief Zmienia położenie płytki na takie jak w grze
		 **/
		void syncWithGame();
		GraphicsTile(GameHandler* parent, const int number, const Point relativePosition);
};

#endif // GRAPHICSTILE_H
