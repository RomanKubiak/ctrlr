#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "LGlobalFunctions.h"
#include "LAffineTransform.h"
#include "LAudioFile.h"
#include "LAudioFormat.h"
#include "LAudioSampleBuffer.h"
#include "LBigInteger.h"
#include "LColourGradient.h"
#include "LColour.h"
#include "LComponent.h"
#include "LFile.h"
#include "LGraphics.h"
#include "LImage.h"
#include "LJustification.h"
#include "LLine.h"
#include "LMemoryBlock.h"
#include "LMidiMessage.h"
#include "LModifierKeys.h"
#include "LMouseEvent.h"
#include "LPath.h"
#include "LPoint.h"
#include "LPopupMenu.h"
#include "LRandom.h"
#include "LRectangle.h"
#include "LResult.h"
#include "LString.h"
#include "LTime.h"
#include "LURL.h"
#include "LValue.h"
#include "LValueTree.h"
#include "LLookAndFeel.h"
#include "LLabel.h"
#include "LSlider.h"
#include "LTimer.h"
#include "LFont.h"
#include "LBubbleMessageComponent.h"
#include "LAttributedString.h"
#include "LRange.h"
#include "LComponentPeer.h"
#include "LGlyphArrangement.h"
#include "LZipFile.h"
#include "LMemoryInputStream.h"
#include "LInputStream.h"
#include "LDrawable.h"
#include "LRelativeCoordinate.h"
#include "LExpression.h"
#include "LSparseSet.h"
#include "LAlertWindow.h"
#include "LComboBox.h"
#include "LTextEditor.h"
#include "LKeyPress.h"
#include "LThread.h"
#include "LThreadWithProgressWindow.h"

void CtrlrLuaManager::wrapJuceCoreClasses(lua_State *L)
{
	LGlobalFunctions::wrapForLua(L);
	LBigInteger::wrapForLua(L);
	LFile::wrapForLua(L);
	LMemoryBlock::wrapForLua(L);
	LMidiMessage::wrapForLua(L);
	LString::wrapForLua(L);
	LResult::wrapForLua(L);
	LTime::wrapForLua(L);
	LURL::wrapForLua(L);
	LValue::wrapForLua(L);
	LTimer::wrapForLua(L);
	LFont::wrapForLua(L);
	LZipFile::wrapForLua(L);
	LMemoryInputStream::wrapForLua(L);
	LInputStream::wrapForLua(L);
	LRange::wrapForLua(L);
	LSparseSet::wrapForLua(L);
	LAudioFile::wrapForLua(L);
	LAudioFormat::wrapForLua(L);
	LAudioSampleBuffer::wrapForLua(L);
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
	LPath::wrapForLua(L);
	LPoint::wrapForLua(L);
	LPopupMenu::wrapForLua(L);
	LRandom::wrapForLua(L);
	LRectangle::wrapForLua(L);
	LValueTree::wrapForLua(L);
	LLookAndFeel::wrapForLua(L);
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
