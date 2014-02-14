#include "stdafx.h"
#include "LDrawable.h"

void LDrawable::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Drawable>("Drawable")
			.def("createCopy", &Drawable::createCopy)
			.def("draw", &Drawable::draw)
			.def("drawAt", &Drawable::drawAt)
			.def("drawWithin", &Drawable::drawWithin)
			.def("setOriginWithOriginalSize", &Drawable::setOriginWithOriginalSize)
			.def("setTransformToFit", &Drawable::setTransformToFit)
			.def("getParent", &Drawable::getParent)
			.def("createFromImageFile", &Drawable::createFromValueTree)
			.def("getDrawableBounds", &Drawable::getDrawableBounds)
			.scope
			[
				def("createFromImageData", &Drawable::createFromImageData, adopt(result)),
				def("createFromImageDataStream", &Drawable::createFromImageDataStream, adopt(result)),
				def("createFromImageFile", &Drawable::createFromImageFile, adopt(result)),
				def("createFromSVG", &Drawable::createFromSVG, adopt(result)),
				def("createFromValueTree", &Drawable::createFromValueTree, adopt(result)),
				def("toDrawableComposite", &LDrawable::toDrawableComposite)
			]
		,
		class_<DrawableComposite, bases<Drawable> >("DrawableComposite")
			.def(constructor<>())
			.def(constructor<const DrawableComposite &>())
			.def("setBoundingBox", &DrawableComposite::setBoundingBox)
			.def("getBoundingBox", &DrawableComposite::getBoundingBox)
			.def("resetBoundingBoxToContentArea", &DrawableComposite::resetBoundingBoxToContentArea)
			.def("getContentArea", &DrawableComposite::getContentArea)
			.def("setContentArea", &DrawableComposite::setContentArea)
			.def("resetContentAreaAndBoundingBoxToFitChildren", &DrawableComposite::resetContentAreaAndBoundingBoxToFitChildren)
			.def("createCopy", &DrawableComposite::createCopy)
			.def("refreshFromValueTree", &DrawableComposite::refreshFromValueTree)
			.def("createValueTree", &DrawableComposite::createValueTree)
			.def("getDrawableBounds", &DrawableComposite::getDrawableBounds)
			.def("getMarkers", &DrawableComposite::getMarkers)
	];
}