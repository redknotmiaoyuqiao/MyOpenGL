LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := opengldraw
LOCAL_LDLIBS := -llog -lGLESv2 -landroid
LOCAL_CFLAGS    := -std=c++11
LOCAL_SRC_FILES := com_redknot_tool_NativeMethod.cpp MYGL/ShaderManager.cpp MYGL/Vector3f.cpp FILE/ReadFile.cpp

include $(BUILD_SHARED_LIBRARY)