/*
 * Color.cpp
 *
 *  Created on: 15-Nov-2009
 *      Author: mukilan
 */

#include "Color.h"

Color::Color() {
	// TODO Auto-generated constructor stub

}

Color::Color(double red,double green,double blue,double alpha) {
	r = red > 1.0 ? 1.0 : red < 0.0 ? 0.0 : red;
	g = green > 1.0 ? 1.0 : green < 0.0 ? 0.0 : green;
	b = blue > 1.0 ? 1.0 : blue < 0.0 ? 0.0 : blue;
	a = alpha > 1.0 ? 1.0 : alpha < 0.0 ? 0.0 : alpha;
}

