#ifndef POSTEDEVENT_H
#define POSTEDEVENT_H
class Event;
class Widget;

struct PostedEvent
{
    PostedEvent(Widget *receiver,Event *event);
    Event* m_Event;
    Widget* m_Receiver;

};

#endif // POSTEDEVENT_H
