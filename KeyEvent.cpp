#include "KeyEvent.h"

KeyEvent::KeyEvent(Events::Type type,Keys::Key theKey,char * text,int modifierFlag,bool isAutorepeat):m_Type(type),
                                                                                        m_Key(theKey),
                                                                                        m_AutoRepeat(isAutorepeat),
                                                                                        m_ModifierState(modifierFlag),
                                                                                        m_Text(text)
{
		
}

KeyEvent::~KeyEvent() {
    if (m_Text)delete[] m_Text;
}
Events::Type KeyEvent::type(){
    return m_Type;
}

Keys::Key KeyEvent::key() {
    return m_Key;
}

bool KeyEvent::isAutoRepeat() {
    return m_AutoRepeat;
}

int KeyEvent::modifierFlags() {
    return m_ModifierState;
}
char *KeyEvent::getText() {
    return m_Text;
}
