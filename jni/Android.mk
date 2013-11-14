#NDK_TOOLCHAIN_VERSION=clang
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := smartink-jni
LOCAL_SRC_FILES := smartink-jni.cpp
LOCAL_C_INCLUDES :=
LOCAL_LDLIBS := -llog -ldl
include $(BUILD_SHARED_LIBRARY)
