package tuchsen.descent;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.DisplayMetrics;
import android.view.Surface;
import android.view.View;
import android.view.WindowManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.IOException;

/**
 * Created by devin on 4/17/16.
 */
public class DescentActivity extends Activity implements TextWatcher, SensorEventListener {
	private EditText dummyText;
	private Handler mainHandler;
	private InputMethodManager imm;
	private MediaPlayer mediaPlayer;
	private DescentView descentView;
	private float x, y, z;
	private float buttonSizeBias;
	private int mediaPlayerPosition;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		DisplayMetrics metrics;
		Resources resources;
		Sensor rotationVector;
		SensorManager sensorManager;

		super.onCreate(savedInstanceState);

		// Enable immersive mode and make sure it's enabled whenever we're fullscreen
		setImmersive();
		getWindow().getDecorView().setOnSystemUiVisibilityChangeListener(
				new View.OnSystemUiVisibilityChangeListener() {
					@Override
					public void onSystemUiVisibilityChange(int visibility) {
						if ((visibility & View.SYSTEM_UI_FLAG_FULLSCREEN) == 0) {
							setImmersive();
						}
					}
				});

		// Calculate button size bias; want slightly bigger buttons on bigger screens
		resources = getResources();
		metrics = resources.getDisplayMetrics();
		buttonSizeBias = (float) Math.min(Math.max((metrics.widthPixels / metrics.xdpi
				+ metrics.heightPixels / metrics.ydpi) / 5.5f, 1), 1.4);

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
		rotationVector = sensorManager.getDefaultSensor(Sensor.TYPE_GAME_ROTATION_VECTOR);
		if (rotationVector == null) {
			rotationVector = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
		}
		sensorManager.registerListener(this, rotationVector, SensorManager.SENSOR_DELAY_GAME);

		// Create OpenGL ES view
		descentView = new DescentView(this);

		// Set views
		setContentView(descentView);
		addContentView(dummyText, new WindowManager.LayoutParams());
	}

	@Override
	protected void onPause() {
		super.onPause();
		descentPause();
		mediaPlayer.pause();
		mediaPlayerPosition = mediaPlayer.getCurrentPosition();
	}

	@Override
	protected void onResume() {
		super.onResume();
		setImmersive();
		if (!descentView.getSurfaceWasDestroyed()) {
			descentView.resumeRenderThread();
		}
		mediaPlayer.seekTo(mediaPlayerPosition);
		mediaPlayer.start();
	}

	@Override
	public void beforeTextChanged(CharSequence s, int start, int count, int after) {

	}

	@Override
	public void onTextChanged(CharSequence s, int start, int before, int count) {
		char c;
		int i, numchars = count - before;

		if (numchars < 0) {
			for (i = numchars; i < 0; ++i) {
				// Backspace key
				keyHandler((char) 0x0E);
			}
		} else if (s.length() > 0) {
			for (i = numchars; i > 0; --i) {
				c = s.charAt(s.length() - i);
				if (c == '\n') {
					// Enter key
					keyHandler((char) 0x1C);
				} else {
					keyHandler(c);
				}
			}
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
	private boolean textIsActive() {
		return dummyText.getVisibility() == View.VISIBLE;
	}

	@SuppressWarnings("unused")
	private void activateText() {
		mainHandler.post(new Runnable() {
			@Override
			public void run() {
				dummyText.setText("");
				dummyText.setFocusableInTouchMode(true);
				dummyText.setVisibility(View.VISIBLE);
				dummyText.requestFocus();
				imm.showSoftInput(dummyText, InputMethodManager.SHOW_IMPLICIT);
			}
		});
	}

	@SuppressWarnings("unused")
	private void deactivateText() {
		mainHandler.post(new Runnable() {
			@Override
			public void run() {
				imm.hideSoftInputFromWindow(dummyText.getWindowToken(), 0);
				dummyText.setFocusable(false);
				dummyText.setVisibility(View.INVISIBLE);
			}
		});
	}

	@SuppressWarnings("unused")
	private float[] getOrientation() {
		float orientation[] = new float[3];
		float R[] = new float[9];
		float rotationVector[] = {x, y, z};

		SensorManager.getRotationMatrixFromVector(R, rotationVector);
		SensorManager.getOrientation(R, orientation);
		if (getWindowManager().getDefaultDisplay().getRotation() == Surface.ROTATION_270) {
			orientation[2] *= -1;
		}
		return orientation;
	}

	@SuppressWarnings("unused")
	private void playMidi(String path, boolean looping) {
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
	private void stopMidi() {
		mediaPlayer.stop();
		mediaPlayer.reset();
	}

	@SuppressWarnings("unused")
	private void setMidiVolume(float volume) {
		mediaPlayer.setVolume(volume, volume);
	}

	@SuppressWarnings("unused")
	private float dpToPx(float dp) {
		Resources resources = getResources();
		DisplayMetrics metrics = resources.getDisplayMetrics();
		return dp * (((float) metrics.densityDpi / DisplayMetrics.DENSITY_DEFAULT) * buttonSizeBias);
	}

	@SuppressWarnings("unused")
	private float pxToDp(float px) {
		Resources resources = getResources();
		DisplayMetrics metrics = resources.getDisplayMetrics();
		return px / (((float) metrics.densityDpi / DisplayMetrics.DENSITY_DEFAULT) * buttonSizeBias);
	}

	/**
	 * Enables immersive mode, hiding navigation controls
	 */
	private void setImmersive() {
		getWindow().getDecorView().setSystemUiVisibility(
				View.SYSTEM_UI_FLAG_LAYOUT_STABLE
						| View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
						| View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
						| View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
						| View.SYSTEM_UI_FLAG_FULLSCREEN
						| View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
	}

	private static native void keyHandler(char key);

	private static native void descentPause();

	static {
		System.loadLibrary("Descent");
	}
}
