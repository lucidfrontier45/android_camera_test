#NDK_TOOLCHAIN_VERSION=clang
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuild-extlib
LOCAL_SRC_FILES := ./lib/libtest.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := smartink-jni
LOCAL_SRC_FILES := smartink-jni.cpp
LOCAL_C_INCLUDES :=
LOCAL_LDLIBS := -llog -ldl
LOCAL_STATIC_LIBRARIES := prebuild-extlib
include $(BUILD_SHARED_LIBRARY)
