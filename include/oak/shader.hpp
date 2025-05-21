#ifndef OAK_SHADER_H
#define OAK_SHADER_H

#include <oak/types.h>
#include <string>
#include <memory>
namespace oak {
    class Shader {
        public:
            static std::shared_ptr<Shader> Load(const std::string& name); 
            Shader(const std::string& vertSrc, const std::string& fragSrc);


            void bind();
            void unbind();
        private:
            u32 mID;
    };
}

#endif // OAK_SHADER_H