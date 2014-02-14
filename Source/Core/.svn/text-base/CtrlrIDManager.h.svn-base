#ifndef __CTRLR_ID_MANAGER__
#define __CTRLR_ID_MANAGER__

#include "CtrlrIDs.h"

class CtrlrPanel;

#define MIN_CONTROLLER_VALUE			-65536.0
#define MAX_CONTROLLER_VALUE			65536.0
#define MIN_CONTROLLER_NUMBER			0
#define MAX_CONTROLLER_NUMBER			65536.0
#define IMAGE_LAYOUT					"Tile=8192,xLeft=1,xRight=2,xMid=4,yTop=8,yBottom=16,yMid=32,stretchToFit=64,fillDestination=128,onlyReduceInSize=256,onlyIncreaseInSize=512,centred=36"
#define TEXT_JUSTIFICATION				"left,right,horizontallyCentred,top,bottom,verticallyCentred,horizontallyJustified,centred,centredLeft,centredRight,centredTop,centredBottom,topLeft,topRight,bottomLeft,bottomRight"

class CtrlrIDManager
{
	public:
		enum PropertyType
		{
			Numeric,
			Text,
			MultiLine,
			MultiLineSmall,
			Bool,
			VarNumeric,
			VarText,
			Colour,
			Font,
			MultiMidi,
			SysEx,
			LuaMethod,
			ActionButton,
			Expression,
			UnknownProperty,
			ReadOnly,
			FileProperty,
			Timestamp,
			ModulatorList
		};

		class VendorComparator
		{
			public:
				int compareElements (const ValueTree &first, const ValueTree &second)
				{
					return ( first.getProperty(Ids::name).toString().compare (second.getProperty(Ids::name).toString()) );
				}
		};

		CtrlrIDManager();
		~CtrlrIDManager();
		PropertyComponent *createComponentForProperty (	const Identifier &propertyName,
														const ValueTree &propertyElement,
														CtrlrPanel *panel=nullptr,
														StringArray *possibleChoices=nullptr,
														StringArray *possibleValues=nullptr);

		static const String typeToString (const PropertyType t);
		static const PropertyType stringToType (const String t);
		static Array <var> toValueList (const StringArray &in);
		StringArray getChoicesArray(const ValueTree &cid);
		StringArray getValuesArray(const ValueTree &cid);
		ValueTree &getObjectTree() { return (ctrlrIdTree); }

		const String getVendorForId (const MemoryBlock &vendorId);
		const String getVendorForId (const String &vendorId);
		ValueTree getVendorTree();
		JUCE_LEAK_DETECTOR(CtrlrIDManager);

	private:
		ValueTree ctrlrIdTree;
		ValueTree constantsTree;
		ValueTree vendorTree;
};
#endif
