#include "Globals/globals.h"
#include <iostream>

namespace Globals {
    namespace WorldToNormalized {
        float ConvertX(float pixelX, float screenWidth)
        {
            return (pixelX / (screenWidth * 0.5f));
        }
        float ConvertY(float pixelY, float screenHeight)
        {
            return (pixelY / (screenHeight * 0.5f));
        }
        float ConvertScaleX(float pixelWidth, float screenWidth)
        {
            return pixelWidth / (screenWidth * 0.5f);
        }
        float ConvertScaleY(float pixelHeight, float screenHeight)
        {
            return pixelHeight / (screenHeight * 0.5f);
        }
    }
}