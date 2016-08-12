LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := opengldraw
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3
LOCAL_CFLAGS    := -std=c++11

LOCAL_SRC_FILES += com_redknot_tool_NativeMethod.cpp
LOCAL_SRC_FILES += MYGL/ShaderManager.cpp
LOCAL_SRC_FILES += MYGL/Vector3f.cpp
LOCAL_SRC_FILES += MYGL/Matrix4f.cpp
LOCAL_SRC_FILES += MYGL/Pipeline.cpp
LOCAL_SRC_FILES += FILE/ReadFile.cpp


include $(BUILD_SHARED_LIBRARY)