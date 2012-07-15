#include "Rectangle.h"

Rectangle::Rectangle()
{
    x = y = width = height = 0;
}
Rectangle::Rectangle(int X,int Y,int Width,int Height)

{	
        x = X;
        y = Y;
        width = Width;
        height = Height;
	
}
 
Point Rectangle::getOrigin() {
    Point origin(x,y);
    return origin;
}
