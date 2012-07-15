#ifndef EVENT_H
#define EVENT_H


class Widget;
namespace Events {
    enum Type {
        Delete = 1,
        FocusGain,
        FocusLoss,
        KeyPressed,
        KeyReleased,
        Move,
        MousePress,
        MouseRelease,
        MouseMove,
        MouseEnter,
        MouseLeave,
        Paint,
        Resized,
        StackOrderChange,
        Timer,
        Update,
        VisiblityChange,
        UserEvent

    };
}
class Event 	{
public:
    Event() {}
    Widget * target(){ return m_Target; }
    virtual ~Event() {}
    virtual Events::Type type() = 0;
private:
	Widget *m_Target;
};

#endif
