//
// Created by redknot on 8/14/16.
//

#include "ImageData.h"


ImageData::ImageData(png_byte* _pixels, int width, int height)
{
    img_width = width;
    img_height = height;

    pixels = _pixels;
}