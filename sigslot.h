/*
 * sigslot.h
 *
 *  Created on: 18-Nov-2009
 *      Author: mukilan
 */

#ifndef SIGSLOT_H_
#define SIGSLOT_H_

#include <map>
#include <cstdio>

namespace spark
{

template<class Signature>
class signal;

template<class Signature>
class SlotI;

template<class retType,class...argTypes>
class SlotI<retType (argTypes...)> {
public:
	virtual void callWithNoReturn(argTypes...) = 0;
	virtual retType call(argTypes...) = 0;
	virtual void onDeleteCallback() = 0;
	virtual void setConnectionID(signal<retType (argTypes...)> *,int) = 0;
	virtual ~SlotI() {
	}
};

/********* ========< Signal >======== ***************/

template <class retType,class ...argTypes>
class signal<retType (argTypes... )> {
public:
	signal();
	template<class ReceiverType>
	int connect(ReceiverType *receiver,retType (ReceiverType::*mem_func)(argTypes...));
	retType emit(argTypes...);
	void disconnect(int connectionId);
	virtual ~signal();
	
	
private:
	typedef SlotI<retType(argTypes...)> slotI;
	int m_CurrentConnectionId;
	std::map<int,slotI* > m_ConnectionList;

};


/********* ========<  Slot >======== ***************/

template<class ReceiverType,class retType,class... argTypes>
class slot: public SlotI<retType(argTypes...)> {
public:
	slot(ReceiverType *receiver,retType (ReceiverType::*mem_func)(argTypes...));
	virtual void callWithNoReturn(argTypes...);
	virtual retType call(argTypes...);
	virtual void onDeleteCallback();
	virtual void setConnectionID(signal<retType (argTypes...)> *,int id);
	virtual ~slot();
private:
	ReceiverType *m_Receiver;
	retType (ReceiverType::*m_mem_func)(argTypes... );
	signal<retType(argTypes...) >* m_Signal;
	int m_ConnectionID; 

};


/******************************************/
/**********  Implementation ***************/
/******************************************/

template <class retType, class... argTypes>
signal<retType(argTypes...)>::signal() {

	m_CurrentConnectionId = 0;

}
template <class retType, class... argTypes>
signal<retType(argTypes...)>::~signal() {
	auto slotIter = m_ConnectionList.begin();
	for(;slotIter != m_ConnectionList.end();++slotIter)
	{
	  delete (*slotIter).second;

	  
	}
}

/* Connects the receivers member function to this signal and
 * by creating a new slot representing the member function
 * bound to the receiver.
 * Returns the connection id which is used to disconnect the slot
 * later
 */
template <class retType, class... argTypes>
template<class ReceiverType>
int signal<retType(argTypes...)>::connect(ReceiverType* receiver,retType (ReceiverType::*mem_func)(argTypes...)){
	slot<ReceiverType,retType,argTypes...>* newslot;
	newslot = new slot<ReceiverType,retType,argTypes...>(receiver,mem_func);
	int id = m_CurrentConnectionId++;
	m_ConnectionList[id] = static_cast<slotI*>(newslot);
	newslot->setConnectionID(this,id);
	return id;
}

template <class retType, class... argTypes>
retType signal<retType(argTypes...)>::emit(argTypes... args){
	retType returnValue;

	for( auto currentConnection=m_ConnectionList.begin(); currentConnection!=m_ConnectionList.end(); ++currentConnection)
	{
              returnValue = (*currentConnection).second->call(args...);
	}

	return returnValue;
}
template <class retType, class... argTypes>
void signal<retType(argTypes...)>::disconnect(int connectionId){
	
	m_ConnectionList.erase(connectionId);

};



/////////////////////////////////////////////////// 
////////////////*  slots */ ///////////////////////
///////////////////////////////////////////////////

template <class ReceiverType,class retType, class... argTypes>
slot<ReceiverType,retType,argTypes...>::slot(ReceiverType *receiver,retType (ReceiverType::*mem_fun)(argTypes...)) {
	m_Receiver = receiver;
	m_mem_func = mem_fun;
	
	//if (m_Receiver) {
	//	m_Receiver->registerSlot((SlotI *) this);		
	//}

}
template <class ReceiverType,class retType, class... argTypes>
slot<ReceiverType,retType,argTypes...>::~slot() {
	//if(m_Receiver) m_Receiver->unregisterSlot((SlotI *) this);
}

// Calls the slots member function and discards its return value
template <class ReceiverType,class retType, class... argTypes>
void slot<ReceiverType,retType,argTypes...>::callWithNoReturn(argTypes... args) {

	(m_Receiver->*m_mem_func)(args...);
}

/* Stores the return value from the call to member function in retHolder.
 * Used only by the calling signal
 */
template <class ReceiverType,class retType, class... argTypes>
retType slot<ReceiverType,retType,argTypes...>::call(argTypes... args) {


	return (m_Receiver->*m_mem_func)(args...);

}



template <class ReceiverType,class retType, class... argTypes>
void slot<ReceiverType,retType,argTypes...>::onDeleteCallback() {
	m_Signal->disconnect(m_ConnectionID);
	m_Receiver = 0;
	delete this;
}

template <class ReceiverType,class retType, class... argTypes>
void slot<ReceiverType,retType,argTypes...>::setConnectionID(signal<retType(argTypes...)> *sig,int id) {
	m_Signal = sig;
	m_ConnectionID = id;
}

}
#endif /* SIGSLOT_H_ */


