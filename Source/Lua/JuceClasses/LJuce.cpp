#include "stdafx_luabind.h"
#include "LJuce.h"
#include "CtrlrLuaManager.h"

void CtrlrLuaManager::wrapJuceCoreClasses(lua_State *L)
{
	LBigInteger::wrapForLua(L);
	LXmlElement::wrapForLua(L);
	LFile::wrapForLua(L);
	LMemoryBlock::wrapForLua(L);
	LMidiMessage::wrapForLua(L);
	LMidiBuffer::wrapForLua(L);
	LString::wrapForLua(L);
	LResult::wrapForLua(L);
	LTime::wrapForLua(L);
	LURL::wrapForLua(L);
	LValue::wrapForLua(L);
	LTimer::wrapForLua(L);
	LTypeface::wrapForLua(L);
	LFont::wrapForLua(L);
	LZipFile::wrapForLua(L);
	LMemoryInputStream::wrapForLua(L);
	LInputStream::wrapForLua(L);
	LRange::wrapForLua(L);
	LSparseSet::wrapForLua(L);
	LAudioFile::wrapForLua(L);
	LAudioFormat::wrapForLua(L);
	LAudioSampleBuffer::wrapForLua(L);
	LBorderSize::wrapForLua(L);
}

void CtrlrLuaManager::wrapJuceClasses(lua_State *L)
{
	wrapJuceCoreClasses(L);

	LAffineTransform::wrapForLua(L);
	LColourGradient::wrapForLua(L);
	LColour::wrapForLua(L);
	LComponent::wrapForLua(L);
	LGraphics::wrapForLua(L);
	LImage::wrapForLua(L);
	LJustification::wrapForLua(L);
	LLine::wrapForLua(L);
	LModifierKeys::wrapForLua(L);
	LMouseEvent::wrapForLua(L);
	LMouseCursor::wrapForLua(L);
	LPath::wrapForLua(L);
	LPoint::wrapForLua(L);
	LButton::wrapForLua(L);
	LTextButton::wrapForLua(L);
	LToggleButton::wrapForLua(L);
	LPopupMenu::wrapForLua(L);
	LRandom::wrapForLua(L);
	LRectangle::wrapForLua(L);
	LValueTree::wrapForLua(L);
	LookAndFeelBase::wrapForLua(L);
	LLabel::wrapForLua(L);
	LSlider::wrapForLua(L);
	LBubbleMessageComponent::wrapForLua(L);
	LAttributedString::wrapForLua(L);
	LComponentPeer::wrapForLua(L);
	LGlyphArrangement::wrapForLua(L);
	LDrawable::wrapForLua(L);
	LRelativeCoordinate::wrapForLua(L);
	LAlertWindow::wrapForLua(L);
	LComboBox::wrapForLua(L);
	LTextEditor::wrapForLua(L);
	LKeyPress::wrapForLua(L);
	LThread::wrapForLua(L);
	LThreadWithProgressWindow::wrapForLua(L);
}
