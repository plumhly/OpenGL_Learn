//
//  Shader.hpp
//  OpenGL_Ex
//
//  Created by Plum on 2021/12/22.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader {
public:
    // 程序id
    unsigned int ID;
    
    // 构造器读取着色器
    Shader(const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath);
    
    // 使用
    void use();
    
    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMatrix4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &vec) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif /* Shader_hpp */
