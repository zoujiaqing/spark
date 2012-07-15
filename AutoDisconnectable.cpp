#include "AutoDisconnectable.h"
void AutoDisconnectable::registerSlot(SlotI * Slot) {
	m_SlotList.push_back(Slot);
}

void AutoDisconnectable::unregisterSlot(SlotI * Slot) {
	
	m_SlotList.remove(Slot);
}
		
AutoDisconnectable::~AutoDisconnectable() {
			
	std::list<SlotI *>::iterator iter  = m_SlotList.begin();
	for ( ; iter != m_SlotList.end();iter++){
				
		(*iter)->onDeleteCallback();
	}		
		
}
	
