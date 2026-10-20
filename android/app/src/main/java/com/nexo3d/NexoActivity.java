package com.nexo3d;

import android.app.Activity;
import android.os.Bundle;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.MotionEvent;
import android.widget.FrameLayout;
import android.util.Log;

/** Native-first Android host. The 3D viewport is a native surface, never a WebView. */
public final class NexoActivity extends Activity implements SurfaceHolder.Callback {
    private static final String TAG = "Nexo3D";
    private SurfaceView viewport;
    private boolean nativeStarted = false;

    static {
        System.loadLibrary("nexo_android");
    }

    private static native boolean nativeInit(Surface surface, int width, int height);
    private static native void nativeResize(int width, int height);
    private static native void nativeTouch(int action, float x, float y, int pointerCount);
    private static native void nativeShutdown();

    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        viewport = new SurfaceView(this);
        viewport.getHolder().addCallback(this);
        viewport.setFocusable(true);
        viewport.setOnTouchListener((view, event) -> {
            nativeTouch(event.getActionMasked(), event.getX(), event.getY(), event.getPointerCount());
            return true;
        });
        FrameLayout root = new FrameLayout(this);
        root.addView(viewport, new FrameLayout.LayoutParams(
                FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.MATCH_PARENT));
        setContentView(root);
    }

    @Override public void surfaceCreated(SurfaceHolder holder) {
        Surface surface = holder.getSurface();
        nativeStarted = nativeInit(surface, viewport.getWidth(), viewport.getHeight());
        if (!nativeStarted) Log.e(TAG, "Native renderer host initialization failed; see logcat.");
    }

    @Override public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        nativeResize(width, height);
    }

    @Override public void surfaceDestroyed(SurfaceHolder holder) {
        if (nativeStarted) nativeShutdown();
        nativeStarted = false;
    }

    @Override protected void onDestroy() {
        if (nativeStarted) nativeShutdown();
        nativeStarted = false;
        super.onDestroy();
    }
}
