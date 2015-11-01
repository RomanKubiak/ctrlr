#ifndef __CTRLR_LUA_COMPONENT_ANIMATOR__
#define __CTRLR_LUA_COMPONENT_ANIMATOR__
#ifdef _WIN32
#pragma warning(disable:4100)
#endif
#include "CtrlrLuaRectangle.h"
#include "CtrlrLuaMemoryBlock.h"
#include "CtrlrComponents/CtrlrComponent.h"

//==============================================================================
/** @brief A class that animates a component see http://www.rawmaterialsoftware.com/juce/api/classComponentAnimator.html for details
 *
 */
class CtrlrLuaComponentAnimator
{
	public:
		CtrlrLuaComponentAnimator();
		~CtrlrLuaComponentAnimator();
		void animateComponent (CtrlrComponent *component, CtrlrLuaRectangle &finalBounds, float finalAlpha, int animationDurationMilliseconds, bool useProxyComponent, double startSpeed, double endSpeed);
		void fadeOut (CtrlrComponent *component, int millisecondsToTake);
		void fadeIn (CtrlrComponent *component, int millisecondsToTake);
		void cancelAnimation (CtrlrComponent *component, bool moveComponentToItsFinalPosition);
		void cancelAllAnimations (bool moveComponentsToTheirFinalPositions);
		const juce::Rectangle<int> getComponentDestination (CtrlrComponent *component);
		bool isAnimating (CtrlrComponent *component);

		static void wrapForLua (lua_State *L);

		JUCE_LEAK_DETECTOR(CtrlrLuaComponentAnimator)

	private:
		ComponentAnimator animator;
};

#endif
