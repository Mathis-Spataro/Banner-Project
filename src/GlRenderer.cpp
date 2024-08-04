#ifndef GLRENDERER_CPP
#define GLRENDERER_CPP
#include <cassert>
#include <fstream>
#include <memory>
#include <iostream>

#include "GeometryDao.h"
#include "GlRenderer.h"
#include "DiskUtilities.h"

GlRenderer::GlRenderer() {
    vaoId = positionVboId = colorVboId = eboId = vertexShaderId = fragmentShaderId = shaderProgramId = INT_MAX;
    _scene = Geometry::GeometryDao::getPtr();
    const GLenum glewStatus = glewInit();
    assert(glewStatus == GLEW_OK);
    const bool shaderLoadingSuccessful = loadShaders(
        "../../../Assets/Shaders/VS_toClipSpaceColorPassthrough.glsl",
        "../../../Assets/Shaders/FS_plainWhite.glsl"
    );
    assert(shaderLoadingSuccessful);
    assert(vertexShaderId != INT_MAX);
    assert(fragmentShaderId != INT_MAX);
    assert(shaderProgramId != INT_MAX);
    // Init buffers
    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &positionVboId);
    glGenBuffers(1, &colorVboId);
    glGenBuffers(1, &eboId);
    assert(vaoId != INT_MAX);
    assert(positionVboId != INT_MAX);
    assert(colorVboId != INT_MAX);
    assert(eboId != INT_MAX);
}

GlRenderer::~GlRenderer()
{
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &positionVboId);
    glDeleteBuffers(1, &eboId);

    glDeleteProgram(vertexShaderId);
    glDeleteProgram(fragmentShaderId);
    glDeleteProgram(shaderProgramId);

    glBindVertexArray(0);
}

void GlRenderer::render(Geometry::Camera& camera) {
    const std::shared_ptr<Geometry::GeometryDao> gDAO = Geometry::GeometryDao::getPtr();
    glUseProgram(shaderProgramId);
    if(need_update) {
        updateBuffers();
        need_update = false;
    }
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vaoId);

    // Uniforms
    const Geometry::Matrix& perspectiveMatrix = camera.perspectiveProj;
    Geometry::Matrix& cameraTransform = camera.getTransform();
    const Geometry::Matrix mvp = perspectiveMatrix * cameraTransform.Inverse();
    const GLchar* uniformName = "mvpMatrix";
    GLint mvpMatrixLocation = glGetUniformLocation(shaderProgramId, uniformName);
    glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvp.data[0]);

    glDrawElements(GL_TRIANGLES, gDAO->getTrianglesVIdsCount(), GL_UNSIGNED_INT, nullptr);
}

void GlRenderer::updateBuffers() const {
    const std::span<const Geometry::Vector> vertices = _scene->getAllVertices();
    const std::span<const unsigned> trianglesVIds = _scene->getAllTriangleVIds();

    glBindVertexArray(vaoId);

    // Position vbo
    glBindBuffer(GL_ARRAY_BUFFER, positionVboId);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size() * sizeof(Geometry::Vector)),
        vertices.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vector), nullptr);
    glEnableVertexAttribArray(0);

    // Color vbo
    /*glBindBuffer(GL_ARRAY_BUFFER, colorVboId);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(colors.size() * sizeof(Geometry::Color)),
        colors.data(),
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Geometry::Color), nullptr);
    glEnableVertexAttribArray(3);*/

    // Ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(trianglesVIds.size() * sizeof(unsigned int)),
        trianglesVIds.data(),
        GL_STATIC_DRAW
    );

    glBindVertexArray(0);

}

bool GlRenderer::loadShaders(const std::string& pathToVertexShaderFile, const std::string& pathToFragmentShaderFile)
{
    // Read and compile vertex shader
    const std::string vertexShaderSourceString = DiskAccess::Utilities::TryReadFileAsString(pathToVertexShaderFile);
    const GLchar* vertexShaderSource = vertexShaderSourceString.c_str();
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderId);

    // Read and compile fragment shader
    const std::string fragmentShaderSourceString = DiskAccess::Utilities::TryReadFileAsString(pathToFragmentShaderFile);
    const GLchar* fragmentShaderSource = fragmentShaderSourceString.c_str();
        fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId); // Compile the fragment shader

    // Create a program and attach the shaders
    shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    // Detach program components.
    glDetachShader(shaderProgramId, vertexShaderId);
    glDetachShader(shaderProgramId, fragmentShaderId);

    return checkShaderCompileErrors();
}

bool GlRenderer::checkShaderCompileErrors() const {
    GLint success, maxLength;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar infoLog[maxLength];
        glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar infoLog[maxLength];
        glGetShaderInfoLog(fragmentShaderId, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetProgramiv(shaderProgramId, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramiv(shaderProgramId, GL_INFO_LOG_LENGTH, &maxLength);
        GLchar infoLog[maxLength];
        glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
        std::cerr << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return success;
}



#endif //GLRENDERER_CPP
