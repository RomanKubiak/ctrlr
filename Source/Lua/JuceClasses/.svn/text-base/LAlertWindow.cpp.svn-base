#include "stdafx.h"
#include "LAlertWindow.h"
#include "LComboBox.h"

LAlertWindow::LAlertWindow(const String &title, const String &message, AlertIconType iconType)
	: AlertWindow(title,message,iconType,nullptr)
{
}

LAlertWindow::~LAlertWindow()
{
}

void LAlertWindow::showMessageBox (AlertIconType iconType, const String& title, const String& message, const String& buttonText)
{
	AlertWindow::showMessageBox (iconType, title, message, buttonText, nullptr);
}

void LAlertWindow::showMessageBoxAsync (AlertIconType iconType, const String& title, const String& message, const String& buttonText)
{
	AlertWindow::showMessageBoxAsync (iconType, title, message, buttonText, nullptr);
}

bool LAlertWindow::showOkCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text)
{
	return (AlertWindow::showOkCancelBox (iconType, title, message, button1Text, button2Text, nullptr, nullptr));
}

int LAlertWindow::showYesNoCancelBox (AlertIconType iconType, const String& title, const String& message, const String& button1Text, const String& button2Text, const String& button3Text)
{
	return (AlertWindow::showYesNoCancelBox (iconType, title, message, button1Text, button2Text, button3Text, nullptr, nullptr));
}

bool LAlertWindow::showNativeDialogBox (const String& title, const String& bodyText, bool isOkCancel)
{
	return (AlertWindow::showNativeDialogBox (title, bodyText, isOkCancel));
}

void LAlertWindow::queryText(AlertIconType iconType, const String &title, const String &textMessage, const String &textAreaContent, const String &textAreaLabel, const String &button1Text, const String &button2Text, bool isContentPassword, luabind::object const &result)
{
	AlertWindow w(title, textMessage, iconType, 0);
	w.addTextEditor ("userInput", textAreaContent,  textAreaLabel, isContentPassword);
	w.addButton (button1Text, 1);
	w.addButton (button2Text, 0);
	result[1] = w.runModalLoop();
	result[2] = w.getTextEditorContents("userInput");
}

ComboBox *LAlertWindow::getComboBoxComponent(const String &comboName)
{
	ComboBox *box = AlertWindow::getComboBoxComponent (comboName);
	return (box);
}

int LAlertWindow::runModalLoop()
{
	const int ret = AlertWindow::runModalLoop();

	if (o.is_valid())
	{
		luabind::call_function<void> (o, ret, this);
	}

	return (ret);
}

void LAlertWindow::setModalHandler(luabind::object const& _o)
{
	o = _o;
}

void LAlertWindow::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<AlertWindow>("JAlertWindow")
		,
		class_<LAlertWindow, bases<AlertWindow, Component> >("AlertWindow")
			.def(constructor<const String &, const String &, AlertIconType>())
			.def("getAlertType", &AlertWindow::getAlertType)
			.def("setMessage", &AlertWindow::setMessage)
			.def("addButton", &AlertWindow::addButton)
			.def("getNumButtons", &AlertWindow::getNumButtons)
			.def("triggerButtonClick", &AlertWindow::triggerButtonClick)
			.def("setEscapeKeyCancels", &AlertWindow::setEscapeKeyCancels)
			.def("addTextEditor", &AlertWindow::addTextEditor)
			.def("getTextEditorContents", &AlertWindow::getTextEditorContents)
			.def("getTextEditor", &AlertWindow::getTextEditor)
			.def("addComboBox", &AlertWindow::addComboBox)
			.def("getComboBoxComponent", &LAlertWindow::getComboBoxComponent)
			.def("addTextBlock", &AlertWindow::addTextBlock)
			.def("addProgressBarComponent", &AlertWindow::addProgressBarComponent)
			.def("addCustomComponent", &AlertWindow::addCustomComponent)
			.def("getNumCustomComponents", &AlertWindow::getNumCustomComponents)
			.def("getCustomComponent", &AlertWindow::getCustomComponent)
			.def("removeCustomComponent", &AlertWindow::removeCustomComponent)
			.def("containsAnyExtraComponents", &AlertWindow::containsAnyExtraComponents)
			.def("setModalHandler", &LAlertWindow::setModalHandler)
			.def("runModalLoop", &LAlertWindow::runModalLoop)
			.def("exitModalState", &Component::exitModalState)
			.enum_("AlertIconType")
			[
				value("NoIcon", 0),
				value("QuestionIcon", 1),
				value("WarningIcon", 2),
				value("InfoIcon", 3)
			]
			.scope
			[
				def("showMessageBox", &LAlertWindow::showMessageBox),
				def("showMessageBoxAsync", &LAlertWindow::showMessageBoxAsync),
				def("showOkCancelBox", &LAlertWindow::showOkCancelBox),
				def("showYesNoCancelBox", &LAlertWindow::showYesNoCancelBox),
				def("showNativeDialogBox", &LAlertWindow::showNativeDialogBox),
				def("queryText", &LAlertWindow::queryText)
			]
	];
}
