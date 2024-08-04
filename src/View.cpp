#ifndef VIEW_CPP
#define VIEW_CPP

#include <iostream>
#include <cassert>
#include "View.h"
#include "SettingsDao.h"
#include "GlRenderer.h"

    View::View(Geometry::Camera& camera) : _camera(camera) {
        // Initialize glfw
        bool glfw_init_successful = glfwInit();
        assert(glfw_init_successful);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _window = glfwCreateWindow(800, 600, "Bruce Banner", nullptr, nullptr);
        assert(_window);

        glfwMakeContextCurrent(_window);
        bool glfw_context_init_successful = glfwGetCurrentContext();
        assert(glfw_context_init_successful);

        // Create and attach a renderer
        if (SettingsDao::getPtr()->graphicsSettings().raytracing) {
            // todo
        } else {
            _renderer = std::make_unique<GlRenderer>();
        }
    }

    View::~View() {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }

    void View::start() const {
        // Loop until the user closes the window
        while (!glfwWindowShouldClose(_window)) {
            update();
        }
    }

    void View::update() const {
        _renderer->render(_camera);
        glfwSwapBuffers(_window);
        glfwPollEvents();

        // dev, until event system, prototype
        float angleY = 0.0f, angleX = 0.0f;
        bool updateCamera = false;
        if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            angleY += M_PI/800;
            updateCamera = true;
        }
        if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            angleY -= M_PI/800;
            updateCamera = true;
        }
        if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) {
            angleX += M_PI/800;
            updateCamera = true;
        }
        if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            angleX -= M_PI/800;
            updateCamera = true;
        }
        if (updateCamera) {
            Geometry::Matrix& camTransform = _camera.getTransform();
            const Geometry::Matrix cameraRotationY = Geometry::Matrix::RotationY(angleY);
            const Geometry::Matrix cameraRotationX = Geometry::Matrix::RotationX(angleX);
            camTransform = cameraRotationY * cameraRotationX * camTransform;
        }
    }


#endif //VIEW_CPP
