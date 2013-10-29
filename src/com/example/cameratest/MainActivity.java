package com.example.cameratest;

import android.app.Activity;
import android.hardware.Camera;
import android.hardware.Camera.PreviewCallback;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity {

	protected static final String TAG = MainActivity.class.getSimpleName();
	private Camera mCamera = null;
	private CameraPreview mPreview;
	private boolean cb_set = false;
	private TextView mResultTextView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		this.mPreview = new CameraPreview(this.getApplicationContext());
		LinearLayout preview_container = (LinearLayout) this
				.findViewById(R.id.preview_container);
		preview_container.addView(this.mPreview);
		// this.mPreview.setAspectRatio("16:9");
		
		Button b = (Button) this.findViewById(R.id.button_capture);
		b.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				MainActivity parent = MainActivity.this;
				Camera camera = parent.mCamera;
				if(parent.cb_set){
					camera.setPreviewCallback(null);
					parent.cb_set = false;
				}else{
					camera.setPreviewCallback(parent.cb_preview);
					parent.cb_set = true;
				}
			}
		});

		mResultTextView = (TextView) this.findViewById(R.id.result_textview);
		
	}

	@Override
	protected void onResume() {
		super.onResume();
		if (this.mCamera == null) {
			this.mCamera = Camera.open();
			this.mPreview.setmCamera(this.mCamera);
			// this.mCamera.setPreviewCallback(cb_preview);
			this.mCamera.startPreview();
		}
	}

	@Override
	protected void onPause() {
		super.onPause();
		if (this.mCamera != null) {
			this.mCamera.setPreviewCallback(null);
			this.cb_set = false;
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

	private final PreviewCallback cb_preview = new PreviewCallback() {

		@Override
		public void onPreviewFrame(byte[] imag, Camera camera) {
			// TODO Auto-generated method stub
			Log.d(TAG, "cb_preview");
			int ret = JNIMethods.startink(imag);
			if (ret != 0){
				mResultTextView.setText("Captured!");
				camera.setPreviewCallback(null);
				MainActivity.this.cb_set = false;
			}else{
				mResultTextView.setText("Capturing...");
			}
		}
	};

}
