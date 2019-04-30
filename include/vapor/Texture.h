#pragma once

#include <vapor/NonCopyableMixin.h>

namespace VAPoR {

class Framebuffer;

class Texture : private NonCopyableMixin {
protected:
    unsigned int       _id = 0;
    unsigned int       _width = 0;
    unsigned int       _height = 0;
    unsigned int       _depth = 0;
    const unsigned int _type;
    const unsigned int _nDims;

public:
    ~Texture();
    int  Generate();
    int  Generate(int filter);
    void Delete();
    bool Initialized() const;
    void Bind() const;
    void UnBind() const;
    int  TexImage(int internalFormat, int width, int height, int depth, unsigned int format, unsigned int type, const void *data, int level = 0);

    static unsigned int GetDimsCount(unsigned int glTextureEnum);

protected:
    Texture(unsigned int type);

    friend class Framebuffer;
};

class Texture1D : public Texture {
public:
    Texture1D();
};
class Texture2D : public Texture {
public:
    Texture2D();
    void CopyDepthBuffer();
};
class Texture3D : public Texture {
public:
    Texture3D();
};
class Texture2DArray : public Texture {
public:
    Texture2DArray();
};
};    // namespace VAPoR
