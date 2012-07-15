#ifndef MATRIX_H
#define MATRIX_H

#include <cairo/cairo.h>

class Matrix
{
public:
    Matrix();
    Matrix(double xx,double yx,double xy,double yy,double x0,double y0);
    ~Matrix();
    void init(double xx,double yx,double xy,double yy,double x0,double y0);
    void initIdentity();
    void initTranslate(double tx,double ty);
    void initScale(double sx,double sy);
    void initRotate(double radians);

    void translate(double tx,double ty);
    void scale(double sx,double sy);
    void rotate(double radians);

    bool invert();

    void multiply(const Matrix& otherMatrix);

    cairo_matrix_t *getCairoMatrix();


private:
    cairo_matrix_t *m_CairoMatrix;
};

#endif // MATRIX_H
