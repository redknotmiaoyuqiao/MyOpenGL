package com.redknot.openglcpp;

import android.opengl.GLSurfaceView;

import com.redknot.tool.NativeMethod;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by redknot on 8/9/16.
 */
public class DrawRenderer implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        NativeMethod.initialize(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        NativeMethod.drawFrame();
    }
}
