#include "stdafx.h"
/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  3 Apr 2012 10:45:28pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "CtrlrLuaManager.h"
#include "CtrlrManager/CtrlrManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
//[/Headers]

#include "CtrlrLuaConsole.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
const StringArray joinFileArray (const Array<File> ar)
{
	StringArray s;

	for (int i=0; i<ar.size(); i++)
	{
		s.add (ar[i].getFullPathName());
	}
	return (s);
}
//[/MiscUserDefs]

//==============================================================================
CtrlrLuaConsole::CtrlrLuaConsole (CtrlrPanel &_owner)
    : owner(_owner),
      luaConsoleOutput (0),
      luaConsoleInput (0),
      resizer (0)
{
    addAndMakeVisible (luaConsoleOutput = new CodeEditorComponent (outputDocument, 0));
    luaConsoleOutput->setName (L"luaConsoleOutput");

    addAndMakeVisible (luaConsoleInput = new CodeEditorComponent (inputDocument, 0));
    luaConsoleInput->setName (L"luaConsoleInput");

    addAndMakeVisible (resizer = new StretchableLayoutResizerBar (&layoutManager, 1, false));


    //[UserPreSize]
	layoutManager.setItemLayout (0, -0.001, -1.0, -0.69);
 	layoutManager.setItemLayout (1, -0.001, -0.01, -0.01);
 	layoutManager.setItemLayout (2, -0.001, -1.0, -0.30);

	luaConsoleInput->setFont (Font(owner.getOwner().getFontManager().getDefaultMonoFontName(), 12, Font::plain));
	luaConsoleOutput->setFont (Font(owner.getOwner().getFontManager().getDefaultMonoFontName(), 12, Font::plain));
	luaConsoleInput->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffffffff));
	luaConsoleOutput->setColour (CodeEditorComponent::backgroundColourId, Colour(0xffffffff));

	luaConsoleInput->addKeyListener (this);
	owner.getOwner().getCtrlrLog().addListener (this);
	lastHistoryElement = 0;
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	snips.addTokens (owner.getProperty(Ids::uiLuaConsoleSnips).toString(), "$", "\'\"");
    //[/Constructor]
}

CtrlrLuaConsole::~CtrlrLuaConsole()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	owner.getOwner().getCtrlrLog().removeListener (this);
    //[/Destructor_pre]

    deleteAndZero (luaConsoleOutput);
    deleteAndZero (luaConsoleInput);
    deleteAndZero (resizer);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CtrlrLuaConsole::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CtrlrLuaConsole::resized()
{
    luaConsoleOutput->setBounds (0, 0, getWidth() - 0, proportionOfHeight (0.6900f));
    luaConsoleInput->setBounds (0, proportionOfHeight (0.7000f), getWidth() - 0, proportionOfHeight (0.3000f));
    resizer->setBounds (0, proportionOfHeight (0.6900f), getWidth() - 0, proportionOfHeight (0.0100f));
    //[UserResized] Add your own custom resize handling here..
	Component* comps[] = { luaConsoleOutput, resizer, luaConsoleInput  };
 	layoutManager.layOutComponents (comps, 3, 0, 0, getWidth(), getHeight(), true, true);
    //[/UserResized]
}

bool CtrlrLuaConsole::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
bool CtrlrLuaConsole::keyPressed (const KeyPress& key, Component* originatingComponent)
{
	if (key.getKeyCode() == 13 && originatingComponent == luaConsoleInput && !key.getModifiers().isCtrlDown())
	{
		runCode(inputDocument.getAllContent());

		if ((bool)owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun))
		{
			inputDocument.replaceAllContent(String::empty);
		}
		return (true);
	}
	else if (key.getKeyCode() == 13 && originatingComponent == luaConsoleInput && key.getModifiers().isCtrlDown())
	{
		luaConsoleInput->insertTextAtCaret ("\n");
	}
	return (false);
}

void CtrlrLuaConsole::runCode(const String &code)
{
	luaConsoleOutput->moveCaretToEnd(false);
	luaConsoleOutput->insertTextAtCaret ("\n");
	luaConsoleOutput->insertTextAtCaret (">>> " + code + "\n");
	inputHistory.add (code);
	owner.getCtrlrLuaManager().runCode(code);
	// luaConsoleInput->clear();
}

void CtrlrLuaConsole::messageLogged (CtrlrLog::CtrlrLogMessage message)
{
	if (message.level == CtrlrLog::Lua)
	{
		// luaConsoleOutput->setCaretPosition (luaConsoleOutput->getText().length());
		luaConsoleOutput->insertTextAtCaret (message.message + "\n");
	}
	if (message.level == CtrlrLog::LuaError)
	{
		// luaConsoleOutput->setCaretPosition (luaConsoleOutput->getText().length());
		luaConsoleOutput->insertTextAtCaret (message.message + "\n");
	}
}

const PopupMenu CtrlrLuaConsole::getSnipsMenu(const int mask)
{
	PopupMenu m;

	for (int i=0; i<snips.size(); i++)
	{
		m.addItem (mask+i, snips[i]);
	}

	return (m);
}

void CtrlrLuaConsole::snipsItemClicked(Button *b)
{
	PopupMenu m;
	m.addItem (1, "Add input to snips");
	m.addSubMenu ("Run snip", getSnipsMenu(1024));
	m.addSubMenu ("Remove snip", getSnipsMenu(4096));
	m.addItem (2, "Toggle input removal after run", true, (bool)owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	const int ret = m.showAt(b);

	if (ret == 1)
	{
		snips.add (inputDocument.getAllContent());
	}
	if (ret >= 1024 && ret < 4096)
	{
		runCode (snips[ret-1024]);
	}
	if (ret >= 4096)
	{
		snips.remove (ret-4096);
	}
	if (ret == 2)
	{
		owner.setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, !owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	}
	owner.setProperty (Ids::uiLuaConsoleSnips, snips.joinIntoString("$"));
}

StringArray CtrlrLuaConsole::getMenuBarNames()
{
	const char* const names[] = { "File", "View", nullptr };
	return StringArray (names);
}

PopupMenu CtrlrLuaConsole::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
	PopupMenu menu;
	if (topLevelMenuIndex == 0)
	{
		menu.addItem (2, "Add input to snips");
		menu.addSubMenu ("Run snip", getSnipsMenu(1024));
		menu.addSubMenu ("Remove snip", getSnipsMenu(4096));
		menu.addSeparator();
		menu.addItem (1, "Close");
	}
	else if(topLevelMenuIndex == 1)
	{
		menu.addItem (3, "Toggle input removal after run", true, (bool)owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	}

	return (menu);
}

void CtrlrLuaConsole::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
	if (menuItemID == 2)
	{
		snips.add (inputDocument.getAllContent());
	}
	if (menuItemID >= 1024 && menuItemID < 4096)
	{
		runCode (snips[menuItemID-1024]);
	}
	if (menuItemID >= 4096)
	{
		snips.remove (menuItemID-4096);
	}
	if (menuItemID == 3)
	{
		owner.setProperty (Ids::uiLuaConsoleInputRemoveAfterRun, !owner.getProperty(Ids::uiLuaConsoleInputRemoveAfterRun));
	}
	owner.setProperty (Ids::uiLuaConsoleSnips, snips.joinIntoString("$"));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CtrlrLuaConsole" componentName=""
                 parentClasses="public CtrlrChildWindowContent, public CtrlrLog::Listener, public KeyListener"
                 constructorParams="CtrlrPanel &amp;_owner" variableInitialisers="owner(_owner)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <METHODS>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0"/>
  <GENERICCOMPONENT name="luaConsoleOutput" id="cf0696d15c4f91e3" memberName="luaConsoleOutput"
                    virtualName="" explicitFocusOrder="0" pos="0 0 0M 69%" class="CodeEditorComponent"
                    params="outputDocument, 0"/>
  <GENERICCOMPONENT name="luaConsoleInput" id="9630267470906dc" memberName="luaConsoleInput"
                    virtualName="" explicitFocusOrder="0" pos="0 70% 0M 30%" class="CodeEditorComponent"
                    params="inputDocument, 0"/>
  <GENERICCOMPONENT name="" id="f4fe604fd1cb0e52" memberName="resizer" virtualName=""
                    explicitFocusOrder="0" pos="0 69% 0M 1%" class="StretchableLayoutResizerBar"
                    params="&amp;layoutManager, 1, false"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
