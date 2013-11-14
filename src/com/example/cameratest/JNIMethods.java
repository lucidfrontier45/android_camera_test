package com.example.cameratest;

import android.graphics.Bitmap;

public class JNIMethods {
	public static native int startink(int[] rgb, byte[] imag, int width, int height, int rad);
	
	static {
		System.loadLibrary("smartink-jni");
	}
}
