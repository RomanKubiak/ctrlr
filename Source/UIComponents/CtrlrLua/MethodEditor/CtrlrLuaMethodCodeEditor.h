#ifndef __CTRLR_METHOD_EDITOR__
#define __CTRLR_METHOD_EDITOR__

#include "Methods/CtrlrLuaMethod.h"
#include "CtrlrTextEditor.h"
#include "CtrlrWindowManagers/CtrlrChildWindowContent.h"
#include "CtrlrWindowManagers/CtrlrPanelWindowManager.h"
#include "CtrlrLuaCodeTokeniser.h"

class CtrlrLuaMethodEditor;

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
		CodeEditorComponent *getCodeComponent()													{ return (editorComponent); }
		WeakReference <CtrlrLuaMethod> getMethod()												{ return (method); }
		void saveDocument();
		void saveAndCompileDocument();
		void handleAsyncUpdate();
		void setErrorLine (const int lineNumber);
		void setFontAndColour (const Font newFont, const Colour newColour);
		JUCE_LEAK_DETECTOR(CtrlrLuaMethodCodeEditor)

	private:
		CtrlrLuaCodeTokeniser *codeTokeniser;
		WeakReference<CtrlrLuaMethodCodeEditor>::Master masterReference;
		friend class WeakReference<CtrlrLuaMethodCodeEditor>;
		WeakReference <CtrlrLuaMethod> method;
		CodeEditorComponent *editorComponent;
		CodeDocument document;
		ValueTree methodTree;
		CtrlrLuaMethodEditor &owner;
};

#endif