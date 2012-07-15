#include "FocusEvent.h"

FocusEvent::FocusEvent(Events::Type type):m_Type(type) {
	
}

FocusEvent::~FocusEvent(){}

Events::Type FocusEvent::type() {
	return m_Type;
}
