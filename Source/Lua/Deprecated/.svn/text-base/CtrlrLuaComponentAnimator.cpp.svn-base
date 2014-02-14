#include "stdafx.h"
#include "CtrlrLuaComponentAnimator.h"

CtrlrLuaComponentAnimator::CtrlrLuaComponentAnimator()
{
}

CtrlrLuaComponentAnimator::~CtrlrLuaComponentAnimator()
{
}

void CtrlrLuaComponentAnimator::animateComponent (CtrlrComponent *component, CtrlrLuaRectangle &finalBounds, float finalAlpha, int animationDurationMilliseconds, bool useProxyComponent, double startSpeed, double endSpeed)
{
	animator.animateComponent (component, finalBounds, finalAlpha, animationDurationMilliseconds, useProxyComponent, startSpeed, endSpeed);
}

void CtrlrLuaComponentAnimator::fadeOut (CtrlrComponent *component, int millisecondsToTake)
{
	animator.fadeOut (component, millisecondsToTake);
}

void CtrlrLuaComponentAnimator::fadeIn (CtrlrComponent *component, int millisecondsToTake)
{
	animator.fadeIn (component, millisecondsToTake);
}

void CtrlrLuaComponentAnimator::cancelAnimation (CtrlrComponent *component, bool moveComponentToItsFinalPosition)
{
	animator.cancelAnimation (component, moveComponentToItsFinalPosition);
}

void CtrlrLuaComponentAnimator::cancelAllAnimations (bool moveComponentsToTheirFinalPositions)
{
	animator.cancelAllAnimations (moveComponentsToTheirFinalPositions);
}

const Rectangle<int> CtrlrLuaComponentAnimator::getComponentDestination (CtrlrComponent *component)
{
	return (animator.getComponentDestination(component));
}

bool CtrlrLuaComponentAnimator::isAnimating (CtrlrComponent *component)
{
	return (animator.isAnimating(component));
}

void CtrlrLuaComponentAnimator::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<CtrlrLuaComponentAnimator>("CtrlrLuaComponentAnimator")
			.def(constructor<>())
			.def("animateComponent", &CtrlrLuaComponentAnimator::animateComponent)
			.def("fadeOut", &CtrlrLuaComponentAnimator::fadeOut)
			.def("fadeIn", &CtrlrLuaComponentAnimator::fadeIn)
			.def("cancelAnimation", &CtrlrLuaComponentAnimator::cancelAnimation)
			.def("cancelAllAnimations", &CtrlrLuaComponentAnimator::cancelAllAnimations)
			.def("getComponentDestination", &CtrlrLuaComponentAnimator::getComponentDestination)
			.def("isAnimating", &CtrlrLuaComponentAnimator::isAnimating)
	];
}