package com.redknot.opengldemo;

import android.opengl.GLSurfaceView;

import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by redknot on 8/4/16.
 */
public class CubeRenderer implements GLSurfaceView.Renderer {
    float rotateTri, rotateQuad;
    int one = 0x10000;

    int[] colorArray = {
            one, 0, 0, one,
            0, one, 0, one,
            0, 0, one, one,
    };
    int[] triggerArray = {
            0, one, 0,
            -one, -one, 0,
            one, -one, 0};
    int[] quaterArray = {
            one, one, 0,
            -one, one, 0,
            one, -one, 0,
            -one, -one, 0
    };

    @Override
    public void onDrawFrame(GL10 gl) {
        // TODO Auto-generated method stub

        // 清除屏幕和深度缓存
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        // 重置当前的模型观察矩阵
        gl.glLoadIdentity();

        // 左移 1.5 单位，并移入屏幕 6.0
        gl.glTranslatef(-1.5f, 0.0f, -6.0f);
        //设置旋转
        gl.glRotatef(rotateTri, 0.0f, 1.0f, 0.0f);

        //设置定点数组
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
        //设置颜色数组
        gl.glEnableClientState(GL10.GL_COLOR_ARRAY);

        gl.glColorPointer(4, GL10.GL_FIXED, 0, bufferUtil(colorArray));
        // 设置三角形顶点
        gl.glVertexPointer(3, GL10.GL_FIXED, 0, bufferUtil(triggerArray));
        //绘制三角形
        gl.glDrawArrays(GL10.GL_TRIANGLES, 0, 3);

        gl.glDisableClientState(GL10.GL_COLOR_ARRAY);

        //绘制三角形结束
        gl.glFinish();

        /***********************/
        /* 渲染正方形 */
        // 重置当前的模型观察矩阵
        gl.glLoadIdentity();

        // 左移 1.5 单位，并移入屏幕 6.0
        gl.glTranslatef(1.5f, 0.0f, -6.0f);

        // 设置当前色为蓝色
        gl.glColor4f(0.5f, 1.0f, 1.0f, 1.0f);
        //设置旋转
        gl.glRotatef(rotateQuad, 1.0f, 0.0f, 0.0f);

        //设置和绘制正方形
        gl.glVertexPointer(3, GL10.GL_FIXED, 0, bufferUtil(quaterArray));
        gl.glDrawArrays(GL10.GL_TRIANGLE_STRIP, 0, 4);

        //绘制正方形结束
        gl.glFinish();

        //取消顶点数组
        gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);

        //改变旋转的角度
        rotateTri += 0.5f;
        rotateQuad -= 0.5f;
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        // TODO Auto-generated method stub

        float ratio = (float) width / height;
        //设置OpenGL场景的大小
        gl.glViewport(0, 0, width, height);
        //设置投影矩阵
        gl.glMatrixMode(GL10.GL_PROJECTION);
        //重置投影矩阵
        gl.glLoadIdentity();
        // 设置视口的大小
        gl.glFrustumf(-ratio, ratio, -1, 1, 1, 10);
        // 选择模型观察矩阵
        gl.glMatrixMode(GL10.GL_MODELVIEW);
        // 重置模型观察矩阵
        gl.glLoadIdentity();

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        // TODO Auto-generated method stub
        // 启用阴影平滑
        gl.glShadeModel(GL10.GL_SMOOTH);

        // 黑色背景
        gl.glClearColor(0, 0, 0, 0);

        // 设置深度缓存
        gl.glClearDepthf(1.0f);
        // 启用深度测试
        gl.glEnable(GL10.GL_DEPTH_TEST);
        // 所作深度测试的类型
        gl.glDepthFunc(GL10.GL_LEQUAL);

        // 告诉系统对透视进行修正
        gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_FASTEST);
    }

    /*
     * OpenGL 是一个非常底层的画图接口，它所使用的缓冲区存储结构是和我们的 java 程序中不相同的。
     * Java 是大端字节序(BigEdian)，而 OpenGL 所需要的数据是小端字节序(LittleEdian)。
     * 所以，我们在将 Java 的缓冲区转化为 OpenGL 可用的缓冲区时需要作一些工作。建立buff的方法如下
     * */
    public Buffer bufferUtil(int[] arr) {
        IntBuffer mBuffer;

        //先初始化buffer,数组的长度*4,因为一个int占4个字节
        ByteBuffer qbb = ByteBuffer.allocateDirect(arr.length * 4);
        //数组排列用nativeOrder
        qbb.order(ByteOrder.nativeOrder());

        mBuffer = qbb.asIntBuffer();
        mBuffer.put(arr);
        mBuffer.position(0);

        return mBuffer;
    }

}