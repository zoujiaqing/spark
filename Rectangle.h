#ifndef RECTANGLE_H
#define RECTANGLE_H 1
#include "Point.h"

class Rectangle {

    public:
        Rectangle();
        Rectangle(int  X,int Y,int Width,int Height);
        Point getOrigin();
        int x;
        int y;
        int width;
        int height;

};
#endif 
