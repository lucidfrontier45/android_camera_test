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


void ImageRotationYUV(jbyte* yuv, int w, int h, int size, int rad_y)
{

	int i, j;
	int x, y;
	int pixPtr;
	int rotPtr;

	int jDiv2;
	int jDiv2w;

	int iDiv2;
	int yDiv2;
	int yDiv2w;

	int xDiv2;
	int xDiv22;

	int cOff;
	int cOffRot;
	//Rotation degree = 0;
	if (rad_y > -135 && rad_y <= -45)
		return;

	jbyte*  yuv_rot = (jbyte*)malloc(size);

	//Rotation degree = 90;
    if ((rad_y > -45 && rad_y <= 0) || (rad_y > 0 && rad_y <= 45)) {

    	pixPtr = 0;
		for(j = 0, x = h - 1; j < h; j++, x--) {

			 jDiv2 = j >> 1;
			 jDiv2w = jDiv2 * w;

			 xDiv2 = x >> 1;
			 xDiv22 = xDiv2 << 1;

			 rotPtr = 0;
			 for(i = 0, y = 0; i < w; i++, y++) {

				 	 iDiv2 = i >> 1;
				 	 yDiv2 = y >> 1;
				 	 //Y = yuv[pixPtr + i];
				 	 yuv_rot[rotPtr + x] = yuv[pixPtr + i];

					 if((i & 0x1) != 1) {
							 cOff = size + jDiv2w + (iDiv2 << 1);
							 cOffRot = size + yDiv2 * h + xDiv22;
							 //Cb = yuv[cOff];
							 yuv_rot[cOffRot] = yuv[cOff];

							 //Cr = yuv[cOff + 1];
							 yuv_rot[cOffRot + 1] = yuv[cOff + 1];
					 }

					 rotPtr += h;
			 }
			 pixPtr += w;
		}
    }
    //Rotation degree = 180;
    else if (rad_y > 45 && rad_y <= 135) {

    	pixPtr = 0;
    	rotPtr = (h-1)*w;
		for(j = 0, y = h - 1; j < h; j++, y--) {

			 jDiv2 = j >> 1;
			 jDiv2w = jDiv2 * w;

			 yDiv2 = y >> 1;
			 yDiv2w = yDiv2 * w;

			 for(i = 0, x = w - 1; i < w; i++, x--) {

				 	 iDiv2 = i >> 1;
				 	 xDiv2 = x >> 1;
				 	 //Y = yuv[pixPtr + i];
				 	 yuv_rot[rotPtr + x] = yuv[pixPtr + i];

					 if((i & 0x1) != 1) {
							 cOff = size + jDiv2w + (iDiv2 << 1);
							 cOffRot = size + yDiv2w + (xDiv2 << 1);
							 //Cb = yuv[cOff];
							 yuv_rot[cOffRot] = yuv[cOff];

							 //Cr = yuv[cOff + 1];
							 yuv_rot[cOffRot + 1] = yuv[cOff + 1];
					 }

			 }
			 pixPtr += w;
			 rotPtr -= w;
		}
    }
    //Rotation degree = -90;
    else if ((rad_y > 135 && rad_y <= 180) || (rad_y >= -180 && rad_y <= -135)) {

    	pixPtr = 0;
		for(j = 0, x = 0; j < h; j++, x++) {

			 jDiv2 = j >> 1;
			 jDiv2w = jDiv2*w;

			 xDiv2 = x >> 1;
			 xDiv22 = xDiv2 << 1;

			 rotPtr = (w-1)*h;
			 for(i = 0, y = w - 1; i < w; i++, y--) {

				 	 iDiv2 = i >> 1;
				 	 yDiv2 = y >> 1;
				 	 //Y = yuv[pixPtr + i];
				 	 yuv_rot[rotPtr + x] = yuv[pixPtr + i];

					 if((i & 0x1) != 1) {
							 cOff = size + jDiv2w + (iDiv2 << 1);
							 cOffRot = size + yDiv2 * h + xDiv22;
							 //Cb = yuv[cOff];
							 yuv_rot[cOffRot] = yuv[cOff];

							 //Cr = yuv[cOff + 1];
							 yuv_rot[cOffRot + 1] = yuv[cOff + 1];
					 }

					 rotPtr -= h;
			 }
			 pixPtr += w;
		}
    }

	free(yuv_rot);
}

void ImageRotation_YUV2BMP(int* rgb, jbyte* yuv, int w, int h, int size, int rad_y)
{

    int             sz;
    int             i;
    int             j;
    int             Y;
    int             Cr = 0;
    int             Cb = 0;
    int             yuvPtr = 0;
    int             jDiv2 = 0;
    int             jDiv2w;

    int             R = 0;
    int             G = 0;
    int             B = 0;
    int             cOff;

    sz = w * h;

	int 			x, y;
	int 			rgbPtr = 0;

	//Rotation degree = 0;
	if (rad_y > -135 && rad_y <= -45)
		return;

	jbyte*  yuv_rot = (jbyte*)malloc(size);

	//Rotation degree = 90;
    if ((rad_y > -45 && rad_y <= 0) || (rad_y > 0 && rad_y <= 45)) {

    	yuvPtr = 0;
        for(j = 0, x = h - 1; j < h; j++, x--) {
		//	yuvPtr = j * w;
			jDiv2 = j >> 1;
			jDiv2w = jDiv2 * w;
			rgbPtr = 0;
			for(i = 0, y = 0; i < w; i++, y++) {
				 Y = yuv[yuvPtr + i];
				 if(Y < 0) Y += 255;
				 if((i & 0x1) != 1) {
				//	 cOff = sz + jDiv2 * w + (i >> 1) * 2;
					 cOff = sz + jDiv2w + (i >> 1) * 2;

					 Cb = yuv[cOff];
					 if(Cb < 0) Cb += 127; else Cb -= 128;
					 Cr = yuv[cOff + 1];
					 if(Cr < 0) Cr += 127; else Cr -= 128;
				 }
				 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);
				 if(R < 0) R = 0; else if(R > 255) R = 255;
				 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
				 if(G < 0) G = 0; else if(G > 255) G = 255;
				 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
				 if(B < 0) B = 0; else if(B > 255) B = 255;

				 rgb[rgbPtr + x] = 0xff000000 + (R << 16) + (G << 8) + B;
				 rgbPtr += w;
			}
			yuvPtr += w;
        }

    }
    //Rotation degree = 180;
    else if (rad_y > 45 && rad_y <= 135) {

    	yuvPtr = 0;
    	rgbPtr = (h - 1)*w;
        for(j = 0, y = h - 1; j < h; j++, y--) {
		//	yuvPtr = j * w;
			jDiv2 = j >> 1;
			jDiv2w = jDiv2 * w;

			for(i = 0, x = w - 1; i < w; i++, x--) {
				 Y = yuv[yuvPtr + i];
				 if(Y < 0) Y += 255;
				 if((i & 0x1) != 1) {
				//	 cOff = sz + jDiv2 * w + (i >> 1) * 2;
					 cOff = sz + jDiv2w + (i >> 1) * 2;

					 Cb = yuv[cOff];
					 if(Cb < 0) Cb += 127; else Cb -= 128;
					 Cr = yuv[cOff + 1];
					 if(Cr < 0) Cr += 127; else Cr -= 128;
				 }
				 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);
				 if(R < 0) R = 0; else if(R > 255) R = 255;
				 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
				 if(G < 0) G = 0; else if(G > 255) G = 255;
				 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
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
		//	yuvPtr = j * w;
			jDiv2 = j >> 1;
			jDiv2w = jDiv2 * w;

			rgbPtr = (w - 1)*h;
			for(i = 0, y = w - 1; i < w; i++, y--) {
				 Y = yuv[yuvPtr + i];
				 if(Y < 0) Y += 255;
				 if((i & 0x1) != 1) {
				//	 cOff = sz + jDiv2 * w + (i >> 1) * 2;
					 cOff = sz + jDiv2w + (i >> 1) * 2;

					 Cb = yuv[cOff];
					 if(Cb < 0) Cb += 127; else Cb -= 128;
					 Cr = yuv[cOff + 1];
					 if(Cr < 0) Cr += 127; else Cr -= 128;
				 }
				 R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);
				 if(R < 0) R = 0; else if(R > 255) R = 255;
				 G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
				 if(G < 0) G = 0; else if(G > 255) G = 255;
				 B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
				 if(B < 0) B = 0; else if(B > 255) B = 255;

				 rgb[rgbPtr + x] = 0xff000000 + (R << 16) + (G << 8) + B;
				 rgbPtr -= w;
			}
			yuvPtr -= w;
        }
    }

	free(yuv_rot);
}

void YUV2BMP(jint* rgb, jbyte* yuv, int w, int h)
{
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

    sz = w * h;

    for(j = 0; j < h; j++) {
             pixPtr = j * w;
             jDiv2 = j >> 1;
             for(i = 0; i < w; i++) {
                     Y = yuv[pixPtr];
                     if(Y < 0) Y += 255;
                     if((i & 0x1) != 1) {
                             cOff = sz + jDiv2 * w + (i >> 1) * 2;
                             Cb = yuv[cOff];
                             if(Cb < 0) Cb += 127; else Cb -= 128;
                             Cr = yuv[cOff + 1];
                             if(Cr < 0) Cr += 127; else Cr -= 128;
                     }
                     R = Y + Cr + (Cr >> 2) + (Cr >> 3) + (Cr >> 5);
                     if(R < 0) R = 0; else if(R > 255) R = 255;
                     G = Y - (Cb >> 2) + (Cb >> 4) + (Cb >> 5) - (Cr >> 1) + (Cr >> 3) + (Cr >> 4) + (Cr >> 5);
                     if(G < 0) G = 0; else if(G > 255) G = 255;
                     B = Y + Cb + (Cb >> 1) + (Cb >> 2) + (Cb >> 6);
                     if(B < 0) B = 0; else if(B > 255) B = 255;
                     rgb[pixPtr++] = 0xff000000 + (R << 16) + (G << 8) + B;
             }
    }

}
int* rgbData;
int rgbDataSize = 0;

extern "C" {

	JNIEXPORT jint JNICALL Java_com_example_cameratest_JNIMethods_startink(
		//	JNIEnv *,jclass, jbyteArray) {
		JNIEnv * env, jobject obj, jintArray rgbOut, jbyteArray yuv420sp, jint width, jint height, jint rad){


	//	jint len = env->GetArrayLength(yuv420sp);
	//	jbyte* yuv = (jbyte*)env->GetPrimitiveArrayCritical(yuv420sp, 0);
	//	jint *rgbData = (jint*)env->GetPrimitiveArrayCritical(rgbOut, 0);

		int sz = width*height;
		jboolean isCopy;
		jbyte* yuv = env->GetByteArrayElements(yuv420sp, &isCopy);
		if(rgbDataSize < sz) {
				int tmp[sz];
				rgbData = &tmp[0];
				rgbDataSize = sz;
		}

	//	ImageRotationYUV(yuv, width, height, len, rad);
	//	ImageRotation_YUV2BMP(rgbData, yuv, width, height, len, rad);
		YUV2BMP(rgbData, yuv, width, height);

		env->SetIntArrayRegion(rgbOut, 0, sz, ( jint * ) &rgbData[0] );
		env->ReleaseByteArrayElements(yuv420sp, yuv, JNI_ABORT);

	//    env->ReleasePrimitiveArrayCritical(rgbOut, rgbData, 0);
	//	env->ReleasePrimitiveArrayCritical(yuv420sp, yuv, 0);
		return 0;
	}
}
