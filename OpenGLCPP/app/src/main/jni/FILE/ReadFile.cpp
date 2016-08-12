//
// Created by redknot on 8/12/16.
//

#include "ReadFile.h"

using namespace std;

ReadFile::ReadFile(AAssetManager *_pAssetManager)
{
    pAssetManager = _pAssetManager;
}

char* ReadFile::readShaderSrcFile(char *shaderFile)
{
    AAsset *pAsset = NULL;
    char *pBuffer = NULL;
    off_t size = -1;
    int numByte = -1;

    if (NULL == pAssetManager)
    {
        LOG_ERROR("pAssetManager is null!");
        return NULL;
    }
    pAsset = AAssetManager_open(pAssetManager, shaderFile, AASSET_MODE_UNKNOWN);

    size = AAsset_getLength(pAsset);
    pBuffer = (char *)malloc(size+1);
    pBuffer[size] = '\0';

    numByte = AAsset_read(pAsset, pBuffer, size);
    LOG_ERROR("%s : [%s]", shaderFile, pBuffer);
    AAsset_close(pAsset);

    return pBuffer;
}