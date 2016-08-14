//
// Created by redknot on 8/14/16.
//

#ifndef OPENGLCPP_IMAGEDATA_H
#define OPENGLCPP_IMAGEDATA_H

#include <sys/types.h>
#include "png.h"

class ImageData {
public:
    int img_width, img_height;
    uint8_t* pixels;

    ImageData(png_byte* _pixels, int width, int height);
};



#endif //OPENGLCPP_IMAGEDATA_H
