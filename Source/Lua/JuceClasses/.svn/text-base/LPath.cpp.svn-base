#include "stdafx.h"
#include "LPath.h"

void LPath::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Path>("Path")
			.def(constructor<>())
			.def(constructor<const Path &>())
			.def("isEmpty", &Path::isEmpty)
			.def("getBounds", &Path::getBounds)
			.def("getBoundsTransformed", &Path::getBoundsTransformed)
			.def("contains", (bool (Path::*)(float, float, float) const) &Path::contains)
			.def("contains", (bool (Path::*)(const Point<float>, float) const) &Path::contains)
			.def("intersectsLine", &Path::intersectsLine)
			.def("getClippedLine", &Path::getClippedLine)
			.def("getLength", &Path::getLength)
			.def("getPointAlongPath", &Path::getPointAlongPath)
			.def("getNearestPoint", &Path::getNearestPoint)
			.def("clear", &Path::clear)
			.def("startNewSubPath", (void (Path::*)(float, float)) &Path::startNewSubPath)
			.def("startNewSubPath", (void (Path::*)(const Point<float>)) &Path::startNewSubPath)
			.def("closeSubPath", &Path::closeSubPath)
			.def("lineTo", (void (Path::*)(float, float)) &Path::lineTo)
			.def("lineTo", (void (Path::*)(const Point<float>)) &Path::lineTo)
			.def("quadraticTo", (void (Path::*)(float, float, float, float)) &Path::quadraticTo)
			.def("quadraticTo", (void (Path::*)(const Point<float>, const Point<float>)) &Path::quadraticTo)
			.def("cubicTo", (void (Path::*)(float, float, float, float, float, float)) &Path::cubicTo)
			.def("cubicTo", (void (Path::*)(const Point<float>, const Point<float>, const Point<float>)) &Path::cubicTo)
			.def("getCurrentPosition", &Path::getCurrentPosition)
			.def("addRectangle", (void (Path::*)(float, float, float, float)) &Path::addRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float)) &Path::addRoundedRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float, float)) &Path::addRoundedRectangle)
			.def("addRoundedRectangle", (void (Path::*)(float, float, float, float, float, float, bool, bool, bool, bool)) &Path::addRoundedRectangle)
			.def("addTriangle", &Path::addTriangle)
			.def("addQuadrilateral", &Path::addQuadrilateral)
			.def("addEllipse", &Path::addEllipse)
			.def("addArc", &Path::addArc)
			.def("addCentredArc", &Path::addCentredArc)
			.def("addPieSegment", &Path::addPieSegment)
			.def("addLineSegment", &Path::addLineSegment)
			.def("addArrow", &Path::addArrow)
			.def("addPolygon", &Path::addPolygon)
			.def("addStar", &Path::addStar)
			.def("addBubble", &Path::addBubble)
			.def("addPath", &Path::addQuadrilateral)
			.def("addPath", &Path::addQuadrilateral)
			.def("swapWithPath", &Path::swapWithPath)
			.def("applyTransform", &Path::applyTransform)
			.def("scaleToFit", &Path::scaleToFit)
			.def("getTransformToScaleToFit", (AffineTransform (Path::*)(float, float, float, float, bool, Justification) const)&Path::getTransformToScaleToFit)
			.def("getTransformToScaleToFit", (AffineTransform (Path::*)(const Rectangle<float> &, bool, Justification) const)&Path::getTransformToScaleToFit)
			.def("createPathWithRoundedCorners", &Path::createPathWithRoundedCorners)
			.def("setUsingNonZeroWinding", &Path::setUsingNonZeroWinding)
			.def("isUsingNonZeroWinding", &Path::isUsingNonZeroWinding)
			.def("loadPathFromStream", &Path::loadPathFromStream)
			.def("loadPathFromData", &Path::loadPathFromData)
			.def("writePathToStream", &Path::writePathToStream)
			.def("toString", &Path::toString)
			.def("restoreFromString", &Path::restoreFromString)
		,
		
		class_<PathStrokeType>("PathStrokeType")
			.def(constructor<float, PathStrokeType::JointStyle, PathStrokeType::EndCapStyle>())
			.def(constructor<const PathStrokeType &>())
			.def("createDashedStroke", &PathStrokeType::createDashedStroke)
			.def("createDashedStroke", &PathStrokeType::createDashedStroke)
			.def("createStrokeWithArrowheads", &PathStrokeType::createStrokeWithArrowheads)
			.def("getStrokeThickness", &PathStrokeType::getStrokeThickness)
			.def("setStrokeThickness", &PathStrokeType::setStrokeThickness)
			.def("getJointStyle", &PathStrokeType::getJointStyle)
			.def("setJointStyle", &PathStrokeType::setJointStyle)
			.def("getEndStyle", &PathStrokeType::getEndStyle)
			.def("setEndStyle", &PathStrokeType::setEndStyle)
			.enum_("JoinStyle")
			[
				value("mitered", PathStrokeType::mitered),
				value("curved", PathStrokeType::curved),
				value("beveled", PathStrokeType::beveled)
			]
			.enum_("EndCapStyle")
			[
				value("butt", PathStrokeType::butt),
				value("square", PathStrokeType::square),
				value("rounded", PathStrokeType::rounded)
			]
	];
}