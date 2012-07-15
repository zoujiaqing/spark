#include "Matrix.h"

Matrix::Matrix()
        :m_CairoMatrix(new cairo_matrix_t)
{
    cairo_matrix_init_identity(m_CairoMatrix);
}

Matrix::Matrix(double xx,double yx,double xy,double yy,double x0,double y0)
        :m_CairoMatrix(new cairo_matrix_t)
{
    cairo_matrix_init(m_CairoMatrix,xx,yx,xy,yy,x0,y0);
}

Matrix::~Matrix()
{
    if (m_CairoMatrix) delete m_CairoMatrix;
}

void Matrix::init(double xx,double yx,double xy,double yy,double x0,double y0)
{
    cairo_matrix_init(m_CairoMatrix,xx,yx,xy,yy,x0,y0);
}

void Matrix::initIdentity()
{
    cairo_matrix_init_identity(m_CairoMatrix);
}

void Matrix::initTranslate(double tx,double ty)
{
    cairo_matrix_init_translate(m_CairoMatrix,tx,ty);
}

void Matrix::initScale(double sx,double sy)
{
    cairo_matrix_init_scale(m_CairoMatrix,sx,sy);
}

void Matrix::initRotate(double radians)
{
    cairo_matrix_init_rotate(m_CairoMatrix,radians);
}

void Matrix::translate(double tx,double ty)
{
    cairo_matrix_translate(m_CairoMatrix,tx,ty);
}

void Matrix::scale(double sx,double sy)
{
    cairo_matrix_scale(m_CairoMatrix,sx,sy);
}

void Matrix::rotate(double radians)
{
    cairo_matrix_rotate(m_CairoMatrix,radians);
}

bool Matrix::invert()
{
    if(cairo_matrix_invert(m_CairoMatrix) == CAIRO_STATUS_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Matrix::multiply(const Matrix& otherMatrix)
{
    cairo_matrix_multiply(m_CairoMatrix,m_CairoMatrix,otherMatrix.m_CairoMatrix);
}

cairo_matrix_t * Matrix::getCairoMatrix()
{
    return m_CairoMatrix;
}
