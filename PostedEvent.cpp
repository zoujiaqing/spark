#include "PostedEvent.h"
#include "Widget.h"
#include "Event.h"

PostedEvent::PostedEvent(Widget *receiver,Event *event)
{
    m_Event = event;
    m_Receiver = receiver;
}
