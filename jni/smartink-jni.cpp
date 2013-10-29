#include "smartink-jni.h"
#include <stdlib.h>

static int counter = 0;

JNIEXPORT jint JNICALL Java_com_example_cameratest_JNIMethods_startink(JNIEnv *,
		jclass, jbyteArray) {
	int ret = 0;

	if (counter == 100){
		counter = 0;
		return 1;
	}

	counter ++;

	return ret;
}
