#include "TestWidget.h"
#include "Debug.h"
#include "Painter.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include <stdio.h>
#include "Application.h"
#include "LinearGradient.h"
#include "Point.h"
#include "Matrix.h"
TestWidget::TestWidget(Widget *parentWidget,int x,int y,int width,int height):Widget(parentWidget,x,y,width,height),
    m_DownColor(.2,.2,.2,0.7),
    m_EnterColor(.7,.7,.7,0.7)
{
    state = 3;
    mousepressed = false;

}

void TestWidget::onPaintEvent(PaintEvent *event) {

    debugMessage("Check point :in testwidget paintevent\n")
        Painter painter(event);

    LinearGradient gradient(0.0 ,0.0,0.0,(double) height());

    switch(state)
    {
        case 1:
            gradient.addColorStop(0.0,227/256.0,227/256.0,227/256.0);
            gradient.addColorStop(1.0,126/256.0,126/256.0,126/256.0);
            painter.setSource(gradient);
            painter.drawRoundedRect(0.0,0.0,width(),height(),5.0);
            painter.paint();
            break;
        case 2:
        case 4:
            painter.setSource(m_EnterColor);
            painter.drawRoundedRect(0.0,0.0,width(),height(),5.0);
            painter.paint();
            break;
        case 3:
            //Color NormalColor = backgroundColor();
            // painter.setSource(NormalColor);
            //painter.drawRoundedRect(0.0,0.0,width(),height(),5.0);

            gradient.addColorStop(0.0,227/256.0,227/256.0,227/256.0);
            gradient.addColorStop(1.0,126/256.0,126/256.0,126/256.0);
            painter.setSource(gradient);
            painter.drawRoundedRect(0.0,0.0,width(),height(),5.0);
            painter.fillPreserve();
            painter.setSource(Color(.2,.2,.2,1.0));
            painter.setLineWidth(1.0);
            painter.strokePreserve();
            break;
    }




    //painter.fillRect(getBackground());
    return;
}

bool TestWidget::onMouseEvent(MouseEvent *event) {


    switch (event->type()) {

        case Events::MouseMove:
            debug("Mouse moved at %d ,%d\n",event->getPosition().x,event->getPosition().y);

            if(mousepressed)
            {
                Point point =   origin();
                move(Point(point.x + (event->getPosition().x - startp.x) ,point.y + (event->getPosition().y - startp.y)));


            }

            return true;

        case Events::MousePress:
            debug("Mouse pressed at %d ,%d\n",event->getPosition().x,event->getPosition().y);
            mousepressed = true;
            startp.x = event->getPosition().x;
            startp.y = event->getPosition().y;
            state = 1;
            getFocus(); 
            break;
        case Events::MouseRelease:
            debug("Mouse released at %d ,%d\n",event->getPosition().x,event->getPosition().y);
            mousepressed = false;
            state = 2;
            clicked.emit();
            break;
        case Events::MouseLeave:
            debug("Mouse leave ",event->getPosition().x,event->getPosition().y);

            state = 3;

            break;
        case Events::MouseEnter:
            debug("Mouse enter ",event->getPosition().x,event->getPosition().y);
            mousepressed = false;
            state = 2;
            break;

    }
    update();
    return true;

}
bool TestWidget::onKeyPressEvent(KeyEvent *event){
    m_Text = event->getText();
    printf("You pressed the key %s\n",m_Text);
    if(event->key() == Keys::Shift_L ) {printf("the left shift key was pressed\n"); }
    if(event->key() == Keys::Escape ) appInstance->quit();
    if(event->modifierFlags() & Shift) {printf("Shift was pressed\n"); }

    if(event->key() == Keys::Alt_R )  toTop();
    if(event->key() == Keys::Alt_L )  toBottom();
    if(event->key() == Keys::Up )     move(Point(x(),y()-5));
    if(event->key() == Keys::Down )   move(Point(x(),y()+5));
    if(event->key() == Keys::Left )   move(Point(x()-5,y()));
    if(event->key() == Keys::Right)   move(Point(x()+5,y()));
    if(event->key() == Keys::Super_L ) {printf("hA HA ha\n"); }
    return true;
}
bool TestWidget::onKeyReleaseEvent(KeyEvent *event){

    /* m_Text = event->getText();
       printf("You released the key %s\n",m_Text);
       printf("MODIFIERS: %d\n",event->modifierFlags());
       if(event->modifierFlags() & CapsLock) {printf("Caps lock was on\n"); }
       if(event->modifierFlags() & Shift) {printf("Shift was pressed\n"); }
       if(event->modifierFlags() & NumLock) {printf("Numlock was on\n"); }
       if(event->modifierFlags() & Control) {printf("Control was pressed\n"); }
       if(event->modifierFlags() & Alt) {printf("Alt was pressed\n"); }
       if(event->modifierFlags() & Super) {printf("Super was pressed\n"); }
       if(event->modifierFlags() & Meta) {printf("Meta was pressed\n"); }
       return true;
       */
}
