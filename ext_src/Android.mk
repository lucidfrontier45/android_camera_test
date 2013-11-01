#NDK_TOOLCHAIN_VERSION=clang

# specify current directory
LOCAL_PATH := $(call my-dir)

# clear all the previous vars
include $(CLEAR_VARS)

# specify the module to build
LOCAL_MODULE    := test

# specify the source
LOCAL_SRC_FILES := ext_test.c

# specify the include files
LOCAL_C_INCLUDES :=

# specify the compile flags
LOCAL_CFLAGS := -O2

# specify the external libraries
LOCAL_STATIC_LIBRARIES :=


# build as shared library
#include $(BUILD_SHARED_LIBRARY)

# build as static library
include $(BUILD_STATIC_LIBRARY)
