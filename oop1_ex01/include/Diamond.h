#pragma once
#include "IsoscelesTriangle.h"


class Diamond
{
public:
	//c-tors
	Diamond(const Vertex vertices[4]);
	Diamond(const IsoscelesTriangle & lower);

	//shape functions
	Vertex getVertex(int index) const;
	double getWidth() const;
	double getHeight() const;
	Vertex getCenter() const;
	double getPerimeter() const;
	double getArea() const;
	bool scale(double factor);

	//draw functions
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;

private:
	void default();
	bool isValidDiamond() const;
	Vertex m_left;
	Vertex m_right;
	Vertex m_top;
	Vertex m_down;
};