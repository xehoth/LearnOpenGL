#ifndef _LEARN_OPENGL_IMAGE_H_
#define _LEARN_OPENGL_IMAGE_H_
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

namespace LearnOpenGL {
    class Image {
       public:
        Image() : d(), width(), height(), channels() {}
        Image(const char *file, bool flip = true) : d(), width(), height(), channels() {
            load(file, flip);
        }

        Image(const Image &) = delete;
        Image &operator=(const Image &) = delete;
        Image(Image &&o) {
            if (o.d) {
                d = o.d;
                o.d = nullptr;
                width = o.width;
                o.width = 0;
                height = o.height;
                o.height = 0;
                channels = o.channels;
                o.channels = 0;
            }
        }

        Image &operator=(Image &&o) {
            if (o.d) {
                d = o.d;
                o.d = nullptr;
                width = o.width;
                o.width = 0;
                height = o.height;
                o.height = 0;
                channels = o.channels;
                o.channels = 0;
            }
        }

        stbi_uc *get() const { return d; }

        void load(const char *file, bool flip = true) {
            if (d) release();
            stbi_set_flip_vertically_on_load(flip);
            d = stbi_load(file, &width, &height, &channels, 0);
        }

        void release() const { stbi_image_free(d); }

        int getWidth() const { return width; }

        int getHeight() const { return height; }

        int getChannels() const { return channels; }
        ~Image() {
            if (d) release();
        }

        bool genTexImage2D(GLint internalFormat, GLenum format, GLenum type) const {
            if (d) {
                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, d);
                return true;
            }
            std::cerr << "Failed to load texture" << std::endl;
            return false;
        }

       private:
        stbi_uc *d;
        int width, height, channels;
    };
}  // namespace LearnOpenGL
#endif