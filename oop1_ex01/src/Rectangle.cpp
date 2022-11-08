#include "Rectangle.h"

//*************************************************
//				c-tor functions
//*************************************************
Rectangle::Rectangle(const Vertex& bottomLeft, const Vertex& topRight)
	: m_bottomLeft(bottomLeft.m_col, bottomLeft.m_row),
	  m_topRight(topRight.m_col, topRight.m_row)
{
	if (!isValidRectangle())
	{
		m_bottomLeft = Vertex(20, 10);
		m_topRight = Vertex(30, 20);
	}
}
//--------------------------------------------------------------------
Rectangle::Rectangle(const Vertex vertices[2])
	: m_bottomLeft(vertices[0].m_col, vertices[0].m_row),
	  m_topRight(vertices[1].m_col, vertices[1].m_row)
{
	if (!isValidRectangle())
	{
		m_bottomLeft = Vertex(20, 10);
		m_topRight = Vertex(30, 20);
	}
}
//--------------------------------------------------------------------
Rectangle::Rectangle(double x0, double y0, double x1, double y1)
	: m_bottomLeft(x0, y0),
	  m_topRight(x1,y1)
{
	if (!isValidRectangle())
	{
		m_bottomLeft = Vertex(20, 10);
		m_topRight = Vertex(30, 20);
	}
}
//--------------------------------------------------------------------
Rectangle::Rectangle(const Vertex& start, double width, double height)
	: m_bottomLeft(start.m_col, start.m_row),
	  m_topRight((m_bottomLeft.m_col + width),
	  m_topRight.m_row + height)
{
	if (!isValidRectangle())
	{
		m_bottomLeft = Vertex(20, 10);
		m_topRight = Vertex(30, 20);
	}
}

//*************************************************
bool Rectangle::isValidRectangle() const
{
	if (m_topRight.isToTheRightOf(m_bottomLeft) &&
		m_topRight.isHigherThan(m_bottomLeft) &&
		m_bottomLeft.isValid() && m_topRight.isValid())
		return true;

	return false;
}


//*************************************************
//				draw functions
//*************************************************
void Rectangle :: draw(Board& board) const
{
	board.drawLine(m_bottomLeft, getTopLeft());
	board.drawLine(getTopLeft(), m_topRight);
	board.drawLine(m_topRight, getBottomRight());
	board.drawLine(getBottomRight(), m_bottomLeft);
}

//*****************************************************
//					get functions
//*****************************************************
double Rectangle:: getWidth() const
{
	return (m_topRight.m_col - m_bottomLeft.m_col);
}
//----------------------------------------------------
double Rectangle:: getHeight() const
{
	return (m_topRight.m_row - m_bottomLeft.m_row);
}
//----------------------------------------------------
double Rectangle:: getArea() const
{
	return (getHeight() * getWidth());
}
//----------------------------------------------------
double Rectangle:: getPerimeter() const
{
	return 2*(getWidth() + getHeight());
}
//----------------------------------------------------
Vertex Rectangle:: getCenter() const
{
	Vertex v1((m_topRight.m_col + m_bottomLeft.m_col)/2.0,
		(m_topRight.m_row + m_bottomLeft.m_row)/2.0);

	return v1;
}
//----------------------------------------------------
Vertex Rectangle:: getBottomRight() const
{
	Vertex v(m_topRight.m_col, m_bottomLeft.m_row);

	return v;
}
//----------------------------------------------------
Vertex Rectangle:: getTopLeft() const
{
	Vertex v(m_bottomLeft.m_col, m_topRight.m_row);

	return v;
}
//-----------------------------------------------------
Vertex Rectangle::getBottomLeft() const
{
	return m_bottomLeft;
}
//-----------------------------------------------------
Vertex Rectangle::getTopRight() const
{
	return m_topRight;
}
//-------------------------------------------------------------
Rectangle Rectangle::getBoundingRectangle() const
{
	Rectangle r1(m_bottomLeft, m_topRight);
	return r1;
}
//**********************************************************


bool Rectangle:: scale(double factor)
{
	Vertex center(getCenter()),
		   bottomLeft(getBottomLeft()),
		   topRight(getTopRight());

	bottomLeft = bottomLeft.setFactor(center, factor);

	topRight = topRight.setFactor(center, factor);

	if (factor <= 0 || !bottomLeft.isValid() || !topRight.isValid())
		return false;

	m_bottomLeft = bottomLeft;
	m_topRight = topRight;

	return true;
}