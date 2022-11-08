#pragma once
#include "Rectangle.h"

class Window
{
public:
	Window(const Rectangle& rectangle, const Vertex& point);
	Window(const Vertex& start, double width, double height, const Vertex& point);
	Vertex getBottomLeft() const;
	Vertex getTopRight() const;
	Vertex getPoint() const;

	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;
	Vertex getCenter() const;
	double getPerimeter() const;
	double getArea() const;
	bool scale(double factor);

private:
	bool isValidWindow() const;
	bool splitIsValid() const;
	void defaultSetup();
	Vertex getBottomRight() const;
	Vertex getTopLeft() const;
	Vertex m_bottomLeft;
	Vertex m_topRight;
	Vertex m_splitPoint;
};