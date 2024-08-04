#ifndef GEOMETRYDAO_CPP
#define GEOMETRYDAO_CPP

#include <cassert>

#include "GeometryDao.h"

namespace Geometry {
    // --- -- Getters -- --- //

    // Count getters
    unsigned GeometryDao::getVerticesCount() const {
        return _vertices.size();
    }
    unsigned GeometryDao::getTrianglesVIdsCount() const {
        return _trianglesVIds.size();
    }
    unsigned GeometryDao::getTrianglesCount() const {
        return static_cast<unsigned>(_trianglesVIds.size() / 3);
    }
    unsigned GeometryDao::getNormalsCount() const {
        return _normals.size();
    }
    unsigned GeometryDao::getUVCouplesCount() const {
        return _textureCoordinates.size() / 2;
    }
    unsigned GeometryDao::getTextureCoordinatesCount() const {
        return _textureCoordinates.size();
    }
    unsigned GeometryDao::getTriangleToUVCount() const {
        return _trianglesUVIds.size();
    }

    // All elements getters
    std::span<const Vector> GeometryDao::getAllVertices() const {
        return {_vertices.data(), _vertices.size()};
    }
    std::span<const unsigned> GeometryDao::getAllTriangleVIds() const {
        return {_trianglesVIds.data(), _trianglesVIds.size()};
    }
    std::span<const Vector> GeometryDao::getAllNormals() const {
        return {_normals.data(), _normals.size()};
    }
    std::span<const float> GeometryDao::getAllTextureCoordinates() const {
        return {_textureCoordinates.data(), _textureCoordinates.size()};
    }
    std::span<const unsigned> GeometryDao::getAllTrianglesToUVIndices() const {
        return {_trianglesUVIds.data(), _trianglesUVIds.size()};
    }

    Matrix& GeometryDao::getTransform(const unsigned& i) {
        return _transforms[i];
    }



    void GeometryDao::setVertex(const unsigned& meshIndex, const unsigned& vertexIndex,
                                const float& x, const float& y, const float& z) {
        assert(meshIndex < _meshLayouts.size());
        assert(vertexIndex < _meshLayouts[meshIndex].vertexCount);
        _vertices.emplace(_vertices.begin() + _meshLayouts[meshIndex].firstVertexIndex + vertexIndex, x, y, z, 1.0f);
    }

    void GeometryDao::setNormal(const unsigned& meshIndex, const unsigned& vertexIndex,
                                const float& x, const float& y, const float& z) {
        assert(meshIndex < _meshLayouts.size());
        assert(vertexIndex < _meshLayouts[meshIndex].vertexCount);
        _normals.emplace(_normals.begin() + _meshLayouts[meshIndex].firstVertexIndex + vertexIndex, x, y, z, 0.0f);
    }

    void GeometryDao::setTextureCoordinates(const unsigned& meshIndex, const unsigned& textureCoordinatesIndex,
                                            const float& u, const float& v) {
        assert(meshIndex < _meshLayouts.size());
        assert(textureCoordinatesIndex < _meshLayouts[meshIndex].textureCoordinateCount * 2);
        _textureCoordinates.emplace(_textureCoordinates.begin() + _meshLayouts[meshIndex].firstTextureCoordinateIndex + textureCoordinatesIndex * 2, u);
        _textureCoordinates.emplace(_textureCoordinates.begin() + _meshLayouts[meshIndex].firstTextureCoordinateIndex + textureCoordinatesIndex * 2 + 1, v);
    }

    void GeometryDao::setTriangle(const unsigned& meshIndex, const unsigned& triangleIndex,
                                  const unsigned& vId1, const unsigned& vId2, const unsigned& vId3) {
        assert(meshIndex < _meshLayouts.size());
        assert(triangleIndex < _meshLayouts[meshIndex].triangleCount * 3);
        _trianglesVIds.emplace(_trianglesVIds.begin() + _meshLayouts[meshIndex].firstTriangleIndex + triangleIndex * 3, vId1);
        _trianglesVIds.emplace(_trianglesVIds.begin() + _meshLayouts[meshIndex].firstTriangleIndex + triangleIndex * 3 + 1, vId2);
        _trianglesVIds.emplace(_trianglesVIds.begin() + _meshLayouts[meshIndex].firstTriangleIndex + triangleIndex * 3 + 2, vId3);
    }

    void GeometryDao::setTriangleUVIds(const unsigned& meshIndex, const unsigned& triangleIndex,
                                       const unsigned& uvId1, const unsigned& uvId2, const unsigned& uvId3) {
        assert(meshIndex < _meshLayouts.size());
        assert(triangleIndex < _meshLayouts[meshIndex].triangleCount * 3);
        _trianglesUVIds.emplace(_trianglesUVIds.begin() + _meshLayouts[meshIndex].firstTriangleIndex + triangleIndex * 3, uvId1);
        _trianglesUVIds.emplace(_trianglesUVIds.begin() + _meshLayouts[meshIndex].firstTriangleIndex + triangleIndex * 3 + 1, uvId2);
        _trianglesUVIds.emplace(_trianglesUVIds.begin() + _meshLayouts[meshIndex].firstTriangleIndex + triangleIndex * 3 + 2, uvId3);
    }


    // todo store transform and refactor camera class.
    // todo add default perspective matrix.
    unsigned GeometryDao::addTransform(const Matrix& transform) {
        _transforms.push_back(transform);
        return _transforms.size() - 1;
    }

    unsigned GeometryDao::reserveMesh(const unsigned& vertexCount, const unsigned& textureCoordinatesCount, const unsigned& triangleCount) {
        // The next mesh should start at the end of previous mesh, which will fill up the current capacity.
        const unsigned firstVertexIndex = _vertices.capacity();
        // -- first normal index = first vertex index
        const unsigned firstTextureCoordinateIndex = _textureCoordinates.capacity();
        const unsigned firstTriangleIndex = _trianglesVIds.capacity();
        // -- first triangle to UV coordinates index = first triangle index

        _meshLayouts.emplace_back(
            firstVertexIndex,
            firstTextureCoordinateIndex,
            firstTriangleIndex,
            vertexCount,
            textureCoordinatesCount,
            triangleCount
        );

        // reserve memory for the upcoming mesh
        _vertices.reserve(firstVertexIndex + vertexCount);
        _normals.reserve(firstVertexIndex + vertexCount);
        _textureCoordinates.reserve(firstTextureCoordinateIndex + textureCoordinatesCount * 2);
        _trianglesVIds.reserve(firstTriangleIndex + triangleCount * 3);
        _trianglesUVIds.reserve(firstTriangleIndex + triangleCount * 3);

        // add default transform
        _transforms.emplace_back(Matrix::Identity());

        return _meshLayouts.size() - 1;
    }

} // Geometry

#endif // GEOMETRYDAO_CPP
