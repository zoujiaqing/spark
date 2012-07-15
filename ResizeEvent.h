#ifndef RESIZEEVENT_H
#define RESIZEEVENT_H
#include "Event.h"
#include "Size.h"
class ResizeEvent : public Event
{
public:
    ResizeEvent(Size newSize,Size oldSize);
	virtual Events::Type type();
	Size getOldSize();
	Size getNewSize();
private:
	Size m_OldSize;
	Size m_NewSize;
	
};

#endif // RESIZEEVENT_H
