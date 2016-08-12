//
// Created by redknot on 8/12/16.
//

#ifndef OPENGLCPP_SHADERMANAGER_H
#define OPENGLCPP_SHADERMANAGER_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>

#include "LOG/logger.h"

class ShaderManager {
private:
    void AddShader(GLuint ShadlerProgram, const char* shaderText,GLenum shaderType);
    char * vertex_shader;
    char * fragment_shader;

    GLuint * UniformLocation;
public:
    ShaderManager(char * _vertex_shader,char * _fragment_shader);
    void setUniformLocation(GLuint * _UniformLocation);
    void CompileShaders();
};



#endif //OPENGLCPP_SHADERMANAGER_H
