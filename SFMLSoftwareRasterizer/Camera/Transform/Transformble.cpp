#include "Transformble.h"

void TD::Transformble::moveInLocal(const Vec3d & moveVector)
{
	setPosition(translation + moveVector * Transform::asRotationMatrix(rotation, transform.getRotationOrder()));
}

void TD::Transformble::moveInGlobal(const Vec3d & moveVector)
{
	setPosition(translation + moveVector);
}

void TD::Transformble::setPosition(const Vec3d & newPosition)
{
	transform.translate(-translation);
	translation = newPosition;
	transform.translate(translation);
}

//void TD::Transformble::rotateInLocal(const Vec3d & rotation)
//{
//	
//}

void TD::Transformble::rotateInGlobal(const Vec3d & rotation)
{
	setRotation(this->rotation + rotation);
}

void TD::Transformble::setRotation(const Vec3d & newRotation)
{
	transform.rotate(-rotation, Transform::reversedOrder(transform.getRotationOrder()));
	rotation = newRotation;
	transform.rotate(newRotation);
}

void TD::Transformble::scaleInLocal(const TD::Vec3d & scale)
{
	setScale(this->scale + scale * Transform::asRotationMatrix(rotation, transform.getRotationOrder()));
}

void TD::Transformble::scaleInGlobal(const Vec3d & scale)
{
	setScale(this->scale + scale);
}

void TD::Transformble::setScale(const Vec3d & newScale)
{
	scale = newScale;
	transform.scale(1. / scale);
	transform.scale(newScale);
}

void TD::Transformble::setRotationOrder(const Transform::RotationOrder & order)
{
	transform.setRotationOrder(order);
}

TD::Vec3d TD::Transformble::getPosition() const
{
	return translation;
}

TD::Vec3d TD::Transformble::getRotation() const
{
	return rotation;
}

TD::Vec3d TD::Transformble::getScale() const
{
	return scale;
}

TD::Transform::RotationOrder TD::Transformble::getRotationOrder() const
{
	return transform.getRotationOrder();
}

TD::Transform TD::Transformble::getTransform() const
{
	return Transform(translation, rotation, scale, transform.getRotationOrder());
}
