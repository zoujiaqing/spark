#ifndef AUTODISCONNECTABLE_H
#define AUTODISCONNECTABLE_H
#include <list>

#include "sigslot.h"
using namespace spark;
class AutoDisconnectable {
public:
	void registerSlot(SlotI * Slot);
	void unregisterSlot(SlotI * Slot);		
	virtual ~AutoDisconnectable();	
private:
	std::list<SlotI *> m_SlotList;
	
};
#endif
