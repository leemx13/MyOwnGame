#pragma once

#define WINWIDTH										1600
#define WINHEIGHT										900

namespace Globals {

	namespace WorldToNormalized
	{
		float ConvertY(float pixelY, float screenHeight);
		float ConvertX(float pixelX, float screenWidth);
		float ConvertScaleX(float pixelWidth, float screenWidth);
		float ConvertScaleY(float pixelHeight, float screenHeight);
	}
}