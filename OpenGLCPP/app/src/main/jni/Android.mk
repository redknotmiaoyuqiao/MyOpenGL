LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := opengldraw

LOCAL_STATIC_LIBRARIES := png
LOCAL_C_INCLUDES += $(LOCAL_PATH)/PNG

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv3 -lz
LOCAL_CFLAGS := -std=c++11

LOCAL_SRC_FILES += com_redknot_tool_NativeMethod.cpp
LOCAL_SRC_FILES += MYGL/ShaderProgram.cpp
LOCAL_SRC_FILES += MYGL/ShaderManager.cpp
LOCAL_SRC_FILES += MYGL/Vector3f.cpp
LOCAL_SRC_FILES += MYGL/Matrix4f.cpp
LOCAL_SRC_FILES += MYGL/Pipeline.cpp
LOCAL_SRC_FILES += MYGL/Texture.cpp
LOCAL_SRC_FILES += FILE/ReadFile.cpp
LOCAL_SRC_FILES += FILE/ReadPNG.cpp
LOCAL_SRC_FILES += FILE/ImageData.cpp

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/PNG/Android.mk