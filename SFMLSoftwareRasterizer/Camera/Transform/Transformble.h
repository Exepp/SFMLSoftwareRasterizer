#pragma once
#include "Transform.h"

namespace TD
{
	class Transformble
	{
	public:

		void moveInLocal	 (const Vec3d & moveVector);
		void moveInGlobal	 (const Vec3d & moveVector);
		void setPosition	 (const Vec3d & newPosition);
		
		//void rotateInLocal	 (const Vec3d & rotation);
		void rotateInGlobal	 (const Vec3d & rotation);
		void setRotation	 (const Vec3d & newRotation);

		void scaleInLocal	 (const Vec3d & scale);
		void scaleInGlobal	 (const Vec3d & scale);
		void setScale		 (const Vec3d & newScale);

		void setRotationOrder(const Transform::RotationOrder & order);

		Vec3d						getPosition() const;
		Vec3d						getRotation() const;
		Vec3d						getScale() const;
		Transform::RotationOrder	getRotationOrder() const;
		Transform					getTransform() const;

	private:
		Vec3d rotation;
		Vec3d translation;
		Vec3d scale = Vec3d::oneVector;

		Transform transform;
	};
}

