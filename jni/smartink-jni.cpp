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


void ImageRotation_YUV2BMP(jint* rgb, jbyte* yuv, int w, int h, int rad_y)
{

    int             sz;
    int             i;
    int             j;
    int             Y;
    int             Cr = 0;
    int             Cb = 0;
    int             yuvPtr = 0;
    int             jDiv2 = 0;

    int             R = 0;
    int             G = 0;
    int             B = 0;
    int             cOff;

    sz = w * h;

	int 			x, y;
	int 			rgbPtr = 0;

	//rad_y = 150;
	//Rotation degree = 90;
    if ((rad_y > -45 && rad_y <= 0) || (rad_y > 0 && rad_y <= 45)) {

    	yuvPtr = 0;
        for(j = 0, x = h - 1; j < h; j++, x--) {
			jDiv2 = j >> 1;
		//	jDiv2w = jDiv2 * w;

			rgbPtr = 0;
			for(i = 0, y = 0; i < w; i++, y++) {

			//	rgbPtr = y * h;
				 Y = yuv[yuvPtr+i];
				 if(Y < 0) Y += 255;
				 if((i & 0x1) != 1) {
					 cOff = sz + jDiv2 * w + (i >> 1) * 2;
				//	 cOff = sz + jDiv2w + (i >> 1) * 2;

					 Cb = yuv[cOff + 1];
					 if(Cb < 0) Cb += 127; else Cb -= 128;
					 Cr = yuv[cOff];
					 if(Cr < 0) Cr += 127; else Cr -= 128;
				 }
				 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);
				 if(R < 0) R = 0; else if(R > 255) R = 255;
				 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
				 if(G < 0) G = 0; else if(G > 255) G = 255;
				 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
				 if(B < 0) B = 0; else if(B > 255) B = 255;

				 rgb[rgbPtr + x] = 0xff000000 + (R << 16) + (G << 8) + B;
				 rgbPtr += h;
			}
			yuvPtr += w;
        }

    }
    //Rotation degree = 180;
    else if (rad_y > 45 && rad_y <= 135) {

    	yuvPtr = 0;
    	rgbPtr = (h - 1)*w;
        for(j = 0, y = h - 1; j < h; j++, y--) {
			jDiv2 = j >> 1;
		//	jDiv2w = jDiv2 * w;

			for(i = 0, x = w - 1; i < w; i++, x--) {
				 Y = yuv[yuvPtr + i];
				 if(Y < 0) Y += 255;
				 if((i & 0x1) != 1) {
						 cOff = sz + jDiv2 * w + (i >> 1) * 2;
						 Cb = yuv[cOff + 1];
						 if(Cb < 0) Cb += 127; else Cb -= 128;
						 Cr = yuv[cOff];
						 if(Cr < 0) Cr += 127; else Cr -= 128;
				 }
				 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);//1.406*~1.403
				 if(R < 0) R = 0; else if(R > 255) R = 255;
				 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);//
				 if(G < 0) G = 0; else if(G > 255) G = 255;
				 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);//1.765~1.770
				 if(B < 0) B = 0; else if(B > 255) B = 255;

				 rgb[rgbPtr + x] = 0xff000000 + (R << 16) + (G << 8) + B;
			}
			yuvPtr += w;
			rgbPtr -= w;
        }
    }
    //Rotation degree = -90;
    else if ((rad_y > 135 && rad_y <= 180) || (rad_y >= -180 && rad_y <= -135)) {

    	yuvPtr = 0;
        for(j = 0, x = 0; j < h; j++, x++) {
			jDiv2 = j >> 1;
		//	jDiv2w = jDiv2 * w;

			rgbPtr = (w - 1)*h;
			for(i = 0, y = w - 1; i < w; i++, y--) {
				 Y = yuv[yuvPtr + i];
				 if(Y < 0) Y += 255;
				 if((i & 0x1) != 1) {
					 cOff = sz + jDiv2 * w + (i >> 1) * 2;
				//	 cOff = sz + jDiv2w + (i >> 1) * 2;

					 Cb = yuv[cOff + 1];
					 if(Cb < 0) Cb += 127; else Cb -= 128;
					 Cr = yuv[cOff];
					 if(Cr < 0) Cr += 127; else Cr -= 128;
				 }
				 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);
				 if(R < 0) R = 0; else if(R > 255) R = 255;
				 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
				 if(G < 0) G = 0; else if(G > 255) G = 255;
				 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
				 if(B < 0) B = 0; else if(B > 255) B = 255;

				 rgb[rgbPtr + x] = 0xff000000 + (R << 16) + (G << 8) + B;
				 rgbPtr -= h;
			}
			yuvPtr += w;
        }
    }
	//Rotation degree = 0;
	else if (rad_y > -135 && rad_y <= -45){

		yuvPtr = 0;
		for(j = 0; j < h; j++) {
			 //yuvPtr = j * w;
			 jDiv2 = j >> 1;
			 for(i = 0; i < w; i++) {
					 Y = yuv[yuvPtr + i];
										 if(Y < 0) Y += 255;
					 if((i & 0x1) != 1) {
							 cOff = sz + jDiv2 * w + (i >> 1) * 2;
							 Cb = yuv[cOff];
							 if(Cb < 0) Cb += 127; else Cb -= 128;
							 Cr = yuv[cOff + 1];
							 if(Cr < 0) Cr += 127; else Cr -= 128;
					 }
					 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);//1.406*~1.403
					 if(R < 0) R = 0; else if(R > 255) R = 255;
					 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);//
					 if(G < 0) G = 0; else if(G > 255) G = 255;
					 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);//1.765~1.770
					 if(B < 0) B = 0; else if(B > 255) B = 255;
					 rgb[yuvPtr + i] = 0xff000000 + (B << 16) + (G << 8) + R;
			 }
			 yuvPtr += w;
		}

    }
}

extern "C" {

	JNIEXPORT jint JNICALL Java_com_example_cameratest_JNIMethods_startink(
		JNIEnv * env, jobject obj, jintArray rgbOut, jbyteArray yuv420sp, jint width, jint height, jint rad){

	    int             sz;
	    int             i;
	    int             j;
	    int             Y;
	    int             Cr = 0;
	    int             Cb = 0;
	    int             pixPtr = 0;
	    int             jDiv2 = 0;
	    int             R = 0;
	    int             G = 0;
	    int             B = 0;
	    int             cOff;
	    int w = width;
	    int h = height;
	    sz = w * h;

	    LOGD("rad = %d", rad);

		jint len = env->GetArrayLength(yuv420sp);
		jbyte* yuv = (jbyte*)env->GetPrimitiveArrayCritical(yuv420sp, 0);
		jint *rgbData = (jint*)env->GetPrimitiveArrayCritical(rgbOut, 0);


	//	ImageRotationYUV(yuv, width, height, len, rad);
		ImageRotation_YUV2BMP(rgbData, yuv, width, height, rad);

	    env->ReleasePrimitiveArrayCritical(rgbOut, rgbData, 0);
		env->ReleasePrimitiveArrayCritical(yuv420sp, yuv, 0);
		return 0;
	}
}


