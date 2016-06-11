package tuchsen.descent;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Point;
import android.view.Display;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.WindowManager;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL10;

public class DescentView extends SurfaceView implements SurfaceHolder.Callback {
	private boolean descentRunning, paused, surfaceWasDestroyed;
	private Context context;
	private DescentView thiz;
	private final Object renderThreadObj = new Object();
	private Point size;
	private SurfaceHolder holder;

	public DescentView(Context context) {
		super(context);
		this.context = context;
		this.descentRunning = false;
		this.holder = getHolder();
		this.thiz = this;
		holder.addCallback(this);
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
				prevX = event.getX(i);
				prevY = event.getY(i);
			}
			touchHandled |= touchHandler(event.getActionMasked(), event.getPointerId(i),
					event.getX(i), event.getY(i), prevX, prevY);
		}
		if (!touchHandled && (action == MotionEvent.ACTION_DOWN ||
				action == MotionEvent.ACTION_UP)) {
			mouseHandler((short) event.getX(), (short) event.getY(),
					action == MotionEvent.ACTION_DOWN);
			return true;
		}
		return touchHandled;
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		if (!descentRunning) {
			new Thread(new Runnable() {
				@Override
				public void run() {
					WindowManager wm = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
					Display display = wm.getDefaultDisplay();
					size = new Point();
					display.getRealSize(size);
					initEgl();

					// Start Descent!
					descentMain(size.x, size.y, context, thiz, context.getAssets(),
							context.getFilesDir().getAbsolutePath(),
							context.getCacheDir().getAbsolutePath());
				}
			}).start();
			descentRunning = true;
		} else {
			this.holder = holder;
			resumeRenderThread();
		}
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		surfaceWasDestroyed = true;
		surfaceWasDestroyed();
	}

	public boolean getSurfaceWasDestroyed() {
		return surfaceWasDestroyed;
	}

	public void resumeRenderThread() {
		synchronized (renderThreadObj) {
			paused = false;
			surfaceWasDestroyed = false;
			renderThreadObj.notifyAll();
		}
	}

	@SuppressWarnings("unused")
	private void pauseRenderThread() {
		synchronized (renderThreadObj) {
			paused = true;
			while (paused) {
				try {
					renderThreadObj.wait();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

	/**
	 * Initializes EGL for the current thread
	 */
	private void initEgl() {
		int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
		int[] num_config = new int[1];
		final EGLConfig configs[] = new EGLConfig[1];
		int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 1, EGL10.EGL_NONE};
		EGL10 egl;
		EGLConfig eglConfig;
		EGLContext eglContext;
		EGLDisplay eglDisplay;
		EGLSurface eglSurface;
		GL10 gl;

		egl = (EGL10) EGLContext.getEGL();
		eglDisplay = egl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
		egl.eglInitialize(eglDisplay, new int[]{1, 0});
		egl.eglChooseConfig(eglDisplay, new int[]{
				EGL10.EGL_RED_SIZE, 8,
				EGL10.EGL_GREEN_SIZE, 8,
				EGL10.EGL_BLUE_SIZE, 8,
				EGL10.EGL_ALPHA_SIZE, 8,
				EGL10.EGL_DEPTH_SIZE, 16,
				EGL10.EGL_STENCIL_SIZE, 0,
				EGL10.EGL_NONE}, configs, 1, num_config);
		eglConfig = configs[0];
		eglContext = egl.eglCreateContext(eglDisplay, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
		eglSurface = egl.eglCreateWindowSurface(eglDisplay, eglConfig, holder, null);
		egl.eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
		gl = (GL10) eglContext.getGL();

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
	}

	private static native void mouseHandler(short x, short y, boolean down);

	private static native boolean touchHandler(int action, int pointerId, float x, float y,
											   float prevX, float prevY);

	private static native void surfaceWasDestroyed();

	private static native void descentMain(int w, int h, Context activity,
										   DescentView descentView,
										   AssetManager assetManager, String documentPath,
										   String cachePath);
}
