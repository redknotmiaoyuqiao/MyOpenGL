package com.redknot.model;

import android.content.Context;
import android.opengl.GLES20;

import com.redknot.gltools.GLTools;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * Created by redknot on 8/9/16.
 */
public class Triangle {

    private final String vertexShaderFileName = "shader.vertex";

    private final String fragmentShaderFileName = "shader.fragment";

    private int vertexShader;
    private int fragmentShader;

    private FloatBuffer vertexBuffer;

    private final int COORDS_PER_VERTEX = 3;

    private float triangleCoords[] = {// 按逆时针方向顺序:
            0.0f, 1.0f, 0.0f,// top
            -1.0f, -1.0f, 0.0f,// bottom left
            1.0f, -1.0f, 0.0f// bottom right
    };

    private float color[] = {
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f
    };

    public Triangle() {
        ByteBuffer bb = ByteBuffer.allocateDirect(triangleCoords.length * 4);
        bb.order(ByteOrder.nativeOrder());
        vertexBuffer = bb.asFloatBuffer();
        vertexBuffer.put(triangleCoords);
        vertexBuffer.position(0);

        GLTools glTools = new GLTools();

        vertexShader = glTools.loadShader(GLES20.GL_VERTEX_SHADER, vertexShaderFileName);
        fragmentShader = glTools.loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentShaderFileName);
    }

    public void draw() {
        useShader();
    }

    private void useShader() {
        int mProgram = GLES20.glCreateProgram();
        GLES20.glAttachShader(mProgram, vertexShader);
        GLES20.glAttachShader(mProgram, fragmentShader);
        GLES20.glLinkProgram(mProgram);
        GLES20.glUseProgram(mProgram);

        int mPositionHandle = GLES20.glGetAttribLocation(mProgram, "vPosition");
        GLES20.glEnableVertexAttribArray(mPositionHandle);
        GLES20.glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX,GLES20.GL_FLOAT, false, 0, vertexBuffer);

        int mColorHandle = GLES20.glGetUniformLocation(mProgram, "vColor");
        GLES20.glUniform4fv(mColorHandle, 1, color, 0);

        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, triangleCoords.length);

        GLES20.glDisableVertexAttribArray(mPositionHandle);
    }
}
