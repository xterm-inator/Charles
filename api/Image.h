#pragma once

#include <vector_types.h>
#include <opencv2/core/mat.hpp>

struct Dimensions {
    unsigned int Height;
    unsigned int Width;
};

class Image
{
public:
    Image();
    cv::Mat RawImage{};

private:
    Dimensions ImageDimensions{};

public:
    inline void SetDimensions(unsigned int Height, unsigned int Width) { ImageDimensions.Height = Height; ImageDimensions.Width = Width; }
    [[nodiscard]] inline unsigned int GetHeight() const { return ImageDimensions.Height; }
    [[nodiscard]] inline unsigned int GetWidth() const { return ImageDimensions.Width; }
};
