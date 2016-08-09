package com.redknot.gltools;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.opengl.GLES20;

import com.redknot.opengldemo.MainActivity;

import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * Created by redknot on 8/9/16.
 */
public class GLTools {

    private Context context = MainActivity.context;

    public GLTools() {
    }

    public int loadShader(int type, String shaderCodeFileName) {
        // 创建一个vertex shader类型(GLES20.GL_VERTEX_SHADER)
        // 或fragment shader类型(GLES20.GL_FRAGMENT_SHADER)

        String shaderCode = getFromAssets(shaderCodeFileName);

        int shader = GLES20.glCreateShader(type);

        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);

        return shader;
    }

    public String getFromAssets(String fileName) {
        String Result = "";
        try {
            InputStreamReader inputReader = new InputStreamReader(context.getResources().getAssets().open(fileName));
            BufferedReader bufReader = new BufferedReader(inputReader);
            String line = "";

            while ((line = bufReader.readLine()) != null) {
                Result += line;
            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return Result;
    }
}
