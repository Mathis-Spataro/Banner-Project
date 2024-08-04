#ifndef GLRENDERER_H
#define GLRENDERER_H
#include <glew.h>
#include "Renderer.h"

class GlRenderer final : public Renderer
{
public:
    GlRenderer();

    ~GlRenderer() override;

    void render(Geometry::Camera& camera) override;

    void updateBuffers() const;

    bool loadShaders(const std::string& pathToVertexShaderFile, const std::string& pathToFragmentShaderFile);

protected:
    std::shared_ptr<Geometry::GeometryDao> _scene;
    GLuint vertexShaderId, fragmentShaderId, shaderProgramId;
    GLuint vaoId, positionVboId, colorVboId, eboId;
    bool need_update = true; // dev, until event system

    [[nodiscard ]] bool checkShaderCompileErrors() const;
};


#endif //GLRENDERER_H
