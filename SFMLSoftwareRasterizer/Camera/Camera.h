#pragma once
#include <SFML/Graphics.hpp>
#include "Transform/Transformble.h"
#include "Utilities/AABB2.h"
#include "Renderer.h"

namespace TD
{
	class Camera : public TD::Transformble, public sf::Drawable
	{
	public:
		Camera(const Vec2u winSize);
		void setFarClippingPlane(double farClippingPlane);
		void setNearClippingPlane(double nearClippingPlane);
	
		//void lookAt(const Vec3d & target, const Vec3d& temp = Vec3d(0, 1, 0));

		virtual void draw(sf::RenderTarget & target, sf::RenderStates staes) const;

	private:
		mutable Renderer renderer;
	};
} // namespace TD