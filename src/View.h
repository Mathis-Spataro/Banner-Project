#ifndef VIEW_H
#define VIEW_H

#include <glew.h>   // needed for glfw3
#include <glfw3.h>
#include <memory>
#include "Renderer.h"
#include "Camera.h"

namespace Geometry
{
    class GeometryDao;
    class Color;
}

class View
{
public:
    explicit View(Geometry::Camera& camera);
    ~View();

    void start() const;
    void update() const;

protected:
    Geometry::Camera& _camera;
    GLFWwindow* _window;
    std::unique_ptr<Renderer> _renderer;

};



#endif //VIEW_H

