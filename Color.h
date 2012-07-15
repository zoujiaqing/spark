/*
 * Color.h
 *
 *  Created on: 15-Nov-2009
 *      Author: mugilan
 */

#ifndef COLOR_H_
#define COLOR_H_

class Color {
public:
	Color();
        Color(double red,double green,double blue,double alpha = 1.0);
	double r,g,b,a;
};

#endif /* COLOR_H_ */
