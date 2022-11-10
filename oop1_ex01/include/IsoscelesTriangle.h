#pragma once
#include "Rectangle.h"


class IsoscelesTriangle
{
public:
	//c-tors
	IsoscelesTriangle(const Vertex& left, const Vertex& right, double height);
	IsoscelesTriangle(const Vertex vertices[3]);

	//shape functions
	Vertex getVertex(int index) const;
	double getBaseLength() const;
	double getLegLength() const;
	double getHeight() const;
	Vertex getCenter() const;
	double getPerimeter() const;
	double getArea() const;
	bool scale(double factor);

	//draw functions
	void draw(Board& board) const;
	Rectangle getBoundingRectangle() const;

private:
	void defaultTriangle();
	bool isValidTriangle() const;
	Vertex m_left;
	Vertex m_right;
	Vertex m_tip;
};