#ifndef SURFACEPATTERN_H
#define SURFACEPATTERN_H
#include "Pattern.h"

class Surface;
class SurfacePattern : public Pattern
{
public:
    SurfacePattern(Surface *surface);
    ~SurfacePattern();
};

#endif // SURFACEPATTERN_H
