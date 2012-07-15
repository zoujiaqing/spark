#include "MouseEvent.h"


MouseEvent::MouseEvent(Events::Type type,MouseButtons buttons,Point position):
                       m_Type(type),m_ButtonState(buttons),m_Position(position)
{

}
MouseEvent::~MouseEvent() {}
MouseButtons MouseEvent::getButtonState() {
    return m_ButtonState;
}

Point MouseEvent::getPosition() {
    return m_Position;
}

Events::Type MouseEvent::type() {
	return m_Type;
} 

