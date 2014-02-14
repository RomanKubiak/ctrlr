#ifndef CTRLR_COLOUR_PROPERTY_COMPONENT_H
#define CTRLR_COLOUR_PROPERTY_COMPONENT_H

#include "CtrlrPropertyComponent.h"
#include "CtrlrIDManager.h"

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

		class CtrlrColourSelectorComp   : public Component, public ButtonListener
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
					_DBG("mouseDown");
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


#endif
