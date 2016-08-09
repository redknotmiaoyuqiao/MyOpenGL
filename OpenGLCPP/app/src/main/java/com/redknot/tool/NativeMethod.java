package com.redknot.tool;

/**
 * Created by redknot on 8/9/16.
 */
public class NativeMethod {
    static{
        System.loadLibrary("opengldraw");
    }
    public native static void initialize(int width, int height);
    public native static void drawFrame();
}
