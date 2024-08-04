#ifndef GEOMETRYDAO_H
#define GEOMETRYDAO_H

#include <memory>
#include <vector>
#include <span>

#include "Matrix.h"
#include "Vector.h"

namespace Geometry {
    class GeometryDao { // Singleton
    public :
        // --- -- Constructor -- --- //
        GeometryDao(const GeometryDao&) = delete;
        void operator=(const GeometryDao&) = delete;
        static std::shared_ptr<GeometryDao> getPtr() {
            static std::shared_ptr<GeometryDao> instance(new GeometryDao);
            return instance;
        }

        // --- -- Getters -- --- //

        [[nodiscard]] unsigned getVerticesCount() const;
        [[nodiscard]] unsigned getTrianglesVIdsCount() const;
        [[nodiscard]] unsigned getTrianglesCount() const;
        [[nodiscard]] unsigned getNormalsCount() const;
        [[nodiscard]] unsigned getUVCouplesCount() const;
        [[nodiscard]] unsigned getTextureCoordinatesCount() const;  // more explanatory name needed
        [[nodiscard]] unsigned getTriangleToUVCount() const;

        [[nodiscard]] std::span<const Vector> getAllVertices() const;
        [[nodiscard]] std::span<const unsigned> getAllTriangleVIds() const;
        [[nodiscard]] std::span<const Vector> getAllNormals() const;
        [[nodiscard]] std::span<const float> getAllTextureCoordinates() const;
        [[nodiscard]] std::span<const unsigned> getAllTrianglesToUVIndices() const;

        [[nodiscard]] Matrix& getTransform(const unsigned& i);

        // --- -- Setters -- --- //

        void setVertex(const unsigned& meshIndex, const unsigned& vertexIndex,
                       const float& x, const float& y, const float& z);
        void setNormal(const unsigned& meshIndex, const unsigned& vertexIndex,
                       const float& x, const float& y, const float& z);
        void setTextureCoordinates(const unsigned& meshIndex, const unsigned& textureCoordinatesIndex,
                                   const float& u, const float& v);
        void setTriangle(const unsigned& meshIndex, const unsigned& triangleIndex,
                         const unsigned& vId1, const unsigned& vId2, const unsigned& vId3);
        void setTriangleUVIds(const unsigned& meshIndex, const unsigned& triangleIndex,
                              const unsigned& uvId1, const unsigned& uvId2, const unsigned& uvId3);

        unsigned addTransform(const Matrix& transform);

        unsigned reserveMesh(const unsigned& vertexCount, const unsigned& textureCoordinatesCount, const unsigned& triangleCount);

#ifndef TEST_MODE
    protected:
#endif
        GeometryDao() = default;
        struct MeshLayout {
            unsigned firstVertexIndex{}, firstTextureCoordinateIndex{}, firstTriangleIndex{};
            unsigned vertexCount{}, textureCoordinateCount{}, triangleCount{};
        };

        // ---- --- Data --- ---- //
        std::vector<Vector> _vertices{};          // layout location 0
        std::vector<Vector> _normals{};           // layout location 1
        std::vector<float> _textureCoordinates{}; // layout location 2
        std::vector<unsigned> _trianglesVIds{};
        std::vector<unsigned> _trianglesUVIds{};
        std::vector<Matrix> _transforms{};

        std::vector<MeshLayout> _meshLayouts{};

    }; // GeometryDAO

} // Geometry



#endif //GEOMETRYDAO_H
