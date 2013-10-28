package com.example.cameratest;

import android.app.Activity;
import android.hardware.Camera;
import android.hardware.Camera.PreviewCallback;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.LinearLayout;

public class MainActivity extends Activity {

	protected static final String TAG = MainActivity.class.getSimpleName();
	private Camera mCamera = null;
	private CameraPreview mPreview;
	private final PreviewCallback cb_preview = new PreviewCallback() {

		@Override
		public void onPreviewFrame(byte[] arg0, Camera arg1) {
			// TODO Auto-generated method stub
			Log.d(TAG, "cb_preview");
		}
	};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		this.mPreview = new CameraPreview(this.getApplicationContext());
		LinearLayout preview_container = (LinearLayout) this
				.findViewById(R.id.preview_container);
		preview_container.addView(this.mPreview);
//		 this.mPreview.setAspectRatio("16:9");

	}

	@Override
	protected void onResume() {
		super.onResume();
		if (this.mCamera == null) {
			this.mCamera = Camera.open();
			this.mPreview.setmCamera(this.mCamera);
//			this.mCamera.setPreviewCallback(cb_preview);
			this.mCamera.startPreview();
		}
	}

	@Override
	protected void onPause() {
		super.onPause();
		if (this.mCamera != null) {
			this.mCamera.setPreviewCallback(null);
			this.mCamera.stopPreview();
			this.mCamera.release();
			this.mCamera = null;
		}

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
