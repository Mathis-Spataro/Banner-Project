#include <gtest/gtest.h>
#include <filesystem>
#include "DiskUtilities.h"
#include "ObjParser.h"
#include "SettingsDao.h"

// --------- ObjParserLoader UT ---------- //
/*
TEST(ObjParserLoaderUT, Counting) {
    // init
    ObjParser loader;
    unsigned vertexCount = 0, triangleCount = 0;

    // one triangle test
    std::string pathStr = SettingsDao::getPtr()->programSettings().assets_dir + "/Models/Triangle.obj";
    string dummy;
    loader.iss = istringstream(DiskDao::TryReadFileAsString(pathStr));
    while (dummy != "o") {
        loader.iss >> dummy;
    }
    loader._countVerticesAndTriangles(vertexCount, triangleCount);
    EXPECT_EQ(vertexCount, 3);
    EXPECT_EQ(triangleCount, 1);

    // cube test
    vertexCount = 0; triangleCount = 0;
    pathStr = SettingsDao::getPtr()->programSettings().assets_dir + "/Models/Cube.obj";
    dummy = "";
    loader.iss = istringstream(DiskDao::TryReadFileAsString(pathStr));
    while (dummy != "o") {
        loader.iss >> dummy;
    }
    loader._countVerticesAndTriangles(vertexCount, triangleCount);
    EXPECT_EQ(vertexCount, 8);
    EXPECT_EQ(triangleCount, 12);
}


///

TEST(DiskDaoUT1_LoadOBJ, OneTriangle) {
    const shared_ptr<Geometry::GeometryDao> gDAO = Geometry::GeometryDao::getPtr();
    const std::string pathStr = SettingsDao::getPtr()->programSettings().assets_dir + "/Models/Triangle.obj";
    const bool loadSuccess = DiskDao::loadObjFile(pathStr);

    EXPECT_EQ(loadSuccess, true);
    EXPECT_EQ(gDAO->getVerticesCount(), 3);
    EXPECT_EQ(gDAO->getTrianglesVIdsCount(), 3);
    EXPECT_EQ(gDAO->getTrianglesCount(), 1);
    EXPECT_EQ(gDAO->getVColorsCount(), 3);

}

TEST(DiskDaoUT1_LoadOBJ, Cube) {
    const shared_ptr<Geometry::GeometryDao> gDAO = Geometry::GeometryDao::getPtr();
    const std::string pathStr = SettingsDao::getPtr()->programSettings().assets_dir + "/Models/Cube.obj";
    const bool loadSuccess = DiskDao::loadObjFile(pathStr);

    EXPECT_EQ(loadSuccess, true);
    EXPECT_EQ(gDAO->getVerticesCount(), 8);
    EXPECT_EQ(gDAO->getTrianglesVIdsCount(), 12*3);
    EXPECT_EQ(gDAO->getTrianglesCount(), 12);
    EXPECT_EQ(gDAO->getVColorsCount(), 8);

}
*/
