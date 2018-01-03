#pragma once
#include "Utilities/Matrix.h"
#include "Utilities\Vec.h"

namespace TD
{
	class Transform
	{
	public:

		enum class RotationOrder : uint8_t {XYZ, ZYX, Current};

		Transform() = default;
		Transform(const Vec3d & translation, const Vec3d & rotation, const Vec3d & scale, const RotationOrder & order);

		void rotate(const Vec3d & rotation, RotationOrder order = RotationOrder::Current);
		void scale(const Vec3d & scale);
		void translate(const Vec3d & translation);

		void setRotationOrder(const Transform::RotationOrder & order);

		Vec3d		getRightVector() const;
		Vec3d		getUpVector() const;
		Vec3d		getForwardVector() const;
		Matrix		getMatrix() const;
		Matrix		getMatrixInverse() const;

		Transform::RotationOrder getRotationOrder() const;

		static Matrix					asScaleMatrix(const Vec3d & scale);
		static Matrix					asRotationMatrix(const Vec3d & rotation, RotationOrder order = RotationOrder::XYZ);
		static Matrix					asTranslationMatrix(const Vec3d & translation);
		static Transform::RotationOrder reversedOrder(const RotationOrder & order);

	private:
		RotationOrder rotationOrder = RotationOrder::XYZ;

		Matrix transformM;
		Matrix transformMInverse;
	};


	double toRadians(double degrees);
}
