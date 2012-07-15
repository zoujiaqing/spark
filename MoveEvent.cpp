#include "MoveEvent.h"

MoveEvent::MoveEvent(Point toPos)
            :m_ToPos(toPos)
{

}
Events::Type MoveEvent::type()
{
    return Events::Move;
}
