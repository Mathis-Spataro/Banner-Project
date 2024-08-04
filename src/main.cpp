#include <cassert>

#include "SettingsDao.h"
#include "GeometryDao.h"
#include "View.h"
#include "ObjLoader.h"
#include "Camera.h"

using namespace std;
using namespace Geometry;

int main() {
    const shared_ptr<GeometryDao> gDao = GeometryDao::getPtr();
    DiskAccess::ObjLoader loader("../../../Assets/Models/Cube.obj");
    const bool success = loader.load();
    assert(success);

    unsigned transformIndex = gDao->addTransform(Matrix::Translation(0, 0, 3));
    GraphicsSettings gs; // dev
    Camera c(transformIndex, gs.fov, gs.near, gs.far);

    const View v1(c);
    v1.start();

    return 0;
}
