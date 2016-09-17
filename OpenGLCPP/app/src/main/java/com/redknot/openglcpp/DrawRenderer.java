package com.redknot.openglcpp;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import com.redknot.tool.NativeMethod;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by redknot on 8/9/16.
 */
public class DrawRenderer implements GLSurfaceView.Renderer {

    private Context context;
    private AssetManager mgr;

    public DrawRenderer(Context context){
        this.context = context;
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        mgr = context.getResources().getAssets();
        NativeMethod.initialize(width, height,mgr);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        NativeMethod.drawFrame();
    }
}
