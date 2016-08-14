//
// Created by redknot on 8/13/16.
//

#ifndef OPENGLCPP_READPNG_H
#define OPENGLCPP_READPNG_H

#include "ImageData.h"
#include <string>
#include <android/asset_manager.h>
#include "png.h"
#include "../LOG/logger.h"

using namespace std;

class ReadPNG {
private:

public:
    ImageData* FromAssetPNGFile(AAssetManager* mgr, const string& fname);

};



#endif //OPENGLCPP_READPNG_H
