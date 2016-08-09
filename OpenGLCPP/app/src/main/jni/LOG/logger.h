//
// Created by redknot on 8/9/16.
//

#ifndef OPENGLCPP_LOGGER_H
#define OPENGLCPP_LOGGER_H

#include <string.h>
#include <android/log.h>

#define LOG_TAG "opengl"

#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

#endif //OPENGLCPP_LOGGER_H
