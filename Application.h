#ifndef APPLICATION_H
#define APPLICATION_H 1

#include "WindowSystem.h"
#include "Widget.h"
#include <X11/Xlib.h>
#include <map>
class Application {

	public:
	  Application();
	  void run();
	  void quit();
	  Application* instance();
	  ~Application();

	private:	  
	  WindowSystem m_WindowSystem; 
	  Widget *mMainWindow;
	  friend class Widget;
	  friend class Painter;
	   
};

extern Application *appInstance;
extern WindowSystem *windowSystem;

#endif
