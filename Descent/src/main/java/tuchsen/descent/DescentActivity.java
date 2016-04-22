package tuchsen.descent;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.graphics.Point;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.MediaPlayer;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.DisplayMetrics;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by devin on 4/17/16.
 */
public class DescentActivity extends Activity implements TextWatcher, SensorEventListener {
	private GLSurfaceView mGLView;
	private EditText dummyText;
	private Handler mainHandler;
	private InputMethodManager imm;
	private MediaPlayer mediaPlayer;
	private float x, y, z;
	private float buttonSizeBias;
	private int mediaPlayerPosition;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		SensorManager sensorManager;
		Sensor rotationVector;
		Resources resources;
		DisplayMetrics metrics;

		super.onCreate(savedInstanceState);

		setImmersive();

		// Calculate button size bias; want slightly bigger buttons on bigger screens
		resources = getResources();
		metrics = resources.getDisplayMetrics();
		buttonSizeBias = (float) Math.min(Math.max((metrics.widthPixels / metrics.xdpi + metrics.heightPixels / metrics.ydpi) / 5.5f, 1), 1.4);

		// Set up dummy text field for text input
		dummyText = new EditText(this);
		dummyText.addTextChangedListener(this);
		dummyText.setFocusable(false);
		dummyText.setVisibility(View.INVISIBLE);
		dummyText.setAlpha(0.0f);
		mainHandler = new Handler(getMainLooper());
		imm = (InputMethodManager)
				getSystemService(Context.INPUT_METHOD_SERVICE);

		// Create media player for MIDI
		mediaPlayer = new MediaPlayer();

		// Set up sensor manager for motion controls
		sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
		rotationVector = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
		sensorManager.registerListener(this, rotationVector, SensorManager.SENSOR_DELAY_GAME);

		// Create OpenGL ES view
		mGLView = new DescentGLSurfaceView(this);

		// Set views
		setContentView(mGLView);
		addContentView(dummyText, new WindowManager.LayoutParams());
	}

	@Override
	protected void onPause() {
		super.onPause();
		mediaPlayer.pause();
		mGLView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mGLView.onResume();
		mediaPlayer.start();
	}

	@Override
	public void beforeTextChanged(CharSequence s, int start, int count, int after) {

	}

	@Override
	public void onTextChanged(CharSequence s, int start, int before, int count) {
		char c;

		if (s.length() > 0) {
			c = s.charAt(s.length() - 1);
		} else {
			c = '\0';
		}
		if (count < before) {
			// Backspace key
			keyHandler((char) 0x0E);
		} else if (c == '\n') {
			// Enter key
			keyHandler((char) 0x1C);
		} else if (c != '\0' && before != count) {
			keyHandler(c);
		}
	}

	@Override
	public void afterTextChanged(Editable s) {

	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		x = event.values[0];
		y = event.values[1];
		z = event.values[2];
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {

	}

	@SuppressWarnings("unused")
	public boolean textIsActive() {
		return imm.isAcceptingText();
	}

	@SuppressWarnings("unused")
	public void activateText() {
		mainHandler.post(new Runnable() {
			@Override
			public void run() {
				dummyText.setFocusableInTouchMode(true);
				dummyText.setVisibility(View.VISIBLE);
				dummyText.requestFocus();
				imm.showSoftInput(dummyText, InputMethodManager.SHOW_IMPLICIT);
			}
		});
	}

	@SuppressWarnings("unused")
	public void deactivateText() {
		mainHandler.post(new Runnable() {
			@Override
			public void run() {
				imm.hideSoftInputFromWindow(dummyText.getWindowToken(), 0);
				dummyText.setFocusable(false);
				dummyText.setVisibility(View.INVISIBLE);
				setImmersive();
			}
		});
	}

	@SuppressWarnings("unused")
	public float[] getOrientation() {
		float orientation[] = new float[3];
		float R[] = new float[9];
		float rotationVector[] = {x, y, z};

		SensorManager.getRotationMatrixFromVector(R, rotationVector);
		SensorManager.getOrientation(R, orientation);
		return orientation;
	}

	@SuppressWarnings("unused")
	public void playMidi(String path, boolean looping) {
		File file = new File(path);
		FileDescriptor fd;
		FileInputStream fos;

		try {
			fos = new FileInputStream(file);
			fd = fos.getFD();
			mediaPlayer.setDataSource(fd);
			mediaPlayer.prepare();
		} catch (IOException e) {
			e.printStackTrace();
		}
		mediaPlayer.setLooping(looping);
		mediaPlayer.start();
	}

	@SuppressWarnings("unused")
	public void stopMidi() {
		mediaPlayer.stop();
		mediaPlayer.reset();
	}

	@SuppressWarnings("unused")
	public void setMidiVolume(float volume) {
		mediaPlayer.setVolume(volume, volume);
	}

	@SuppressWarnings("unused")
	public float dpToPx(float dp) {
		Resources resources = getResources();
		DisplayMetrics metrics = resources.getDisplayMetrics();
		return dp * (((float) metrics.densityDpi / DisplayMetrics.DENSITY_DEFAULT) * buttonSizeBias);
	}

	@SuppressWarnings("unused")
	public float pxToDp(float px) {
		Resources resources = getResources();
		DisplayMetrics metrics = resources.getDisplayMetrics();
		return px / (((float) metrics.densityDpi / DisplayMetrics.DENSITY_DEFAULT) * buttonSizeBias);
	}

	private void setImmersive() {
		// Hide navigation
		getWindow().getDecorView().setSystemUiVisibility(
				View.SYSTEM_UI_FLAG_LAYOUT_STABLE
						| View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
						| View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
						| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
						| View.SYSTEM_UI_FLAG_FULLSCREEN
						| View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
	}

	private static native void keyHandler(char key);

	static {
		System.loadLibrary("Descent");
	}
}

class DescentGLSurfaceView extends GLSurfaceView {
	DescentRenderer mRenderer;

	public DescentGLSurfaceView(Context context) {
		super(context);
		mRenderer = new DescentRenderer(context);
		setRenderer(mRenderer);
	}

	@Override
	public boolean onTouchEvent(final MotionEvent event) {
		int i, historySize, firstPointerIndex, numPointers;
		int action = event.getActionMasked();
		float prevX, prevY;
		boolean touchHandled = false;

		historySize = event.getHistorySize();
		if (action == MotionEvent.ACTION_POINTER_DOWN || action == MotionEvent.ACTION_POINTER_UP) {
			firstPointerIndex = event.getActionIndex();
		} else {
			firstPointerIndex = 0;
		}
		if (action == MotionEvent.ACTION_MOVE) {
			numPointers = event.getPointerCount();
		} else {
			numPointers = 1;
		}
		for (i = firstPointerIndex; i < numPointers + firstPointerIndex; ++i) {
			if (historySize > 0) {
				prevX = event.getHistoricalX(i, 0);
				prevY = event.getHistoricalY(i, 0);
			} else {
				prevX = prevY = 0;
			}
			touchHandled |= touchHandler(event.getActionMasked(), event.getPointerId(i),
					event.getX(i), event.getY(i), prevX, prevY);
		}
		if (!touchHandled && (action == MotionEvent.ACTION_DOWN || action == MotionEvent.ACTION_UP)) {
			mouseHandler((short) event.getX(), (short) event.getY(), action == MotionEvent.ACTION_DOWN);
			return true;
		}
		return touchHandled;
	}

	@Override
	public void onPause() {
		super.onPause();
	}

	@Override
	public void onResume() {
		super.onResume();
	}

	private static native void mouseHandler(short x, short y, boolean down);

	private static native boolean touchHandler(int action, int pointerId, float x, float y, float prevX,
											   float prevY);
}

class DescentRenderer implements GLSurfaceView.Renderer {
	private Context context;

	public DescentRenderer(Context context) {
		this.context = context;
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
		Display display = wm.getDefaultDisplay();
		Point size = new Point();
		display.getRealSize(size);

		// Clear to back
		gl.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);

		// Enable depth test
		gl.glClearDepthf(1.0f);
		gl.glEnable(GL10.GL_DEPTH_TEST);

		// Enable culling
		gl.glEnable(GL10.GL_CULL_FACE);
		gl.glCullFace(GL10.GL_BACK);

		// Viewport is screen bounds
		gl.glViewport(0, 0, size.x, size.y);

		// Enable blending for alphas
		gl.glEnable(GL10.GL_BLEND);
		gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);

		// Disable depth mask (otherwise get artifacts with 3D sprites)
		gl.glDepthMask(false);

		// Start Descent!
		descentMain(size.x, size.y, context, context.getAssets(),
				context.getFilesDir().getAbsolutePath(), context.getCacheDir().getAbsolutePath());
	}

	public void onDrawFrame(GL10 gl) {
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
	}

	private static native void descentMain(int w, int h, Context activity,
										   AssetManager assetManager, String documentPath,
										   String cachePath);
}
