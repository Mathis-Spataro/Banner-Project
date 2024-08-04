#ifndef CAMERA_H
#define CAMERA_H

#include "GeometryDao.h"
#include "Matrix.h"

namespace Geometry {

	class Camera {
	public:
    	Camera() = delete;
    	Camera(const unsigned& transformIndex, const Matrix& perspectiveMat4)
			: perspectiveProj(perspectiveMat4), _transformIndex(transformIndex) {}
		Camera(const unsigned& transformIndex, const float& fov, const float& zNear, const float& zFar)
			: perspectiveProj(Matrix::Perspective(fov, zNear, zFar)), _transformIndex(transformIndex) {}
		Camera(const Camera& other) = default;

		Matrix& getTransform() {
			return GeometryDao::getPtr()->getTransform(_transformIndex);
		}
		Matrix perspectiveProj;
	protected:
		unsigned _transformIndex;
	};

} // Geometry


#endif //CAMERA_H
