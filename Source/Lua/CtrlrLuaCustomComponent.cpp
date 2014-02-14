#include "stdafx.h"
#include "CtrlrLuaManager.h"
#include "CtrlrLog.h"
#include "CtrlrComponents/CtrlrCustomComponent.h"

/** @brief Get bounds of the component 

	@return	a CtrlrLuaRectangle object that describes the components bounds
*/
CtrlrLuaRectangle CtrlrComponent::getLuaBounds()
{
	return (getBounds());
}

/** @brief Set bounds of the component

	@param	newBounds	a CtrlrLuaRectangle object that describes the new component bounds
*/
void CtrlrComponent::setLuaBounds(CtrlrLuaRectangle newBounds)
{
	setBounds (newBounds);
}

void CtrlrCustomComponent::wrapForLua(lua_State *L)
{
	using namespace luabind;
	module(L)
	[
		class_<CtrlrCustomComponent,CtrlrComponent>("CtrlrCustomComponent")
	];
}