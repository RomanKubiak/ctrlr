#ifndef L_ALERT_WINDOW
#define L_ALERT_WINDOW

#include "JuceHeader.h"
#include "luabind/object_fwd.hpp"

class LAlertWindow : public AlertWindow
{
	public:
		LAlertWindow(const String &title, const String &message, AlertIconType iconType);
		~LAlertWindow();
		int runModalLoop();
		void setModalHandler(luabind::object const& _o);
		ComboBox *getComboBoxComponent(const String &comboName);

		static void showMessageBox (AlertIconType iconType, const String& title, const String& message, const String& buttonText);
		static void showMessageBoxAsync (AlertIconType iconType, const String& title, const String& message, const String& buttonText);
		static bool showOkCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text);
		static int showYesNoCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text, const String& button3Text);
		static bool showNativeDialogBox (const String& title, const String& bodyText, bool isOkCancel);
		static void queryText(AlertIconType iconType, const String &title, const String &textMessage, const String &textAreaContent, const String &textAreaLabel, const String &button1Text, const String &button2Text, bool isContentPassword, luabind::object const &result);
		static void wrapForLua (lua_State *L);
	private:
		luabind::object o;
};

#endif
