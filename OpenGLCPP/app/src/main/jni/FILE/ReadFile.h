//
// Created by redknot on 8/12/16.
//

#ifndef OPENGLCPP_READFILE_H
#define OPENGLCPP_READFILE_H

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "LOG/logger.h"

using namespace std;

class ReadFile {
private:
    AAssetManager *pAssetManager;
public:
    char* readShaderSrcFile(char *shaderFile);
    ReadFile(AAssetManager *_pAssetManager);
};



#endif //OPENGLCPP_READFILE_H
