SOURCES =   test.cpp \
            Widget.cpp \
            Application.cpp \
            Painter.cpp \
            WindowSystem.cpp \
            TestWidget.cpp \
            Color.cpp \
            Point.cpp \
	    PointF.cpp \
            Rectangle.cpp \
	    RectangleF.cpp \
            Surface.cpp \
            Image.cpp \
            Size.cpp \
            NativeWindowSurface.cpp \
            MouseEvent.cpp \
            MoveEvent.cpp \
            KeyEvent.cpp \
            KeyMap.cpp \
            FocusEvent.cpp \
            TimerEvent.cpp \
            UpdateEvent.cpp \
            PostedEvent.cpp \
	    PaintEvent.cpp \
	    Pattern.cpp \
	    SolidPattern.cpp \
	    SurfacePattern.cpp \
	    Gradient.cpp \
	    LinearGradient.cpp \
	    RadialGradient.cpp \
	    Matrix.cpp \
	    AreaF.cpp


IFLAGS = `pkg-config --cflags cairo`
LFLAGS =  -lX11 -lXcomposite -lXrender  `pkg-config --libs cairo`
  
EXEC = test 

all:
	    g++  -O3 -o $(EXEC) -std=c++0x $(IFLAGS) $(SOURCES) $(LFLAGS)
