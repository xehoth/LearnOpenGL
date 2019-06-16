#ifndef _LEARN_OPENGL_SHADER_H_
#define _LEARN_OPENGL_SHADER_H_
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace LearnOpenGL {
    class Shader {
       public:
        enum class ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, SHADER_PROGRAM };

        Shader(const char *vertexPath, const char *fragmentPath) {
            std::string vertexCode, fragmentCode;
            std::ifstream vFile, fFile;
            vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try {
                vFile.open(vertexPath);
                fFile.open(fragmentPath);

                std::stringstream vStream, fStream;
                vStream << vFile.rdbuf();
                fStream << fFile.rdbuf();

                vertexCode = vStream.str();
                fragmentCode = fStream.str();
            } catch (std::ifstream::failure e) {
                std::cerr << "Failed to open Shader files " << vertexPath << ' ' << fragmentPath;
                std::cerr << std::endl << e.what() << std::endl;
            }

            const char *vCode = vertexCode.c_str(), *fCode = fragmentCode.c_str();

            GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vShader, 1, &vCode, nullptr);
            glCompileShader(vShader);
            checkCompileStatus(vShader, ShaderType::VERTEX_SHADER);

            GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fShader, 1, &fCode, nullptr);
            glCompileShader(fShader);
            checkCompileStatus(fShader, ShaderType::FRAGMENT_SHADER);

            id = glCreateProgram();
            glAttachShader(id, vShader);
            glAttachShader(id, fShader);
            glLinkProgram(id);
            checkCompileStatus(id, ShaderType::SHADER_PROGRAM);

            glDeleteShader(vShader);
            glDeleteShader(fShader);
        }

        GLuint getId() const { return id; }

        void use() const { glUseProgram(id); }

        void set(const char *name, int val) const {
            glUniform1i(glGetUniformLocation(id, name), val);
        }

        void set(const char *name, float val) const {
            glUniform1f(glGetUniformLocation(id, name), val);
        }

        GLuint getUniformLocation(const char *name) const { return glGetUniformLocation(id, name); }

       private:
        GLuint id;

        void checkCompileStatus(GLuint shader, ShaderType type) {
            GLint success;
            char infoLog[1024];
            switch (type) {
                case ShaderType::VERTEX_SHADER: {
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        std::cerr << "vertex shader compile error" << std::endl
                                  << infoLog << std::endl;
                    }
                    break;
                }
                case ShaderType::FRAGMENT_SHADER: {
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                        std::cerr << "fragment shader compile error" << std::endl
                                  << infoLog << std::endl;
                    }
                    break;
                }
                case ShaderType::SHADER_PROGRAM: {
                    glGetProgramiv(shader, GL_LINK_STATUS, &success);
                    if (!success) {
                        glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                        std::cerr << "shader program link error" << std::endl
                                  << infoLog << std::endl;
                    }
                    break;
                }
            }
        }
    };
}  // namespace LearnOpenGL
#endif