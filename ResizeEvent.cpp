#include "ResizeEvent.h"

ResizeEvent::ResizeEvent(Size newSize,Size oldSize):
						m_OldSize(oldSize),m_NewSize(newSize)
{

}

Events::Type ResizeEvent::type() {
        return Events::Resize;
}

Size ResizeEvent::getOldSize() {
	return m_OldSize;
}

Size ResizeEvent::getNewSize() {
	return m_NewSize;
}
