#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include <string>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <math.h>

#include "LOG/logger.h"

#include "MYGL/Vector3f.h"
#include "MYGL/ShaderManager.h"

#include "FILE/ReadFile.h"

#include "com_redknot_tool_NativeMethod.h"

using namespace std;

GLuint VBO;//定点缓冲区对象

void CreateVertexBuffer()
{
    Vector3f vectices[3];
    vectices[0] = Vector3f(-1.0f,-1.0f,0.0f);
    vectices[1] = Vector3f(1.0f,-1.0f,0.0f);
    vectices[2] = Vector3f(0.0f,1.0f,0.0f);


    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vectices),vectices,GL_STATIC_DRAW);
}

GLuint UniformLocation;

JNIEXPORT void JNICALL Java_com_redknot_tool_NativeMethod_initialize
  (JNIEnv * env, jclass thiz, jint width, jint height, jobject assetManager)
  {
    glClearColor(1.0f,1.0f,1.0f,1.0f);

    AAssetManager* g_pAssetManager = AAssetManager_fromJava(env, assetManager);
    ReadFile read = ReadFile(g_pAssetManager);

    char * vertex_shader = read.readShaderSrcFile("vertex.shader");
    char * fragment_shader = read.readShaderSrcFile("fragment.shader");

    ShaderManager shader = ShaderManager(vertex_shader,fragment_shader);

    shader.setUniformLocation(&UniformLocation);
    shader.CompileShaders();

    CreateVertexBuffer();
  }

JNIEXPORT void JNICALL Java_com_redknot_tool_NativeMethod_drawFrame
  (JNIEnv * env, jclass thiz)
  {
    glClear(GL_COLOR_BUFFER_BIT);

    static float scale = 0.0f;
    scale += 0.02f;
    glUniform1f(UniformLocation,sinf(scale));

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*4,0);
    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableVertexAttribArray(0);
  }

