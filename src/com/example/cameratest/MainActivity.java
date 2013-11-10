package com.example.cameratest;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.List;

import android.app.Activity;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.PreviewCallback;
import android.hardware.Camera.Size;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

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
		addContentView(new CameraOnView(this), new LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));

		Button b = (Button) this.findViewById(R.id.button_picture);
		b.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				MainActivity parent = MainActivity.this;
				Camera camera = parent.mCamera;
				camera.takePicture(null, null, cb_picture);
			}
		});

		Button b2 = (Button) this.findViewById(R.id.button_capture);
		b2.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				MainActivity parent = MainActivity.this;
				Camera camera = parent.mCamera;

				if (parent.cb_set) {
					camera.setPreviewCallback(null);
					parent.cb_set = false;
				} else {
					camera.setPreviewCallback(parent.cb_preview2);
					parent.cb_set = true;
				}

			}
		});

		mResultTextView = (TextView) this.findViewById(R.id.result_textview);

	}

	private void setOptimalPictureSize() {

		Parameters params = this.mCamera.getParameters();
		List<Size> sizes = params.getSupportedPictureSizes();

		double targetRatio = (double) 4 / 3;
		// int minSize = 1000;
		int minWdith = 1000;
		int minHeight = 1000;
		boolean bIsVailble = false;
		Size size_out = sizes.get(0);
		size_out.width = 10000;
		size_out.height = 10000;

		for (Size size : sizes) {
			/*
			 * double ratio = (double) size.width / size.height; int gasosu =
			 * size.width * size.height; if (gasosu < (300 * 10000) &&
			 * Math.abs(ratio - targetRatio) < 0.1) { return size; }
			 */

			if (size.width > minWdith && size.height > minHeight) {

				if (size.width < size_out.width
						&& size.height < size_out.height) {
					size_out = size;
				}
				bIsVailble = true;
			}

		}

		if (bIsVailble) {
			params.setPictureSize(size_out.width, size_out.height);
		} else {
			params.setPictureSize(sizes.get(0).width, sizes.get(0).height);
		}

		this.mCamera.setParameters(params);

	}

	@Override
	protected void onResume() {
		super.onResume();
		if (this.mCamera == null) {
			this.mCamera = Camera.open();
			this.mPreview.setmCamera(this.mCamera);
			// this.mCamera.setPreviewCallback(cb_preview);
			this.setOptimalPictureSize();
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
			if (ret != 0) {
				mResultTextView.setText("Captured!");
				camera.setPreviewCallback(null);
				MainActivity.this.cb_set = false;
			} else {
				mResultTextView.setText("Capturing...");
			}
		}
	};

	private Camera.PreviewCallback cb_preview2 = new Camera.PreviewCallback() {
		// @Override
		public void onPreviewFrame(byte[] data, Camera camera) {
			Log.v(TAG, "Preview ");

			if (data != null) {

				// rawデータをJPEGファイルに変換
				camera.addCallbackBuffer(data);
				Camera.Parameters params = camera.getParameters();
				Camera.Size size = params.getPreviewSize();
				YuvImage image = new YuvImage(data, params.getPreviewFormat(),
						size.width, size.height, null);

				File dir = new File(
						Environment
								.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES),
						"smart-ink");

				if (!dir.exists()) {
					if (!dir.mkdirs()) {
						Toast.makeText(
								MainActivity.this.getApplicationContext(),
								"cannot make picture directory in SD card",
								Toast.LENGTH_SHORT).show();
						return;
					}
				}

				String fname = System.currentTimeMillis() + ".jpg";
				File file = new File(dir, fname);
				FileOutputStream out = null;
				try {
					out = new FileOutputStream(file);
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				image.compressToJpeg(
						new Rect(0, 0, image.getWidth(), image.getHeight()),
						100, out);
				try {
					out.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}

			camera.startPreview();

		}

	};

	private final PictureCallback cb_picture = new PictureCallback() {

		@Override
		public void onPictureTaken(byte[] imag, Camera camera) {
			// TODO Auto-generated method stub
			File dir = new File(
					Environment
							.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES),
					"smart-ink");

			if (!dir.exists()) {
				if (!dir.mkdirs()) {
					Toast.makeText(MainActivity.this.getApplicationContext(),
							"cannot make picture directory in SD card",
							Toast.LENGTH_SHORT).show();
					return;
				}
			}

			String fname = System.currentTimeMillis() + ".jpg";
			File file = new File(dir, fname);

			FileOutputStream fos;
			try {
				fos = new FileOutputStream(file);
				fos.write(imag);
				fos.close();
				Log.d(TAG, "saved file to " + file.toString());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}

			camera.startPreview();
		}

	};

}
