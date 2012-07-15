#include "Application.h"
#include "Debug.h"
#include <utility> // make_pair
#include <cstdio>
#include <cstdlib>
#include <X11/Xutil.h>

using namespace std;
Application *appInstance = 0;
WindowSystem *windowSystem =0;

Application::Application(){
	
	if (m_WindowSystem.initialize()) {
		appInstance = this;
		windowSystem = &m_WindowSystem;
		return;
	}
	else {
		printf("Unable to intialize window system");
		exit(-1);
	}
}
void Application::run() {
	
	m_WindowSystem.startEventLoop();



}

void Application::quit(){
	
        appInstance = 0;
        m_WindowSystem.shutdown();
	::exit(0);

}


Application::~Application(){
	
	debugMessage("In destructor\n")
	Application::quit();
	debugMessage("After exiting app\n")
	return;
}
