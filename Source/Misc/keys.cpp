#ifdef LINUX
#include <float.h>
#include <sys/time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#undef Font
#undef KeyPress
#undef Drawable
#undef Time
#undef Drawble
#undef KeyPress
#define KEYCODE XK_Down
#include "keys.h"

XKeyEvent createKeyEvent(Display *display, Window &win,
                           Window &winRoot, bool press,
                           int keycode, int modifiers)
{
   XKeyEvent event;

   event.display     = display;
   event.window      = win;
   event.root        = winRoot;
   event.subwindow   = None;
   event.time        = CurrentTime;
   event.x           = 1;
   event.y           = 1;
   event.x_root      = 1;
   event.y_root      = 1;
   event.same_screen = True;
   event.keycode     = XKeysymToKeycode(display, keycode);
   event.state       = modifiers;

   if(press)
      event.type = 2;
   else
      event.type = KeyRelease;

   return event;
}

const Result ctrlr_sendKeyPressEvent (const KeyPress &keyPress)
{
    Display *display = XOpenDisplay(0);
    if(display == NULL)
        return (Result::fail("Can't open display"));

   Window winRoot = XDefaultRootWindow(display);
   Window winFocus;
   int    revert;
   if (!XGetInputFocus(display, &winFocus, &revert))
   {
       return (Result::fail("XGetInputFocus failed"));
   }

   XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, keyPress.getKeyCode(), keyPress.getModifiers().getRawFlags());
   if (XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event) == 0)
   {
       return (Result::fail("XSendEvent failed"));
   }

   event = createKeyEvent(display, winFocus, winRoot, false, keyPress.getKeyCode(), keyPress.getModifiers().getRawFlags());
   if (XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event) == 0)
   {
       return (Result::fail("XSendEvent failed"));
   }

   XCloseDisplay(display);
   return (Result::ok());
}
#endif
