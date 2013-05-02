/* Tomasz [Tommalla] Zakrzewski, 2013
All rights reserved */

#ifndef POINT_H
#define POINT_H

class Point {
	public:
		int x, y;
		Point(int x, int y);
		Point(){}
};

Point operator+(const Point &a, const Point &b);
const bool operator==(const Point &a, const Point &b);
const bool operator!=(const Point &a, const Point &b);

#endif // POINT_H
