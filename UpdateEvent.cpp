#include "UpdateEvent.h"

UpdateEvent::UpdateEvent(Rectangle updateRectangle)
{
    m_UpdateRectangle = updateRectangle;
}

Events::Type UpdateEvent::type()
{
    return Events::Update;
}

Rectangle UpdateEvent::getUpdateRectangle()
{
    return m_UpdateRectangle;
}

