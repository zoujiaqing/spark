#ifndef FOCUSEVENT_H
#define FOCUSEVENT_H

#include "Event.h"

class FocusEvent : public Event {
public:
	FocusEvent(Events::Type type);
        ~FocusEvent();
	virtual Events::Type type();
private:
	Events::Type m_Type;
};
#endif 
