#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "Event.h"



namespace Keys {
enum Key{
        /* Latin character set */
        BackSpace,
        Tab,
        Return,
        Escape,
        Space = 20,
        Exclamation,
        DoubleQuote,
        Sharp,
        Dollar,
        Percentage,
        Ampersand,
        Apostrophe,
        OpenParantheses,
        CloseParanteses,
        Asterix,
        Plus,
        Minus,
        Period,
        Slash,
        Digit_1,
        Digit_2,
        Digit_3,
        Digit_4,
        Digit_5,
        Digit_6,
        Digit_7,
        Digit_8,
        Digit_9,
        Digit_0,
        Colon,
        Semicolon,
        Lesser,
        Equal,
        Greater,
        QuestionMark,
        At,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        OpenBracket = Z + 26,
        Backslash,
        CloseBracket,
        Caret,
        Underscore,
        Backtick,
        OpenBrace,
        Pipe,
        CloseBrace,
        Tilde,
        Delete,

        /* Cursor control & motion */

        Home,
        Left,
        Up,
        Right,
        Down,
        Prior,
        Page_Up,
        Next,
        Page_Down,
        End,
        Begin,

        Select,
        Print,
        Execute,
        Insert,
        Undo,
        Redo,
        Menu,
        Find,
        Cancel,
        Help,
        Break,
        ModeSwitch,
        Num_Lock,

        /* Numpad */
        KP_Enter,
        KP_Home,
        KP_Left,
        KP_Up,
        KP_Right,
        KP_Down,
        KP_PageUp,
        KP_PageDown,
        KP_End,
        KP_Begin,
        KP_Insert,
        KP_Delete,
        KP_Equal,
        KP_Multiply,
        KP_Add,
        KP_Separator,
        KP_Subtract,
        KP_Decimal,
        KP_Divide,
        KP_0,
        KP_1,
        KP_2,
        KP_3,
        KP_4,
        KP_5,
        KP_6,
        KP_7,
        KP_8,
        KP_9,

        /* Function Keys */
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        F25,
        F26,
        F27,
        F28,
        F29,
        F30,
        F31,
        F32,
        F33,
        F34,
        F35,
        /* Modifiers */
        Shift_L,
        Shift_R,
        Control_L,
        Control_R ,
        CapsLock,
        ShiftLock,
        Meta_L,
        Meta_R ,
        Alt_L,
        Alt_R ,
        Super_L,
        Super_R,
        Hyper_L,
        Hyper_R,
};


}



enum KeyboardModifiers {
    Shift   = 1,
    Control    = 2,
    Alt     = 4,
    CapsLock= 8,
    NumLock = 16,
    Meta    = 32,
    Super   = 64,
};

	
	

class KeyEvent : public Event
{
public:
    KeyEvent(Events::Type type, Keys::Key theKey,char *text,int modifierFlag,bool isAutorepeat);
    ~KeyEvent();
    virtual Events::Type type();
    Keys::Key key();
    char *getText();
    bool isAutoRepeat();
    int modifierFlags();
private:
    Events::Type m_Type;
    Keys::Key m_Key;
    bool m_AutoRepeat;
    int m_ModifierState;
    char *m_Text;


};

#endif // KEYEVENT_H
