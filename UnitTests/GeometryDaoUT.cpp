#include <gtest/gtest.h>
#include "GeometryDao.h"

using namespace Geometry;
using namespace std;

// --- ---- SINGLETON TESTS ---- --- //

TEST(GeometryDaoUT1_Constructor, ConstructorProtected) {
    // Try to create an instance of the class
    // This should fail to compile
    // GeometryDao dao;
}

TEST(GeometryDaoUT1_Constructor, SingletonPattern1) {
    shared_ptr<GeometryDao> gDAO1 = GeometryDao::getPtr();
    shared_ptr<GeometryDao> gDAO2 = GeometryDao::getPtr();
    EXPECT_EQ(gDAO1.get(), gDAO2.get());
}

TEST(GeometryDaoUT1_Constructor, SingletonPattern2) {
    const shared_ptr<GeometryDao> gDAO1 = GeometryDao::getPtr();
    gDAO1->_vertices.emplace_back(0, 1, 2, 3);
    const shared_ptr<GeometryDao> gDAO2 = GeometryDao::getPtr();

    const unsigned VIdsCount1 = gDAO1->getVerticesCount();
    const unsigned VIdsCount2 = gDAO2->getVerticesCount();
    EXPECT_EQ(VIdsCount1, VIdsCount2);

    Vector& vertex1 = gDAO1->_vertices[0];
    Vector& vertex2 = gDAO2->_vertices[0];
    EXPECT_EQ(vertex1.x(), vertex2.x());
    EXPECT_EQ(vertex1.y(), vertex2.y());
    EXPECT_EQ(vertex1.z(), vertex2.z());
    EXPECT_EQ(vertex1.w(), vertex2.w());
}

// --- ---- DATA ACCESS TESTS ---- --- //

TEST(GeometryDaoUT2_DataAccessing, MeshInitialization) {
    const shared_ptr<GeometryDao> gDAO = GeometryDao::getPtr();

    gDAO->reserveMesh(0,0,0);
    gDAO->reserveMesh(1,1,1);
    gDAO->reserveMesh(2,3,4);

    // Check capacity exactly fit meshes needs
    ASSERT_EQ(gDAO->_meshLayouts.size(), 3);
    ASSERT_EQ(gDAO->_vertices.capacity(), 3);
    ASSERT_EQ(gDAO->_normals.capacity(), 3);
    ASSERT_EQ(gDAO->_textureCoordinates.capacity(), 8);
    ASSERT_EQ(gDAO->_trianglesVIds.capacity(), 15);
    ASSERT_EQ(gDAO->_trianglesUVIds.capacity(), 15);

    // Check layout of first mesh
    ASSERT_EQ(gDAO->_meshLayouts[0].vertexCount, 0);
    ASSERT_EQ(gDAO->_meshLayouts[0].textureCoordinateCount, 0);
    ASSERT_EQ(gDAO->_meshLayouts[0].triangleCount, 0);
    ASSERT_EQ(gDAO->_meshLayouts[0].firstVertexIndex, 0);
    ASSERT_EQ(gDAO->_meshLayouts[0].firstTextureCoordinateIndex, 0);
    ASSERT_EQ(gDAO->_meshLayouts[0].firstTriangleIndex, 0);

    // Check layout of second mesh
    ASSERT_EQ(gDAO->_meshLayouts[1].vertexCount, 1);
    ASSERT_EQ(gDAO->_meshLayouts[1].textureCoordinateCount, 1);
    ASSERT_EQ(gDAO->_meshLayouts[1].triangleCount, 1);
    ASSERT_EQ(gDAO->_meshLayouts[1].firstVertexIndex, 0);
    ASSERT_EQ(gDAO->_meshLayouts[1].firstTextureCoordinateIndex, 0);
    ASSERT_EQ(gDAO->_meshLayouts[1].firstTriangleIndex, 0);

    // Check layout of third mesh
    ASSERT_EQ(gDAO->_meshLayouts[2].vertexCount, 2);
    ASSERT_EQ(gDAO->_meshLayouts[2].textureCoordinateCount, 3);
    ASSERT_EQ(gDAO->_meshLayouts[2].triangleCount, 4);
    ASSERT_EQ(gDAO->_meshLayouts[2].firstVertexIndex, 1);
    ASSERT_EQ(gDAO->_meshLayouts[2].firstTextureCoordinateIndex, 2);
    ASSERT_EQ(gDAO->_meshLayouts[2].firstTriangleIndex, 3);

}

TEST(GeometryDaoUT2_DataAccessing, VertexAccess) {
    const shared_ptr<GeometryDao> gDAO = GeometryDao::getPtr();
    const unsigned meshIndex = gDAO->reserveMesh(3, 0, 0);
    const array vertices = {
        Vector(0, 1, 2, 1),
        Vector(4, 5, 6, 1),
        Vector(8, 9, 10, 1)
    };
    for (unsigned short i=0; i<3; i++) {
        gDAO->setVertex(meshIndex, i, vertices[i].x(), vertices[i].y(), vertices[i].z());
    }
    EXPECT_EQ(gDAO->getVerticesCount(), 3);

    const span<const Vector> gottenVertices = gDAO->getAllVertices();
    for (unsigned short i=0; i<3; i++) {
        const Vector v = gottenVertices[i];
        EXPECT_EQ(v.x(), vertices[i].x());
        EXPECT_EQ(v.y(), vertices[i].y());
        EXPECT_EQ(v.z(), vertices[i].z());
        EXPECT_EQ(v.w(), vertices[i].w());
    }
}

TEST(GeometryDaoUT2_DataAccessing, NormalsAccess) {
    const shared_ptr<GeometryDao> gDAO = GeometryDao::getPtr();
    const unsigned meshIndex = gDAO->reserveMesh(3, 0, 0);
    const array normals = {
        Vector(0, 1, 2, 0),
        Vector(4, 5, 6, 0),
        Vector(8, 9, 10, 0)
    };
    for (unsigned short i=0; i<3; i++) {
        gDAO->setNormal(meshIndex, i, normals[i].x(), normals[i].y(), normals[i].z());
    }
    EXPECT_EQ(gDAO->getNormalsCount(), 3);

    const span<const Vector> gottenNormals = gDAO->getAllNormals();
    for (unsigned short i=0; i<3; i++) {
        const Vector n = gottenNormals[i];
        EXPECT_EQ(n.x(), normals[i].x());
        EXPECT_EQ(n.y(), normals[i].y());
        EXPECT_EQ(n.z(), normals[i].z());
        EXPECT_EQ(n.w(), normals[i].w());
    }
}

TEST(GeometryDaoUT2_DataAccessing, TextureCoordinatesAccess) {
    const shared_ptr<GeometryDao> gDAO = GeometryDao::getPtr();
    const unsigned meshIndex = gDAO->reserveMesh(0, 4, 0);
    const array<float, 8> textCoords = {1, 2, 3, 4, 5, 6, 1, 2};
    for (unsigned short i=0; i<8; i+=2) {
        gDAO->setTextureCoordinates(meshIndex, i/2, textCoords[i], textCoords[i+1]);
    }
    EXPECT_EQ(gDAO->getUVCouplesCount(), 4);

    const span<const float> gottenTextureCoordinates = gDAO->getAllTextureCoordinates();
    for (unsigned short i=0; i<8; i++) {
        EXPECT_EQ(gottenTextureCoordinates[i], textCoords[i]);
    }
}

TEST(GeometryDaoUT2_DataAccessing, TriangleVIdsAccess) {
    const shared_ptr<GeometryDao> gDAO = GeometryDao::getPtr();
    const unsigned meshIndex = gDAO->reserveMesh(0, 0, 3);
    const array<unsigned, 9> vIds = {1, 2, 3, 4, 5, 6, 1, 2, 3};
    for (unsigned short i=0; i<9; i+=3) {
        gDAO->setTriangle(meshIndex, i/3, vIds[i], vIds[i+1], vIds[i+2]);
    }
    EXPECT_EQ(gDAO->getTrianglesVIdsCount(), 9);
    EXPECT_EQ(gDAO->getTrianglesCount(), 3);

    const span<const unsigned> gottenVIds = gDAO->getAllTriangleVIds();
    for (unsigned short i=0; i<9; i++) {
        EXPECT_EQ(gottenVIds[i], vIds[i]);
    }
}

TEST(GeometryDaoUT2_DataAccessing, TriangleUVIdsAccess) {
    const shared_ptr<GeometryDao> gDAO = GeometryDao::getPtr();
    const unsigned meshIndex = gDAO->reserveMesh(0, 0, 3);
    const array<unsigned, 9> tIds = {1, 2, 3, 4, 5, 6, 1, 2, 3};
    for (unsigned short i=0; i<9; i+=3) {
        gDAO->setTriangleUVIds(meshIndex, i/3, tIds[i], tIds[i+1], tIds[i+2]);
    }
    EXPECT_EQ(gDAO->getTriangleToUVCount(), 9);

    const span<const unsigned> gottenTIds = gDAO->getAllTrianglesToUVIndices();
    for (unsigned short i=0; i<9; i++) {
        EXPECT_EQ(gottenTIds[i], tIds[i]);
    }
}

//todo camera & transforms

