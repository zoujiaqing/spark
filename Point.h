#ifndef POINT_H
#define POINT_H 

class Point {
	public:
         Point();
         Point(int X,int Y);
         bool operator<(const Point& point);
         bool operator<=(const Point& point);
         int x;
	 int y;
};
 
#endif
