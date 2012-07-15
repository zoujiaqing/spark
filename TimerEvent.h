#ifndef TIMEREVENT_H
#define TIMEREVENT_H
#include "Event.h"
class TimerEvent : public Event
{
public:
    TimerEvent();
    virtual Events::Type type();
    
};

#endif // TIMEREVENT_H
