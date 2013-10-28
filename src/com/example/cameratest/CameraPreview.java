package com.example.cameratest;

import java.io.IOException;
import java.util.List;

import android.content.Context;
import android.hardware.Camera;
import android.hardware.Camera.Size;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.ViewGroup.LayoutParams;

class CameraPreview extends SurfaceView implements SurfaceHolder.Callback {
	private static final String TAG = CameraPreview.class.getSimpleName();

	private Camera mCamera;
	private Camera.Size mPreviewSize;
	private String aspect_ratio = "4:3";

	public void setAspectRatio(String ratio) {
		this.aspect_ratio = ratio;
	}

	public CameraPreview(Context context) {
		super(context);
		// TODO Auto-generated constructor stub

		SurfaceHolder holder = this.getHolder();
		holder.addCallback(this);
		holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		Log.d(TAG, String.format("Surface Size is %d x %d", width, height));
		Log.d(TAG, String.format("Preview Size is %d x %d",
				this.mPreviewSize.width, this.mPreviewSize.height));

		float ratio = this.mPreviewSize.width
				/ (float) this.mPreviewSize.height;
     	height = (int) (width * ratio);

		Log.d(TAG, String.format("Modified Size is %d x %d", width, height));
		LayoutParams params = this.getLayoutParams();
		params.height = height;
		params.width = width;
		this.setLayoutParams(params);
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		try {
			this.mCamera.setPreviewDisplay(holder);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	@Override
	public void surfaceDestroyed(SurfaceHolder arg0) {
		// TODO Auto-generated method stub

	}

	private Camera.Size get4x3PreviewSize(Camera camera) {
		List<Size> sizes = camera.getParameters().getSupportedPictureSizes();
		Camera.Size max_size = null;
		float ratio;
		for (Camera.Size size : sizes) {
			ratio = size.width / (float) size.height;
			Log.d(TAG, String.format("SupportedPreviewSize %d x %d ratio = %f",
					size.width, size.height, ratio));
			if (ratio > 1.4) {
				if (this.aspect_ratio.equals("4:3")) {
					// skip this resolution because this is at least 16:9
					continue;
				}
			}else if (ratio < 1.334) {
				if (this.aspect_ratio.equals("16:9")) {
					// skip this resolution because this is at least 16:9
					continue;
				}
			}
			if (max_size == null) {
				max_size = size;
			} else if (size.height > max_size.height) {
				max_size = size;
			}
		}
		
		ratio = max_size.width / (float) max_size.height;
		Log.d(TAG, String.format("MaxSize %d x %d ratio = %f",
				max_size.width, max_size.height, ratio));
		return max_size;
	}

	public Camera getmCamera() {
		return mCamera;
	}

	public void setmCamera(Camera camera) {
		this.mCamera = camera;
		this.mCamera.setDisplayOrientation(90);
		this.mPreviewSize = this.get4x3PreviewSize(camera);
		Camera.Parameters params = this.mCamera.getParameters();
//		params.setPreviewSize(this.mPreviewSize.width, this.mPreviewSize.height);
//		this.mCamera.setParameters(params);
		this.mPreviewSize = params.getPreviewSize();
		if (this.getHolder() != null) {
			try {
				this.mCamera.setPreviewDisplay(this.getHolder());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

}