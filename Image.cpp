#include "Image.h"


Image::Image(ImageFormats::Format format,int width,int height)
{

    if (width && height)
    {
        m_CairoSurface = cairo_image_surface_create((cairo_format_t)format,width,height);

        m_Width = width;
        m_Height = height;
        m_Stride =  cairo_image_surface_get_stride(m_CairoSurface);
    }
}

Image::Image(ImageFormats::Format format,int width,int height,unsigned char *data,int stride)
{

    if (width && height)
    {
        m_CairoSurface = cairo_image_surface_create_for_data(data,(cairo_format_t)format,width,height,stride);
        m_Width = width;
        m_Height = height;
        m_Stride = stride;
    }
}

int Image::calculateStride(ImageFormats::Format format,int width)
{
    cairo_format_stride_for_width((cairo_format_t)format,width);
}

int Image::getWidth()
{
    return m_Width;
}

int Image::getHeight()
{
    return m_Height;
}


int Image::getStride()
{
    return m_Stride;
}
