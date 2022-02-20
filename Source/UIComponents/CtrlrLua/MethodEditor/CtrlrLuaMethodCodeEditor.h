#ifndef __CTRLR_METHOD_EDITOR__
#define __CTRLR_METHOD_EDITOR__

#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrTextEditor.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrLuaCodeTokeniser.h"

class CtrlrLuaMethodEditor;
class GenericCodeEditorComponent;
class CtrlrLuaDebugger;

class CtrlrLuaMethodCodeEditor : public Component, public KeyListener, public CodeDocument::Listener, public AsyncUpdater
{
public:
	CtrlrLuaMethodCodeEditor(CtrlrLuaMethodEditor &_owner, CtrlrLuaMethod *_method);
	~CtrlrLuaMethodCodeEditor();
	void resized();
	void mouseDown (const MouseEvent &e);
	void mouseMove (const MouseEvent &e);
	bool keyPressed (const KeyPress &key, Component *originatingComponent);
	bool keyStateChanged (bool isKeyDown, Component *originatingComponent);
	const bool isMouseOverUrl(CodeDocument::Position &position, String *url=nullptr);
	void codeDocumentTextInserted (const String& newText, int insertIndex);
	void codeDocumentTextDeleted (int startIndex, int endIndex);
	void documentChanged(const bool save=false, const bool recompile=false);
	CodeDocument &getCodeDocument()															{ return (document); }
	GenericCodeEditorComponent *getCodeComponent()													{ return (editorComponent); }
	WeakReference <CtrlrLuaMethod> getMethod()												{ return (method); }
	CtrlrLuaMethodEditor& getCtrlrLuaMethodEditor()											{ return (owner);}
	void saveDocument();
	void saveAndCompileDocument();
	void handleAsyncUpdate();
	void setErrorLine (const int lineNumber);
	void setFontAndColour (const Font newFont, const Colour newColour);
    CtrlrLuaMethodEditor &getOwner();
	void findNextMatch(const String & search, bool bMatchCase);
	void gotoLine(int position, const bool selectLine=false);
	void replaceAllMatches(const String &search, const String &replace, bool bMatchCase);
	void replaceNextMatch(const String &search, const String &replace, bool bMatchCase);
	void findInAll(const String &search);
	void findInOpened(const String &search);
	void reportFoundMatch (CodeDocument &document, const String &methodName, const Range<int> range);
	const Array<Range<int> > searchForMatchesInDocument(CodeDocument &doc, const String &search);


	JUCE_LEAK_DETECTOR(CtrlrLuaMethodCodeEditor)

private:
	int lastFoundPosition;
	CtrlrLuaCodeTokeniser *codeTokeniser;
	WeakReference<CtrlrLuaMethodCodeEditor>::Master masterReference;
	friend class WeakReference<CtrlrLuaMethodCodeEditor>;
	WeakReference <CtrlrLuaMethod> method;
	GenericCodeEditorComponent *editorComponent;
	CodeDocument document;
	ValueTree methodTree;
	CtrlrLuaMethodEditor &owner;
};
//==============================================================================
class GenericCodeEditorComponent  : public CodeEditorComponent
{
private:
	class FindPanel;
	class GoToPanel;

public:
	GenericCodeEditorComponent (CtrlrLuaMethodCodeEditor &, CodeDocument&, CodeTokeniser*);
	~GenericCodeEditorComponent();
	void resized() override;

	void showFindPanel(bool bForReplace = false);
	void hideFindPanel();
	bool isFindActive();

	void showGoTOPanel();
	void hideGoTOPanel();
	void gotoLine(int position);
	void findSelection(bool forward = true);
	void findNext (bool forwards, bool skipCurrentSelection);
	void handleEscapeKey() override;
    void markedLinesChanged(int lineNumber, bool isNowSelected);
	void replaceAllMatches(const String &search, const String &replace, bool bMatchCase);
	void replaceNextMatch(const String &search, const String &replace, bool bMatchCase);
	void findInAll(const String &search);
	void findInOpened(const String &search);

	String getSearchString();
	bool isCaseSensitiveSearch();

	CtrlrLuaMethodCodeEditor& getCtrlrLuaMethodCodeEditor()		{return (owner);}
private:
	bool bSensitive;
	String lookUpString;
	ScopedPointer<FindPanel> findPanel;
	CtrlrLuaMethodCodeEditor &owner;
	ScopedPointer<GoToPanel> goToPanel;
    CtrlrLuaDebugger &getDebugger();
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenericCodeEditorComponent)
};
//==============================================================================
#endif
