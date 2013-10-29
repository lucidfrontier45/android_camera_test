package com.example.cameratest;

public class JNIMethods {
	public static native int startink(byte[] imag);
	
	static {
		System.loadLibrary("smartink-jni");
	}
}
