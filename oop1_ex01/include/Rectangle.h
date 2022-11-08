#pragma once
#include "Vertex.h"
#include "Board.h"

class Rectangle
{
public:
	//c-tors
	Rectangle(const Vertex& bottomLeft, const Vertex& topRight);
	Rectangle(const Vertex vertices[2]);
	Rectangle(double x0, double y0, double x1, double y1);
	Rectangle(const Vertex& start, double width, double height);

	//shape functions
	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	Vertex getCenter() const;
	double getWidth() const;
	double getHeight() const;
	double getPerimeter() const;
	double getArea() const;
	bool scale(double factor);

	//draw functions
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;

private:
	bool isValidRectangle() const;
	Vertex getBottomRight() const;
	Vertex getTopLeft() const;
	Vertex m_bottomLeft;
	Vertex m_topRight;
};