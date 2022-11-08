#pragma once
#include "Window.h"

//*************************************************
//				c-tor functions
//*************************************************
Window::Window(const Rectangle& rectangle, const Vertex& point)
	:m_splitPoint(point.m_col, point.m_row),
	 m_bottomLeft(rectangle.getBottomLeft().m_col, rectangle.getBottomLeft().m_row),
	 m_topRight(rectangle.getTopRight().m_col, rectangle.getTopRight().m_row)
{
	if (!isValidWindow())
		defaultSetup();
}
//-------------------------------------------------
Window::Window(const Vertex& start, double width, double height, const Vertex& point)
	:m_splitPoint(point.m_col, point.m_row),
	 m_bottomLeft(start.m_col, start.m_row),
	 m_topRight((m_bottomLeft.m_col + width), m_bottomLeft.m_row + height)
{
	if (!isValidWindow())
		defaultSetup();
}

//*************************************************
//				draw functions
//*************************************************
void Window::draw(Board& board) const
{
	Rectangle r(m_bottomLeft, m_topRight);
	r.draw(board);
	
	Vertex leftSplit(m_bottomLeft.m_col, m_splitPoint.m_row);
	Vertex topSplit(m_splitPoint.m_col, m_topRight.m_row);
	Vertex rightSplit(m_topRight.m_col, m_splitPoint.m_row);
	Vertex bottomSplit(m_splitPoint.m_col, m_bottomLeft.m_row);

	board.drawLine(m_splitPoint, leftSplit);
	board.drawLine(m_splitPoint, topSplit);
	board.drawLine(m_splitPoint, rightSplit);
	board.drawLine(m_splitPoint, bottomSplit);
}
//*****************************************************
//					get functions
//*****************************************************
Rectangle Window::getBoundingRectangle() const
{
	Rectangle r(m_bottomLeft, m_topRight);

	return r;
}
//-----------------------------------------------------
Vertex Window::getCenter() const
{
	Rectangle r(m_bottomLeft, m_topRight);
	return r.getCenter();
}
//------------------------------------------------------
double Window::getPerimeter() const
{
	Rectangle r(m_bottomLeft, m_topRight);
	return r.getPerimeter();
}
//------------------------------------------------------
double Window::getArea() const
{
	Rectangle r(m_bottomLeft, m_topRight);
	return r.getArea();
}
//----------------------------------------------------
Vertex Window::getBottomRight() const
{
	Vertex v(m_topRight.m_col, m_bottomLeft.m_row);

	return v;
}
//----------------------------------------------------
Vertex Window::getTopLeft() const
{
	Vertex v(m_bottomLeft.m_col, m_topRight.m_row);

	return v;
}
//-----------------------------------------------------
Vertex Window::getBottomLeft() const
{
	return m_bottomLeft;
}
//-----------------------------------------------------
Vertex Window::getTopRight() const
{
	return m_topRight;
}
//-----------------------------------------------------
Vertex Window::getPoint() const
{
	return m_splitPoint;
}
//------------------------------------------------------
bool Window::scale(double factor)
{
	Rectangle r(m_bottomLeft, m_topRight);
	if (r.scale(factor))
	{
		m_splitPoint = m_splitPoint.setFactor(this->getCenter(), factor);

		m_bottomLeft = r.getBottomLeft();

		m_topRight = r.getTopRight();

		return true;
	}

	return false;
}


//*****************************************************
//					private functions
//*****************************************************
bool Window::isValidWindow() const
{
	if(m_topRight.isToTheRightOf(m_bottomLeft) &&
	   m_topRight.isHigherThan(m_bottomLeft) &&
	   m_bottomLeft.isValid() && m_topRight.isValid() &&
	   splitIsValid())
		return true;

	return false;
}
//-----------------------------------------------------
bool Window::splitIsValid() const
{
	if (m_splitPoint.m_col >= m_bottomLeft.m_col &&

		m_splitPoint.m_col <= m_topRight.m_col &&

		m_splitPoint.m_row >= m_bottomLeft.m_row &&

		m_splitPoint.m_row <= m_topRight.m_row &&
		
		m_splitPoint.isValid())
		return true;

	return false;
}
//-------------------------------------------------------
void Window::defaultSetup()
{
	m_bottomLeft = Vertex(20, 10);
	m_splitPoint = Vertex(25, 15);
	m_topRight   = Vertex(30, 20);
}