/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */
#include <cstdio>

#include "GraphicsScene.h"

void GraphicsScene::keyReleaseEvent (QKeyEvent* event) {
	QGraphicsScene::keyReleaseEvent (event);
	printf("Testing\n");
}

