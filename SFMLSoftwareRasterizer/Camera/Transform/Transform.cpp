#include "Transform.h"

namespace TD
{
	Transform::Transform(const Vec3d & translation, const Vec3d & rotation, const Vec3d & scale, const RotationOrder & order) : rotationOrder(order)
	{
		transformM = asScaleMatrix(scale) *  asRotationMatrix(rotation, rotationOrder) * asTranslationMatrix(translation);
		transformMInverse = asTranslationMatrix(-translation) *  asRotationMatrix(-rotation, reversedOrder(rotationOrder)) * asScaleMatrix(1. / scale);
	}
	void Transform::rotate(const Vec3d & rotation, RotationOrder order)
	{
		if (order == RotationOrder::Current)
			order = rotationOrder;

		transformM = transformM * asRotationMatrix(rotation, order);
		transformMInverse = transformMInverse * asRotationMatrix(-rotation, reversedOrder(order));
	}

	void Transform::translate(const Vec3d & translation)
	{
		transformM = transformM * asTranslationMatrix(translation);
		transformMInverse = transformMInverse * asTranslationMatrix(-translation) ;
	}

	void Transform::scale(const Vec3d & scale)
	{
		transformM = transformM * asScaleMatrix(scale);
		transformMInverse = transformMInverse * asScaleMatrix(1. / scale);
	}

	Vec3d Transform::getRightVector() const
	{
		return Vec3d(transformM(0, 0), transformM(1, 0), transformM(2, 0)).normalized();
	}

	Vec3d Transform::getUpVector() const
	{
		return Vec3d(transformM(0, 1), transformM(1, 1), transformM(2, 1)).normalized();
	}

	Vec3d Transform::getForwardVector() const
	{
		return Vec3d(transformM(0, 2), transformM(1, 2), transformM(2, 2)).normalized();
	}

	Matrix Transform::getMatrix() const
	{
		return transformM;
	}

	Matrix Transform::getMatrixInverse() const
	{
		return transformMInverse;
	}

	Transform::RotationOrder Transform::getRotationOrder() const
	{
		return rotationOrder;
	}

	void Transform::setRotationOrder(const Transform::RotationOrder & order)
	{
		if (order != RotationOrder::Current)
			rotationOrder = order;
	}

	// static:

	Matrix Transform::asScaleMatrix(const Vec3d & scale)
	{
		static Matrix scaleM;
		scaleM(0, 0) = scale.x;
		scaleM(1, 1) = scale.y;
		scaleM(2, 2) = scale.z;
		return scaleM;
	}

	Matrix Transform::asTranslationMatrix(const Vec3d & translation)
	{
		static Matrix translationM;
		translationM(3, 0) = translation.x;
		translationM(3, 1) = translation.y;
		translationM(3, 2) = translation.z;
		return translationM;
	}

	Transform::RotationOrder Transform::reversedOrder(const RotationOrder & order)
	{
		return RotationOrder(!uint8_t(order));
	}

	Matrix Transform::asRotationMatrix(const Vec3d & rotation, RotationOrder order)
	{
		static Matrix pitch;
		static Matrix yaw;
		static Matrix roll;

		if (rotation.x)
		{
			pitch(1, 1) = cos(rotation.x);
			pitch(1, 2) = sin(rotation.x);
			pitch(2, 1) = -sin(rotation.x);
			pitch(2, 2) = cos(rotation.x);
		}
		else
			pitch = Matrix::identityMatrix;
		if (rotation.y)
		{
			yaw(0, 0) = cos(rotation.y);
			yaw(0, 2) = -sin(rotation.y);
			yaw(2, 0) = sin(rotation.y);
			yaw(2, 2) = cos(rotation.y);
		}
		else
			yaw = Matrix::identityMatrix;
		if (rotation.z)
		{
			roll(0, 0) = cos(rotation.z);
			roll(0, 1) = sin(rotation.z);
			roll(1, 0) = -sin(rotation.z);
			roll(1, 1) = cos(rotation.z);
		}
		else
			roll = Matrix::identityMatrix;

		if (order == RotationOrder::XYZ || order == RotationOrder::Current)
			return roll * yaw * pitch;
		else //ZYX
			return pitch * yaw * roll;

	}

	double toRadians(double degrees)
	{
		return 3.14159265359 / 180.0 * degrees;
	}
}