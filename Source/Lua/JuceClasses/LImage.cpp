#include "stdafx.h"
#include "LImage.h"

void LImage::wrapForLua (lua_State *L)
{
	using namespace luabind;

	module(L)
    [
		class_<Image>("Image")
			.def(constructor<const Image &>())
			.def(constructor<>())
			.def("isValid", &Image::isValid)
			.def("isNull", &Image::isNull)
			.def("getWidth", &Image::getWidth)
			.def("getHeight", &Image::getHeight)
			.def("isRGB", &Image::isRGB)
			.def("isARGB", &Image::isARGB)
			.def("isSingleChannel", &Image::isSingleChannel)
			.def("hasAlphaChannel", &Image::hasAlphaChannel)
			.def("rescaled", &Image::rescaled)
			.def("duplicateIfShared", &Image::duplicateIfShared)
			.def("getPixelAt", &Image::getPixelAt)
			.def("setPixelAt", &Image::setPixelAt)
			.def("multiplyAlphaAt", &Image::multiplyAlphaAt)
			.def("multiplyAllAlphas", &Image::multiplyAllAlphas)
			.def("desaturate", &Image::desaturate)
			.def("moveImageSection", &Image::moveImageSection)
			.def("getReferenceCount", &Image::getReferenceCount)
			.enum_("PixelFormat")
			[
				value("UnknownFormat", Image::UnknownFormat),
				value("RGB", Image::RGB),
				value("ARGB", Image::ARGB),
				value("SingleChannel", Image::SingleChannel)
			]
			.enum_("ImageType")
			[
				value("SoftwareImage ", 0),
				value("NativeImage ", 1)
			]
		,
		class_<ImageFileFormat>("ImageFileFormat")
			.def("getFormatName", &ImageFileFormat::getFormatName)
			.def("canUnderstand", &ImageFileFormat::canUnderstand)
			.def("loadFrom", (Image (*)(const File &)) &ImageFileFormat::loadFrom)
	];
}