#include <gtest/gtest.h>
#include "GeometryDao.h"
#include "ObjLoader.h"
#include "SettingsDao.h"

using namespace Geometry;
using namespace std;

// --- ---- SINGLETON TESTS ---- --- //

TEST(FileLoaderUT1_Constructor, ConstructorInitialisation) {
    const std::string pathStr = SettingsDao::getPtr()->programSettings().rootDir + "/../Assets/Models/Triangle.obj";
    bool success = false;
    try {
        DiskAccess::ObjLoader loader(pathStr);
        success = true;
    } catch (runtime_error& e) {cout<<e.what()<<endl;}
    catch (invalid_argument& ia) {cout<<ia.what()<<endl;}
    EXPECT_TRUE(success);
}

TEST(FileLoaderUT2_Loading, SingleMeshLoadingTriangle) {
    const shared_ptr<GeometryDao> gDao = GeometryDao::getPtr();
    const std::string pathStr = SettingsDao::getPtr()->programSettings().rootDir + "/../Assets/Models/Triangle.obj";
    DiskAccess::ObjLoader loader(pathStr);
    loader.load();
    ASSERT_EQ(gDao->getVerticesCount(), 3);
    ASSERT_EQ(gDao->getNormalsCount(), 3);
    ASSERT_EQ(gDao->getTextureCoordinatesCount(), 6);
    ASSERT_EQ(gDao->getTrianglesVIdsCount(), 3);
    ASSERT_EQ(gDao->getTriangleToUVCount(), 3);
}

TEST(FileLoaderUT2_Loading, SingleMeshLoadingCube) {
    const shared_ptr<GeometryDao> gDao = GeometryDao::getPtr();
    const std::string pathStr = SettingsDao::getPtr()->programSettings().rootDir + "/../Assets/Models/Cube.obj";
    DiskAccess::ObjLoader loader(pathStr);
    loader.load();
    ASSERT_EQ(gDao->getVerticesCount(), 8);
    ASSERT_EQ(gDao->getNormalsCount(), 8);
    ASSERT_EQ(gDao->getTextureCoordinatesCount(), 28);
    ASSERT_EQ(gDao->getTrianglesVIdsCount(), 36);
    ASSERT_EQ(gDao->getTriangleToUVCount(), 36);
}

TEST(FileLoaderUT2_Loading, MultipleMeshLoading) {
    const shared_ptr<GeometryDao> gDao = GeometryDao::getPtr();
    const std::string pathStr = SettingsDao::getPtr()->programSettings().rootDir + "/../UnitTests/TestAssets/MultipleObjFile.obj";
    DiskAccess::ObjLoader loader(pathStr);
    loader.load();
    ASSERT_EQ(gDao->getVerticesCount(), 48);
    ASSERT_EQ(gDao->getNormalsCount(), 48);
    ASSERT_EQ(gDao->getTextureCoordinatesCount(), 168);
    ASSERT_EQ(gDao->getTrianglesVIdsCount(), 216);
    ASSERT_EQ(gDao->getTriangleToUVCount(), 216);
}