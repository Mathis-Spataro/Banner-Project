#include <gtest/gtest.h>
#include "ObjParser.h"
#include "SettingsDao.h"

TEST(ObjParserLoaderUT1_Init, TriangleAndCube) {
    string path = SettingsDao::getPtr()->programSettings().rootDir + "/../Assets/Models/Triangle.obj";
    DiskAccess::ObjParser objParser1(path);
    DiskAccess::ObjParser::MeshDescription description1 = objParser1.getMeshDescription(0);
    EXPECT_EQ(description1.vertexCount, 3);
    EXPECT_EQ(description1.trianglesCount, 1);
    EXPECT_EQ(description1.textCoordCount, 3);
    EXPECT_EQ(description1.materialsCount, 0);
    EXPECT_EQ(description1.positionInFile, 15);

    path = SettingsDao::getPtr()->programSettings().rootDir + "/../Assets/Models/Cube.obj";
    DiskAccess::ObjParser objParser2(path);
    DiskAccess::ObjParser::MeshDescription description2 = objParser2.getMeshDescription(0);
    EXPECT_EQ(description2.vertexCount, 8);
    EXPECT_EQ(description2.trianglesCount, 12);
    EXPECT_EQ(description2.textCoordCount, 14);
    EXPECT_EQ(description2.materialsCount, 0);
    EXPECT_EQ(description2.positionInFile, 11);
}

// if multithreading added, add a test with a small buffer instead.
TEST(ObjParserLoaderUT1_Init, MultipleObjFile) {
    string path = SettingsDao::getPtr()->programSettings().rootDir + "/../UnitTests/TestAssets/MultipleObjFile.obj";
    DiskAccess::ObjParser objParser1(path);
    vector<DiskAccess::ObjParser::MeshDescription> descriptions = objParser1.getAllMeshDescriptions();
    EXPECT_EQ(descriptions.size(), 6);
    constexpr unsigned positions[6] = {41, 760, 1478, 2196, 2915, 3635};
    for(int i=0; i<descriptions.size(); i++) {
        EXPECT_EQ(descriptions[i].vertexCount, 8);
        EXPECT_EQ(descriptions[i].trianglesCount, 12);
        EXPECT_EQ(descriptions[i].textCoordCount, 14);
        EXPECT_EQ(descriptions[i].materialsCount, 0);
        EXPECT_EQ(descriptions[i].positionInFile, positions[i]);
    }
}

TEST(ObjParserLoaderUT2_Access, GetLine) {
    const string expectedContent[11] = {
        "o triangle",
        "v  -0.5  -0.5  -1.0",
        "v  0.5  -0.5  -1.0",
        "v  -0  0.5  -1.0",
        "vt 0 1",
        "vt 1 1",
        "vt 0.5 0",
        "vn 0 0 1",
        "vn 0 0 1",
        "vn 0 0 1",
        "f  1/1  2/1  3/1",
    };
    const string path = SettingsDao::getPtr()->programSettings().rootDir + "/../Assets/Models/Triangle.obj";
    DiskAccess::ObjParser objParser(path, 50); // 50 bytes so 50 chars
    unsigned short i = 0;
    while (!objParser.eof()) {
        string line = objParser._getNextValidLine();
        EXPECT_EQ(line, expectedContent[i]);
        i++;
    }
}

