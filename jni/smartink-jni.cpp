#include "smartink-jni.h"
#include <stdlib.h>

#include <android/log.h>
#define LOGD(...) (__android_log_print(ANDROID_LOG_DEBUG, __FILE__, "%s L%u @%s:",__FILE__,__LINE__,__func__), \
             __android_log_print(ANDROID_LOG_DEBUG, __FILE__, ""__VA_ARGS__))
#define LOGI(...) (__android_log_print(ANDROID_LOG_INFO, __FILE__, "%s L%u @%s:",__FILE__,__LINE__,__func__), \
             __android_log_print(ANDROID_LOG_INFO, __FILE__, ""__VA_ARGS__))
#define LOGW(...) (__android_log_print(ANDROID_LOG_WARN, __FILE__, "%s L%u @%s:",__FILE__,__LINE__,__func__), \
             __android_log_print(ANDROID_LOG_WARN, __FILE__, ""__VA_ARGS__))
#define LOGE(...) (__android_log_print(ANDROID_LOG_ERROR, __FILE__, "%s L%u @%s:",__FILE__,__LINE__,__func__), \
             __android_log_print(ANDROID_LOG_ERROR, __FILE__, ""__VA_ARGS__))

extern "C" {
    int stab_ext(const char *imag, int width, int height);
}

static int counter = 0;

JNIEXPORT jint JNICALL Java_com_example_cameratest_JNIMethods_startink(JNIEnv *,
		jclass, jbyteArray) {
	int ret = 0;

	ret = stab_ext(NULL, 0, 0);

    LOGD("stab_ext ret = %d", ret);


	if (counter == 100){
		counter = 0;
		return 1;
	}

	counter ++;

	return 0;
}
