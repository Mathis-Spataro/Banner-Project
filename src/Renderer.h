#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"

class Renderer {
public:
    Renderer() = default;
    virtual ~Renderer() = default;
    virtual void render(Geometry::Camera& camera) {}
};

#endif //RENDERER_H
