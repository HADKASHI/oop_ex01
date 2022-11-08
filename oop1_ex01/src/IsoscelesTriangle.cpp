#include "IsoscelesTriangle.h"
#include <cmath>




//-----------------------------------------------------------
IsoscelesTriangle::IsoscelesTriangle(const Vertex& left, const Vertex& right, double height)
	:m_left(left),
	 m_right(right),
	 m_tip((m_left.m_col + m_right.m_col) / 2.0, m_left.m_row + height)
{
	if (!isValidTriangle())
	{
		m_left = Vertex(20, 20);
		m_right = Vertex(30, 20);
		m_tip = Vertex(25, 25);
	}
}

//--------------------------------------------------------------
IsoscelesTriangle::IsoscelesTriangle(const Vertex vertices[3])
	:m_left(vertices[0]),
	 m_right(vertices[2]),
	 m_tip(vertices[1])
{
	if (!isValidTriangle())
	{
		m_left = Vertex(20, 20);
		m_right = Vertex(30, 20);
		m_tip = Vertex(25, 25);
	}
}

//=============================================================================

//=============================================================================

bool IsoscelesTriangle::isValidTriangle() const
{
	if (abs(m_right.m_row - m_left.m_row) < 0.5 &&
		m_left.isValid() && m_right.isValid() && m_tip.isValid() &&
		abs(m_tip.m_col - (m_left.m_col + m_right.m_col) / 2.0) < 0.5)
		return true;
	
	return false;
}

//-----------------------------------------------------
void IsoscelesTriangle::draw(Board& board) const
{
	board.drawLine(m_left, m_right);
	board.drawLine(m_right, m_tip);
	board.drawLine(m_tip, m_left);
}

//-------------------------------------------------------
Vertex IsoscelesTriangle::getVertex(int index) const
{
	switch (index)
	{
	case 0:
		return m_left;
	case 1:
		return m_tip;
	case 2:
		return m_right;
	}
}

//-------------------------------------------------------
Rectangle IsoscelesTriangle::getBoundingRectangle() const
{
	Vertex v(m_right.m_col, m_tip.m_row);

	Rectangle r(m_left, v);
	return r;
}

//-------------------------------------------------------
double IsoscelesTriangle::getArea() const
{
	return abs(getHeight()) * getBaseLength() / 2.0;
}

//---------------------------------------------------------
double IsoscelesTriangle::getBaseLength() const
{
	return  m_right.m_col - m_left.m_col;
}

//----------------------------------------------------------
double IsoscelesTriangle::getPerimeter() const
{
	return getBaseLength() + getLegLength() * 2.0;
}

//----------------------------------------------------------
Vertex IsoscelesTriangle::getCenter() const
{
	Vertex center(m_tip.m_col , m_left.m_row + getHeight()/2.0);
	return center;
}

//-----------------------------------------------------------
bool IsoscelesTriangle::scale(double factor)
{
	Vertex center(getCenter()),
		right(getVertex(2)),
		tip(getVertex(1)),
		left(getVertex(0));

	right = right.setFactor(center, factor);

	left = left.setFactor(center, factor);

	tip = tip.setFactor(center, factor);


	if (factor <= 0 || !right.isValid() ||
		!left.isValid() || !tip.isValid())
		return false;

	m_left = left;
	m_right = right;
	m_tip = tip;

	return true;
}

//------------------------------------------------------
double IsoscelesTriangle::getHeight() const
{
	return m_tip.m_row - m_left.m_row;
}

//-----------------------------------------------------
double IsoscelesTriangle::getLegLength() const
{
	return sqrt(pow((m_left.m_col - m_tip.m_col), 2) + 
	pow((m_left.m_row - m_tip.m_row), 2));
}