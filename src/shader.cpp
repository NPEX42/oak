#include <oak/shader.hpp>
#include <glad/glad.h>

#include <oak/utils.hpp>

#define MAX_INFO_LOG (1024)
namespace oak {
    Shader::Shader(const std::string& vertSrc, const std::string& fragSrc) : mID(0) {
        u32 vertID, fragID;
        vertID = glCreateShader(GL_VERTEX_SHADER);
        fragID = glCreateShader(GL_FRAGMENT_SHADER);
        mID = glCreateProgram();

        const char* _vertSrc = vertSrc.c_str();
        const char* _fragSrc = fragSrc.c_str();


        glShaderSource(vertID, 1, &_vertSrc, NULL);
        glShaderSource(fragID, 1, &_fragSrc, NULL);

        glCompileShader(vertID);
        i32 status = 0;
        glGetShaderiv(vertID, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            char log[MAX_INFO_LOG];
            glGetShaderInfoLog(vertID, MAX_INFO_LOG, NULL, log);
            printf("Failed To Compile Vertex Shader: \n\t%s\n", log);
            printf("Vert Source: %s", _vertSrc);
            glDeleteShader(vertID);
            glDeleteShader(fragID);
            throw std::exception();
        }

        glCompileShader(fragID);
        glGetShaderiv(fragID, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            char log[MAX_INFO_LOG];
            glGetShaderInfoLog(fragID, MAX_INFO_LOG, NULL, log);
            printf("Failed To Compile Fragment Shader: \n\t%s\n", log);
            printf("Frag Source: %s", _fragSrc);
            glDeleteShader(vertID);
            glDeleteShader(fragID);
            throw std::exception();
        }

        glAttachShader(mID, vertID);
        glAttachShader(mID, fragID);

        glLinkProgram(mID);

        glDetachShader(mID, vertID);
        glDetachShader(mID, fragID);

        glDeleteShader(vertID);
        glDeleteShader(fragID);
    }

    std::shared_ptr<Shader> Shader::Load(const std::string& name) {
        std::string vertPath = name + ".vert";
        std::string fragPath = name + ".frag";

        auto vertSrc = oak::ReadString(vertPath);
        auto fragSrc = oak::ReadString(fragPath);

        return std::make_shared<Shader>(vertSrc, fragSrc);
    }

    void Shader::bind() {glUseProgram(mID);}
    void Shader::unbind() {glUseProgram(0);}
}