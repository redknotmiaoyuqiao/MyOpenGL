//
// Created by redknot on 8/12/16.
//

#ifndef OPENGLCPP_SHADERMANAGER_H
#define OPENGLCPP_SHADERMANAGER_H

#include <EGL/egl.h>
#include <GLES3/gl3.h>

#include "LOG/logger.h"

class ShaderManager {
private:
    void AddShader(GLuint ShadlerProgram, const char* shaderText,GLenum shaderType);
    char * vertex_shader;
    char * fragment_shader;

    GLuint * UniformLocation;
    GLuint * SamplerLocation;
public:
    ShaderManager(char * _vertex_shader,char * _fragment_shader);
    void setUniformLocation(GLuint * _UniformLocation);
    void setSamplerLocation(GLuint * _SamplerLocation);
    void CompileShaders();
};



#endif //OPENGLCPP_SHADERMANAGER_H
