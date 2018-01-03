#pragma once
#include "Utilities/Matrix.h"
#include "Utilities/Vert.h"

#include <SFML/Graphics.hpp>

namespace TD
{
	class Renderer
	{
	public:
		Renderer() = default;
		Renderer(const Vec2u & canvasSize);

		void clearCanvas();
		void draw(const Vert *verticies, size_t vertexNumber, const Matrix & viewMatrix);

		void makeCanvas(const Vec2u & canvasSize);
		
		const RGB* getCanvas() const;

		static Matrix asPerspectiveProjectionMatrix(double_t angleOfView, double_t near, double_t far);

	private:
		void toRasterSpace(Vec3d & vertex);
		void setInClockwiseOrder(Vert & v0, Vert & v1, Vert & v2);
		void rasterization(const TD::Vert & a, const TD::Vert & b, const TD::Vert & c);

	public:
		sf::VertexArray sfCanvas;
		
	private:
		Vec2u		canvasSize;
		RGB*		canvas				= nullptr;
		double_t*	zbuffer				= nullptr;
		double_t	nearClippingPlane	= 1;
		double_t	farClippingPlane	= 1000;
	};

	int edgeFunction(int A, int B, int C, const TD::Vec2i &p);
	int edgeFunction(const TD::Vec3i &a, const TD::Vec3i &b, const TD::Vec3i &p);
}

