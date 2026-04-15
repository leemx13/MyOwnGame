#pragma once

#define WINWIDTH										1600
#define WINHEIGHT										900

#define WIDTH_OF_WHOLE_SPRITESHEET						612.0f
#define HEIGHT_OF_WHOLE_SPRITESHEET						408.0f
#define ROW												2
#define COL												3
#define WIDTH_OF_ENTITY_IN_SPRITESHEET                  (WIDTH_OF_WHOLE_SPRITESHEET / (float)COL)
#define HEIGHT_OF_ENTITY_IN_SPRITESHEET                 (HEIGHT_OF_WHOLE_SPRITESHEET / (float)ROW)

namespace Globals {

	namespace WorldToNormalized
	{
		float ConvertY(float pixelY, float screenHeight);
		float ConvertX(float pixelX, float screenWidth);
		float ConvertScaleX(float pixelWidth, float screenWidth);
		float ConvertScaleY(float pixelHeight, float screenHeight);
	}
}