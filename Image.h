#ifndef IMAGE_H
#define IMAGE_H
#include "Surface.h"
namespace ImageFormats {
    enum Format {
        ARGB32 = 1,
        RGB24,
        A8,
        A1
    };
}

class Image : public Surface
{
public:
    Image(ImageFormats::Format format,int width,int height);
    Image(ImageFormats::Format format,int width,int height,unsigned char *data,int stride);
    static int calculateStride(ImageFormats::Format format,int width);
    int getWidth();
    int getHeight();
    int getStride();
protected:
    int m_Width;
    int m_Height;
    int m_Stride;
};

#endif // IMAGE_H
