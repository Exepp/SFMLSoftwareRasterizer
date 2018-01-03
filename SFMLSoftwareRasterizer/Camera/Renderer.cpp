#include "Renderer.h"
#include "Utilities/AABB2.h"

#define MAX_VERTICES_PRE_POLYGON 10
struct Polygon
{
	TD::Vert verticies[MAX_VERTICES_PRE_POLYGON];
	uint8_t vertNum;
};

TD::Renderer::Renderer(const Vec2u & canvasSize)
{
	makeCanvas(canvasSize);
}

void TD::Renderer::makeCanvas(const Vec2u & canvasSize)
{
	if (!canvas)
	{
		this->canvasSize = canvasSize;
		canvas = new RGB[canvasSize.x * canvasSize.y];
		zbuffer = new double_t[canvasSize.x * canvasSize.y];
		sfCanvas.resize(canvasSize.x * canvasSize.y);
		for (size_t i = 0; i < canvasSize.x * canvasSize.y; i++)
		{
			zbuffer[i] = farClippingPlane;
			sfCanvas[i].position = sf::Vector2f(i % canvasSize.x, i / canvasSize.x);
		}

		sfCanvas.setPrimitiveType(sf::PrimitiveType::Points);
	}
}

void TD::Renderer::clearCanvas()
{
	for (size_t i = 0; i < canvasSize.x * canvasSize.y; i++)
	{
		zbuffer[i] = farClippingPlane;
		sfCanvas[i].color = sf::Color::Black;
		canvas[i] = RGB::zeroVector;
	}
}

void ClipPolygonForAxis(Polygon& face, TD::Axis AXIS, int side);
Polygon clip(TD::Vert & v0, const TD::Vert & v1, const TD::Vert & v2);

void TD::Renderer::draw(const Vert *verticies, size_t vertexNumber, const Matrix & viewMatrix)
{
	if (vertexNumber % 3 != 0)
		return;
	for (size_t i = 0; i < vertexNumber; i += 3)
	{
		Matrix projM = asPerspectiveProjectionMatrix(90, nearClippingPlane, farClippingPlane);
		Vert v0Raster = Vert((verticies[i].position * viewMatrix) * projM, verticies[i].color, verticies[i].textCoords);
		Vert v1Raster = Vert((verticies[i + 1].position * viewMatrix) * projM, verticies[i + 1].color, verticies[i + 1].textCoords);
		Vert v2Raster = Vert((verticies[i + 2].position * viewMatrix) * projM, verticies[i + 2].color, verticies[i + 2].textCoords);

		Polygon polToDraw = clip(v0Raster, v1Raster, v2Raster);

		for (size_t i = 0; i < polToDraw.vertNum; i++)
		{
			double_t w = polToDraw.verticies[i].position.w;
			polToDraw.verticies[i].position.normalizeW();
			polToDraw.verticies[i].position.z = w;
			toRasterSpace(polToDraw.verticies[i].position);
		}
		v0Raster = polToDraw.verticies[0];
		for (size_t i = 0; i < polToDraw.vertNum; i++)
		{
			v1Raster = polToDraw.verticies[(i+1) % polToDraw.vertNum];
			v2Raster = polToDraw.verticies[(i + 2) % polToDraw.vertNum];
			setInClockwiseOrder(v0Raster, v1Raster, v2Raster);
			rasterization(v0Raster, v1Raster, v2Raster);
		}
	}
}

Polygon clip(TD::Vert & v0, const TD::Vert & v1, const TD::Vert & v2)
{
	Polygon face;
	face.vertNum = 3;
	face.verticies[0] = v0;
	face.verticies[1] = v1;
	face.verticies[2] = v2;

	ClipPolygonForAxis(face, TD::Axis::X, -1);    // w=-x
	ClipPolygonForAxis(face, TD::Axis::X, 1);     // w=x
	ClipPolygonForAxis(face, TD::Axis::Y, -1);    // w=-y
	ClipPolygonForAxis(face, TD::Axis::Y, 1);     // w=y
	ClipPolygonForAxis(face, TD::Axis::Z, -1);    // w=-z
	ClipPolygonForAxis(face, TD::Axis::Z, 1);     // w=z

	return face;
}

void ClipPolygonForAxis(Polygon& face, TD::Axis AXIS, int side)	// side - sign (-1) or (1)
{
	TD::Vert* currentVertex;
	TD::Vert* previousVertex;

	uint8_t outVertNum = 0;
	TD::Vert outVertices[MAX_VERTICES_PRE_POLYGON];

	int8_t previousDot;
	int8_t currentDot;

	double_t intersectionFactor;
	TD::Vert intersectionPoint;

	previousVertex = &(face.verticies[face.vertNum - 1]);
	previousDot = (side*(*previousVertex)[AXIS] > previousVertex->position.w) ? -1 : 1;
	currentVertex = &face.verticies[0];
	while (currentVertex != &face.verticies[face.vertNum])
	{
		currentDot = (side*(*currentVertex)[AXIS] > currentVertex->position.w) ? -1 : 1;

		if (previousDot * currentDot < 0)
		{
			intersectionFactor = (previousVertex->position.w - side*(*previousVertex)[AXIS]) /
				((previousVertex->position.w - side*(*previousVertex)[AXIS]) - (currentVertex->position.w - side*(*currentVertex)[AXIS]));
			intersectionPoint.position = previousVertex->position + (currentVertex->position - previousVertex->position) * intersectionFactor;
			intersectionPoint.color = TD::RGB((TD::Vec3d)previousVertex->color + ((TD::Vec3d)currentVertex->color - (TD::Vec3d)previousVertex->color) * intersectionFactor);

			outVertices[outVertNum] = intersectionPoint;
			outVertNum++;
		}
		if (currentDot > 0)
		{
			outVertices[outVertNum] = *currentVertex;
			outVertNum++;
		}
		previousDot = currentDot;
		previousVertex = currentVertex;
		currentVertex++;
	}

	face.vertNum = outVertNum;
	for (int i = 0; i < outVertNum; i++)
		face.verticies[i] = outVertices[i];
}

void TD::Renderer::toRasterSpace(Vec3d & vertex)
{
	vertex.x = ((vertex.x + 1) * 0.5 * canvasSize.x);
	vertex.y = ((1 - (vertex.y + 1) * 0.5) * canvasSize.y);
}

void TD::Renderer::setInClockwiseOrder(Vert & v0, Vert & v1, Vert & v2)
{
	Vec3d edgeCentrePoint = v1.position + ((v2.position - v1.position) * 0.5);
	if (edgeFunction(Vec3i(v0.position), Vec3i(edgeCentrePoint), Vec3i(v2.position)) < 0)
	{
		auto temp = v1;
		v1 = v2;
		v2 = temp;
	}
}

void TD::Renderer::rasterization(const TD::Vert & v0, const TD::Vert & v1, const TD::Vert & v2)
{
	const Vec3i &v0pos = (Vec3i)v0.position;
	const Vec3i &v1pos = (Vec3i)v1.position;
	const Vec3i &v2pos = (Vec3i)v2.position;
	AABB2i triangleAABB;
	triangleAABB.setBounds({ v0pos.x, v0pos.y }, { v1pos.x, v1pos.y }, { v2pos.x, v2pos.y });
	triangleAABB.clampBounds(0, canvasSize.y, 0, canvasSize.x);

	int A0 = v1pos.y - v0pos.y;
	int B0 = v0pos.x - v1pos.x;

	int A1 = v2pos.y - v1pos.y;
	int B1 = v1pos.x - v2pos.x;

	int A2 = v0pos.y - v2pos.y;
	int B2 = v2pos.x - v0pos.x;

	Vec2i p(triangleAABB.left, triangleAABB.top);

	int w0_row = edgeFunction(A0, B0, v1pos.x * v0pos.y - v1pos.y * v0pos.x, p);	// A0, B0, C0
	int w1_row = edgeFunction(A1, B1, v2pos.x * v1pos.y - v2pos.y * v1pos.x, p);	// A1, B1, C1
	int w2_row = edgeFunction(A2, B2, v0pos.x * v2pos.y - v0pos.y * v2pos.x, p);	// A2, B2, C2

	double_t area = edgeFunction(v0pos, v1pos, v2pos);
	if (area <= 0)
		return;

	for (p.y = triangleAABB.top; p.y < triangleAABB.bottom; p.y++)
	{
		int w0 = w0_row;
		int w1 = w1_row;
		int w2 = w2_row;

		for (p.x = triangleAABB.left; p.x < triangleAABB.right; p.x++)
		{
			if ((w0 | w1 | w2) >= 0)
			{
				double_t _w0 = w0 / area / v2pos.z;
				double_t _w1 = w1 / area / v0pos.z;
				double_t _w2 = w2 / area / v1pos.z;

				double_t z = 1 / (_w1 + _w2 + _w0);
				if (zbuffer[p.y * canvasSize.x + p.x] > z)
				{
					sfCanvas[p.y * canvasSize.x + p.x].color = sf::Color(	(_w1 * v0.color.x  + _w2 * v1.color.x  + _w0 * v2.color.x) * z,
																			(_w1 * v0.color.y  + _w2 * v1.color.y  + _w0 * v2.color.y) * z,
																			(_w1 * v0.color.z  + _w2 * v1.color.z  + _w0 * v2.color.z) * z);
					//canvas[p.y * canvasSize.x + p.x] = RGB(	(_w1 * v0.color.x  + _w2 * v1.color.x  + _w0 * v2.color.x) * z,
					//										(_w1 * v0.color.y  + _w2 * v1.color.y  + _w0 * v2.color.y) * z,
					//										(_w1 * v0.color.z  + _w2 * v1.color.z  + _w0 * v2.color.z) * z);
					zbuffer[p.y * canvasSize.x + p.x] = z;
				}
			}
			w0 += A0;
			w1 += A1;
			w2 += A2;
		}
		w0_row += B0;
		w1_row += B1;
		w2_row += B2;
	}
}

int TD::edgeFunction(int A, int B, int C, const TD::Vec2i &p)
{
	return A * p.x + B * p.y + C;
}

int TD::edgeFunction(const TD::Vec3i & a, const TD::Vec3i & b, const TD::Vec3i & p)
{
	return (b.y - a.y) * p.x + (a.x - b.x) * p.y + (b.x * a.y - b.y * a.x);
}

const TD::RGB * TD::Renderer::getCanvas() const
{
	return canvas;
}

TD::Matrix TD::Renderer::asPerspectiveProjectionMatrix(double_t angleOfView, double_t near, double_t far)
{
	Matrix mat;

	double_t scale = 1 / tan(angleOfView * 0.5 * 3.14159265359 / 180);
	mat(0, 0) = scale;
	mat(1, 1) = scale;
	mat(2, 2) = -far / (far - near);
	mat(3, 2) = -far * near / (far - near);
	mat(2, 3) = -1;
	mat(3, 3) = 0;

	return mat;
}

