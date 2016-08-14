#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include <png.h>

#include <string>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <math.h>

#include "LOG/logger.h"

#include "MYGL/Texture.h"
#include "MYGL/Vector3f.h"
#include "MYGL/ShaderManager.h"
#include "MYGL/Matrix4f.h"
#include "MYGL/Pipeline.h"

#include "FILE/ReadFile.h"
#include "FILE/ReadPNG.h"

#include "com_redknot_tool_NativeMethod.h"

using namespace std;

GLuint VBO;//定点缓冲区对象
GLuint IBO;

void CreateIndexBuffer()
{
    unsigned int Indices[] =
    {
        0,3,1,
        1,3,2,
        2,3,0,
        0,1,2
    };

    glGenBuffers(1,&IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(Indices),Indices,GL_STATIC_DRAW);
}

void CreateVertexBuffer()
{
    Vector3f Vertices[8];
    Vertices[0] = Vector3f(-1.0f,-1.0f,0.0f);
    Vertices[1] = Vector3f(1.0f,0.0f,0.0f);

    Vertices[2] = Vector3f(0.0f,-1.0f,1.0f);
    Vertices[3] = Vector3f(0.0f,1.0f,0.0f);

    Vertices[4] = Vector3f(1.0f,-1.0f,0.0f);
    Vertices[5] = Vector3f(0.0f,0.0f,1.0f);

    Vertices[6] = Vector3f(0.0f,1.0f,0.0f);
    Vertices[7] = Vector3f(1.0f,1.0f,1.0f);


    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices),Vertices,GL_STATIC_DRAW);
}

GLuint UniformLocation;

int screen_height;
int screen_width;

Texture * pTexture = NULL;

JNIEXPORT void JNICALL Java_com_redknot_tool_NativeMethod_initialize
  (JNIEnv * env, jclass thiz, jint width, jint height, jobject assetManager)
  {

    screen_height = height;
    screen_width = width;

    //pTexture = new Texture(GL_TEXTURE_2D,"");

    glClearColor(1.0f,1.0f,1.0f,1.0f);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    AAssetManager* g_pAssetManager = AAssetManager_fromJava(env, assetManager);

    ReadPNG r;
    string png_src = "texture.png";
    ImageData* img_res = r.FromAssetPNGFile(g_pAssetManager,png_src);

    LOG_ERROR("width: %d",img_res->img_width);
    LOG_ERROR("height: %d",img_res->img_height);

    ReadFile read = ReadFile(g_pAssetManager);

    char * vertex_shader = read.readShaderSrcFile("vertex.shader");
    char * fragment_shader = read.readShaderSrcFile("fragment.shader");

    ShaderManager shader = ShaderManager(vertex_shader,fragment_shader);

    shader.setUniformLocation(&UniformLocation);
    shader.CompileShaders();

    CreateVertexBuffer();
    CreateIndexBuffer();
  }

JNIEXPORT void JNICALL Java_com_redknot_tool_NativeMethod_drawFrame
  (JNIEnv * env, jclass thiz)
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static float scale = 0.0f;
    scale += 0.02f;

    Pipeline p;
    //p.Scale(sinf(scale * 0.1f),sinf(scale * 0.1f),sinf(scale * 0.1f));
    p.Rotate(0.0f,scale * 90.0f,0.0f);
    p.WorldPos(0.0f,0.0f,-5.0f);

    Vector3f CameraPos(0.0f,0.0f,-10.0f);
    Vector3f CameraTarget(0.0f,0.0f,-1.0f);
    Vector3f CameraUp(0.0f,1.0f,0.0f);
    p.SetCamera(CameraPos,CameraTarget,CameraUp);

    p.SetPerspectivePro(30,screen_width,screen_height,1.0f,1000.0f);

    glUniformMatrix4fv(UniformLocation,1,GL_TRUE,(const float *)p.GetTrans());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*4,0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*4,(GLvoid*)12);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);

    glDrawElements(GL_TRIANGLES,12,GL_UNSIGNED_INT,0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
  }

