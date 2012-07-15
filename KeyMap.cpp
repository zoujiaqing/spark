#include "KeyMap.h"
Keys::Key translateKeySymtoKey(KeySym keysym ) {

        switch(keysym) {
            case XK_BackSpace:return Keys::BackSpace;
            case XK_Tab:return Keys::Tab;
            case XK_Return:return Keys::Return;
            case XK_Escape:return Keys::Escape;
            case XK_Delete:return Keys::Delete;
            case XK_KP_Enter:return Keys::KP_Enter;
            case XK_KP_Equal:return Keys::KP_Equal;
            case XK_Mode_switch:return Keys::ModeSwitch;
        }
        if (keysym >= XK_space && keysym <= XK_asciitilde) {
                if (keysym >= XK_a && keysym <= XK_z) {
                    return (Keys::Key) (Keys::A + (keysym - XK_a));
                }
                return (Keys::Key) (Keys::Space + (keysym - XK_space));
        }
        if (keysym >= XK_Shift_L && keysym <= XK_Hyper_R) {
                return (Keys::Key) (Keys::Shift_L	+ (keysym - XK_Shift_L));
        }
        if (keysym >= XK_Home && keysym <= XK_Begin) {
                return (Keys::Key) (Keys::Home + (keysym-XK_Home));
        }
        if (keysym >= XK_Select && keysym <= XK_Break) {
                return (Keys::Key) (Keys::Select + (keysym - XK_Select));
        }
        if (keysym >= XK_Hyper_R  && keysym <= XK_F1) {
                return (Keys::Key) (Keys::F1 + (keysym - XK_F1));
        }
        if (keysym >= XK_KP_Home && keysym <= XK_KP_Delete ) {
                return (Keys::Key) (Keys::KP_Home + (keysym - XK_KP_Home));
        }
        if (keysym >= XK_KP_Multiply && keysym <= XK_KP_9) {
                return (Keys::Key) (Keys::KP_Multiply + (keysym - XK_KP_Multiply));
        }

}
