#include "Application.h"
#include "TestWidget.h"
#include <stdio.h>
#include <stdlib.h>


class ClickWatcher {

public:
	int onClicked(int winid){
		printf("Click Watcher received event from %d\n",winid);
		return 153;
	}
	void vClicked(int winid){
		printf("Click Watcher received event from %d\n",winid);
	}
	void vvClicked(void) {
		printf("Click Watcher:: in void handler\n");
	}
	
	int ivClicked(void) {
		printf("Click Watcher:: in int-void handler\n");
		return -1;
	}
	

};


ClickWatcher watcher;

int main() {
    using namespace spark;
    Application *app = new Application;
    Widget *mainwidget = new Widget(0,0,0,800,800);
    mainwidget->setBackground(.5, 0.5,0.5,.05);



    for (int i = 0 ; i<8 ;i++) {
        for (int j = 0 ; j < 8 ;j++){

            TestWidget *widget = new TestWidget(mainwidget,(i*100)+4,(j*100)+4,90,90);
            TestWidget *widget2 = new TestWidget(widget,9,9,70,70);
            widget2->clicked.connect(&watcher,&ClickWatcher::ivClicked);
            widget->setBackground(i/7.0,j/5.0,0.5,.8);
            widget2->setBackground(i/2.0,j/7.0,0.5,.8);
        }
    }

    mainwidget->show();

    app->run();
    delete app;
    return 0;
}
