//
// Created by redknot on 8/9/16.
//

#ifndef OPENGLCPP_SHADER_H
#define OPENGLCPP_SHADER_H

#include <string>
#include <fstream>

using namespace std;

class Shader {
private:
    string shader_path;
    string shader_source;
public:
    Shader();
    Shader(string shader_path);

    bool ReadShader();
};



#endif //OPENGLCPP_SHADER_H
