#ifndef __CTRLR_PROPERTY_COMPONENT__
#define __CTRLR_PROPERTY_COMPONENT__

#include "CtrlrIDManager.h"
#include "CtrlrPanel/CtrlrPanel.h"
class CtrlrFloatingWindow;

class CtrlrPropertyChild: public ChangeBroadcaster
{
	public:
		virtual ~CtrlrPropertyChild() {}
		virtual void refresh()=0;
};

class CtrlrPropertyComponent  : public PropertyComponent
{
	public:
		CtrlrPropertyComponent (const Identifier &_propertyName,
								const ValueTree &_propertyElement,
								const ValueTree &_identifierDefinition,
								CtrlrPanel *_panel=nullptr,
								StringArray *_possibleChoices=nullptr,
								Array<var>  *_possibleValues=nullptr);

		virtual ~CtrlrPropertyComponent();
		int getPreferredHeight() const noexcept                 { return preferredHeight; }
		void setPreferredHeight (int newHeight) noexcept        { preferredHeight = newHeight; }
		Component *getPropertyComponent();
		void resized();
		void paint (Graphics &g);
		void refresh();

		const String getElementSubType();
		const String getElementType();

	private:
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrPropertyComponent);
		String visibleText;
		ValueTree propertyElement;
		Identifier propertyName;
		ValueTree identifierDefinition;
		Font currentFont;
		CtrlrIDManager::PropertyType propertyType;
		CtrlrPanel *panel;
		StringArray *possibleChoices;
		Array<var>  *possibleValues;
		URL url;
		String urlString;
};

class CtrlrBooleanPropertyComponent : public Component, public Button::Listener, public CtrlrPropertyChild
{
	public:
		CtrlrBooleanPropertyComponent (const Value& _valueToControl, const String& _stateText);
		~CtrlrBooleanPropertyComponent();
		void paint (Graphics& g);
		void refresh();
		void resized();
	    void buttonClicked (Button*);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrBooleanPropertyComponent);

		Value valueToControl;
		ToggleButton button;
		String onText,offText;
		String stateText;
};

class CtrlrButtonPropertyComponent : public Component, public Button::Listener, public CtrlrPropertyChild
{
	public:
		CtrlrButtonPropertyComponent (const Value &_valueToControl, const String &_propertyName);
		~CtrlrButtonPropertyComponent();
		void refresh();
		void resized();
		void buttonClicked (Button *button);

	private:
		Value valueToControl;
		String propertyName;
		TextButton button;
};

class CtrlrChoicePropertyComponent  : public Component,
									  public ComboBox::Listener,
									  public CtrlrPropertyChild
{
	public:
		CtrlrChoicePropertyComponent (const Value &_valueToControl,
                                        const StringArray *_choices,
                                        const Array<var> *_values,
                                        const bool _numeric);
		~CtrlrChoicePropertyComponent();
		void refresh();
		void resized();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void changed();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrChoicePropertyComponent)
		Value valueToControl;
		Array <var> values;
		StringArray choices;
		ScopedPointer <ComboBox> combo;
		CtrlrPropertyComponent *owner;
		bool numeric;
};

class CtrlrColourLabel : public Label
{
	TextEditor *createEditorComponent ()
	{
		TextEditor* const ed = new TextEditor (getName());
		ed->setColour (TextEditor::highlightColourId, findColour (Label::backgroundColourId).contrasting (0.5f));
		ed->setInputRestrictions (8, "ABCDEFabcdef01234567890");
		ed->applyFontToAllText (getLookAndFeel().getLabelFont (*this));
		copyAllExplicitColoursTo (*ed);
		return ed;
	}
};

class CtrlrColourEditorComponent : 	public Component,
									public ChangeListener,
									public ChangeBroadcaster,
									public Label::Listener
{
	public:
		CtrlrColourEditorComponent(ChangeListener *defaultListener=0);
		~CtrlrColourEditorComponent() { }
		void updateLabel();
		void labelTextChanged (Label *labelThatHasChanged);
		void resized();
		void resetToDefault() { colour = Colours::black; sendChangeMessage(); }
		void setColour (const Colour& newColour, const bool sendChangeMessageNow=false);
		const Colour getColour(){ return (colour); }
		void refresh() { updateLabel(); }
		void mouseDown (const MouseEvent &e);
		void changeListenerCallback (ChangeBroadcaster* source);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrColourEditorComponent)

	private:
		CtrlrColourLabel colourTextInput;
		Colour colour;
		bool canResetToDefault;

		class CtrlrColourSelectorComp   : public Component, public Button::Listener
		{
			public:
				CtrlrColourSelectorComp (CtrlrColourEditorComponent* owner_, const bool canResetToDefault) : owner (owner_), defaultButton (0)
				{
		            addAndMakeVisible (selector = new ColourSelector());
					selector->setName ("Colour");
					selector->setCurrentColour (owner->getColour());
					selector->addChangeListener (owner);
					//Desktop::getInstance().addGlobalMouseListener(this);

					if (canResetToDefault)
					{
		                addAndMakeVisible (defaultButton = new TextButton ("Reset to Default"));
						defaultButton->addListener (this);
					}

					setSize (300,400);
				}

				~CtrlrColourSelectorComp()
				{
		            deleteAllChildren();
				}

				void mouseDown (const MouseEvent &e)
				{
				}

				void resized()
				{
		            if (defaultButton != 0)
					{
		                selector->setBounds (0, 0, getWidth(), getHeight() - 30);
						defaultButton->changeWidthToFitText (22);
						defaultButton->setTopLeftPosition (10, getHeight() - 26);
					}
					else
					{
		                selector->setBounds (0, 0, getWidth(), getHeight());
					}
				}

				void buttonClicked (Button*)
		        {
					owner->resetToDefault();
					owner->refresh();
					selector->setCurrentColour (owner->getColour());
				}

				JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrColourSelectorComp)
		private:

			CtrlrColourEditorComponent* owner;
			ColourSelector* selector;
			TextButton* defaultButton;
		};
};

class CtrlrColourPropertyComponent : public Component, public ChangeListener, public CtrlrPropertyChild
{
	public:
		CtrlrColourPropertyComponent (const Value &_valueToControl);
		~CtrlrColourPropertyComponent();
		void refresh();
		void changeListenerCallback (ChangeBroadcaster* source);
		void resized();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrColourPropertyComponent)

	private:
		Value valueToControl;
		CtrlrColourEditorComponent cs;
};

class CtrlrReadOnlyProperty : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrReadOnlyProperty (const Identifier &_propertyName,
										const ValueTree &_propertyElement,
										const ValueTree &identifier,
										CtrlrPanel *panel=nullptr,
										StringArray *possibleChoices=nullptr,
										StringArray *possibleValues=nullptr);
		~CtrlrReadOnlyProperty();
		void refresh();
		void resized();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrReadOnlyProperty)

	private:
		Label value;
		ValueTree propertyElement;
		Identifier propertyName;
};

class CtrlrExpressionProperty  : public Component,
                                 public TextEditor::Listener,
								 public Button::Listener,
								 public CtrlrPropertyChild
{
	public:
		CtrlrExpressionProperty (const Value &_valeToControl);
		~CtrlrExpressionProperty();
		void refresh();
		void textEditorTextChanged (TextEditor &editor);
		void textEditorReturnKeyPressed (TextEditor &editor);
		void textEditorFocusLost (TextEditor &editor);
		const bool compile(const bool setPropertyIfValid);
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrExpressionProperty);

	private:
		CtrlrFloatingWindow *externalEditorWindow;
		Value valeToControl;
		TextEditor* text;
		ImageButton* apply;
};

class CtrlrFileProperty  : public Component, public Label::Listener, public Button::Listener, public CtrlrPropertyChild
{
	public:
		CtrlrFileProperty (const Value &_valeToControl);
		~CtrlrFileProperty();
		void refresh();
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);
		void labelTextChanged (Label* labelThatHasChanged);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrFileProperty);
		Value valueToControl;
		Label *path;
		TextButton *browse;
};

class CtrlrFontPropertyComponent  : public Component,
									public ComboBox::Listener,
									public Button::Listener,
									public Slider::Listener,
									public CtrlrPropertyChild,
									public LookAndFeel_V2
{
	public:
		CtrlrFontPropertyComponent (const Value &_valueToControl, CtrlrPanel *_owner);
		~CtrlrFontPropertyComponent();
		void refresh();
		Font getFont();
		void resized();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void buttonClicked (Button* buttonThatWasClicked);
		void sliderValueChanged (Slider* sliderThatWasMoved);
		Label* createSliderTextBox (Slider& slider);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrFontPropertyComponent);

		class SliderLabelComp : public Label
		{
			public:
				SliderLabelComp() : Label (String::empty, String::empty) {}
				void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) {}
		};

	private:
		Value valueToControl;
		StringArray choices;
		CtrlrPanel *owner;
		ComboBox* typeface;
		ImageButton* fontBold;
		ImageButton* fontItalic;
		ImageButton* fontUnderline;
		Slider* fontSize,*horizontalScale,*kerning;
};

class CtrlrLuaMethodProperty  : public Component,
								public ComboBox::Listener,
								public Button::Listener,
								public CtrlrPropertyChild
{
	public:
		CtrlrLuaMethodProperty (const Value &_valeToControl, const Identifier &_id, CtrlrPanel *_owner);
		~CtrlrLuaMethodProperty();
		void refresh();
		void resized();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void buttonClicked (Button* buttonThatWasClicked);

	private:
		Value valeToControl;
		Identifier id;
		String propertyName;
		CtrlrPanel *owner;
		ComboBox* methodSelectorCombo;
		ImageButton* editMethodButton;
		ImageButton* newMethodButton;
		ImageButton* deleteMethodButton;
};

class CtrlrModulatorListProperty :	public CtrlrPropertyChild,
									public Component,
									public ComboBox::Listener,
									public CtrlrPanel::Listener
{
	public:
		CtrlrModulatorListProperty (const Value &_valueToControl, CtrlrPanel *_owner);
		~CtrlrModulatorListProperty();
		void refresh();
		void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
		void resized();
		void modulatorChanged (CtrlrModulator *modulatorThatChanged);
		void modulatorAdded (CtrlrModulator *modulatorThatWasAdded);
		void modulatorRemoved (CtrlrModulator *modulatorRemoved);
		void listChanged();

	private:
		CtrlrPanel *owner;
		Value valueToControl;
		StringArray choices;
		ScopedPointer <ComboBox> combo;
		bool numeric;
};

class MultiMidiAlert : public AlertWindow
{
	public:
		MultiMidiAlert ()
			:	AlertWindow (String::empty, "Add a new message to the multi list\n[-1 for parent value setting, -2 for parent number setting. For SysEx message the formula is the same as in the SysEx editor.]", AlertWindow::QuestionIcon, 0),
				valueSlider("Controller Value"), numberSlider("Controller Number")
		{
			const char *types[] = { "CC", "Aftertouch", "ChannelPressure", "NoteOn", "NoteOff", "SysEx", "--", "ProgramChange", "PitchWheel", 0 };
			const char *v[] = { "Direct", "LSB7bit", "MSB7bit", "LSB4bit", "MSB4bit", 0};
			addComboBox ("messageType", StringArray(types), "Midi message type");
			addComboBox ("value", StringArray(v), "Value mapping");
			addComboBox ("number", StringArray(v), "Number mapping");
			addTextEditor ("sysexFormula", "F0 00 F7", "SysEx Formula", false);
			valueSlider.setSize (300,32);
			valueSlider.setSliderStyle (Slider::LinearBar);
			valueSlider.setRange (-2,127,1);
			valueSlider.setValue (-1);

			numberSlider.setSize (300,32);
			numberSlider.setSliderStyle (Slider::LinearBar);
			numberSlider.setRange (-2,127,1);
			numberSlider.setValue (-1);

			addCustomComponent (&numberSlider);
			addCustomComponent (&valueSlider);

			addButton ("OK", 1);
			getComboBoxComponent("messageType")->setSelectedId (1, dontSendNotification);
			getComboBoxComponent("value")->setSelectedId (1, dontSendNotification);
			getComboBoxComponent("number")->setSelectedId (1, dontSendNotification);
		}

		void buttonClicked (Button* button)
		{
			getParentComponent()->exitModalState(1);
		}

		const String getValue()
		{
			String ret;
			ret << getComboBoxComponent("messageType")->getText() + ",";
			ret << getComboBoxComponent("number")->getText() + ",";
			ret << getComboBoxComponent("value")->getText() + ",";
			ret << String (((Slider*)getCustomComponent(0))->getValue()) + ",";
			ret << String (((Slider*)getCustomComponent(1))->getValue()) + ",";
			ret << getTextEditor ("sysexFormula")->getText();
			return (ret);
		}

	private:
		Slider valueSlider, numberSlider;
};

class CtrlrMultiMidiPropertyComponent  : public Component,
                                         public ListBoxModel,
                                         public Label::Listener,
										 public Button::Listener,
										 public CtrlrPropertyChild
{
	public:
		CtrlrMultiMidiPropertyComponent (const Value &_valueToControl);
		~CtrlrMultiMidiPropertyComponent();
		void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
		int getNumRows();
		void refresh();
		void loadAdditionalTemplates(const File &templateFile);
		Component *refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);
		void labelTextChanged (Label* labelThatHasChanged);
		void paint (Graphics& g);
		void resized();
		void buttonClicked (Button* buttonThatWasClicked);
		void mouseDown (const MouseEvent& e);
		void mouseDoubleClick (const MouseEvent& e);

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrMultiMidiPropertyComponent)
		MultiMidiAlert questionWindow;
		StringArray values;
		Value valueToControl;
		StringPairArray templates;
		ImageButton* add;
		ImageButton* remove;
		ListBox* list;
		ImageButton* copy;
		ImageButton* paste;
	    ImageButton* insert;
};

class CtrlrSliderPropertyComponent   : public Component, private Slider::Listener, public CtrlrPropertyChild
{
	public:
		CtrlrSliderPropertyComponent (const Value &_valueToControl, double rangeMin, double rangeMax, double interval);
		~CtrlrSliderPropertyComponent();
		virtual void setValue (double newValue);
		virtual double getValue() const;
		void refresh();
		void sliderValueChanged (Slider *sliderThatChanged);
		void resized();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrSliderPropertyComponent);
		Slider slider;
		Value valueToControl;
};

class SysExRow : public Component
{
	public:
		SysExRow(const int _n=1, const int _w=32, const int _gap=4);
		void paint (Graphics &g);
		void resized();

	private:
		int n,w,gap;
};

class CtrlrSysExEditor  : public Component,
						  public Slider::Listener,
						  public Label::Listener,
                          public ChangeBroadcaster
{
	public:
		CtrlrSysExEditor (Value &_val, CtrlrPanel *_panel);
		~CtrlrSysExEditor();
		void setLength (const int newLength);
		Label *addByte(const String &byteAsString);
		const String getValue();
		const PopupMenu getVendorIdMenu();
		void paint (Graphics& g);
		void resized();
		void sliderValueChanged (Slider* sliderThatWasMoved);
		void labelTextChanged (Label* labelThatHasChanged);
		void mouseDown (const MouseEvent& e);

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrSysExEditor)

	private:
		Value val;
		CtrlrPanel *owner;
		StringArray splitMessage;
		OwnedArray <Label> byteValueLabels;
		OwnedArray <SysExRow> rows;
		int currentMessageLength;
		Slider* messageLength;
		Label* label;

};

class CtrlrSysExFormulaEditor  : public Component
{
public:
    //==============================================================================
    CtrlrSysExFormulaEditor ();
    ~CtrlrSysExFormulaEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	CodeDocument forwardFormulaDocument, reverseFormulaDocument;
    //[/UserVariables]

    //==============================================================================
    CodeEditorComponent* forwardFormula;
    CodeEditorComponent* reverseFormula;
    Label* forwardLabel;
    Label* reverseLabel;
    Label* label;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    CtrlrSysExFormulaEditor (const CtrlrSysExFormulaEditor&);
    const CtrlrSysExFormulaEditor& operator= (const CtrlrSysExFormulaEditor&);
};

class CtrlrSysExPropertyComponent  : public Component,
									 public Label::Listener,
									 public Button::Listener,
									 public CtrlrPropertyChild,
									 public ChangeListener
{
	public:
		CtrlrSysExPropertyComponent (const Value &_valueToControl, const ValueTree &_propertyTree, const Identifier &_propertyName, CtrlrPanel *_owner);
		~CtrlrSysExPropertyComponent();
		void refresh();
		void resized();
		void labelTextChanged (Label* labelThatHasChanged);
		void buttonClicked (Button* buttonThatWasClicked);
		void changeListenerCallback (ChangeBroadcaster *cb);
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrSysExPropertyComponent)

	private:
		Value valueToControl;
		Label* sysexPreview;
		TextButton* editButton;
		ImageButton* copy;
		ImageButton* paste;
		ValueTree propertyTree;
		Identifier propertyName;
		CtrlrPanel *owner;
};

class CtrlrTextPropertyComponent : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrTextPropertyComponent (const Value& _valueToControl,
									const int maxNumChars,
									const bool isMultiLine,
									const bool isReadOnly=false);

		~CtrlrTextPropertyComponent();
		void refresh();
		void setText (const String& newText);
		String getText() const;
		void textWasEdited();
		void resized();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrTextPropertyComponent);

		ScopedPointer<Label> textEditor;
		void createEditor (int maxNumChars, bool isMultiLine);
		Value valueToControl;
};

class CtrlrTimestampProperty : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrTimestampProperty (const Value& _valueToControl);
		~CtrlrTimestampProperty();
		void refresh();
		void resized();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrTimestampProperty);
		ScopedPointer<Label> textEditor;
		Value valueToControl;
};

class CtrlrUnknownPropertyComponent : public Component, public CtrlrPropertyChild
{
	public:
		CtrlrUnknownPropertyComponent(const Identifier &_propertyName,
										const ValueTree &_propertyElement,
										const ValueTree &identifier,
										CtrlrPanel *panel=nullptr,
										StringArray *possibleChoices=nullptr,
										StringArray *possibleValues=nullptr);
		~CtrlrUnknownPropertyComponent();
		void resized();
		void refresh();

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CtrlrUnknownPropertyComponent);
		Label l;
		Identifier propertyName;
		ValueTree propertyElement;
};

#endif
