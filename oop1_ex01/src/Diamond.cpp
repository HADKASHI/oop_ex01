#include "Diamond.h"




Diamond::Diamond(const Vertex vertices[4])
	:m_left(vertices[0]),
	m_right(vertices[2]),
	m_top(vertices[1]),
	m_down(vertices[3])
{
	if (!isValidDiamond())
		default();

}

//---------------------------------------------------------
Diamond::Diamond(const IsoscelesTriangle& lower)
	:m_left(lower.getVertex(0)),
	m_right(lower.getVertex(2)),
	m_down(lower.getVertex(1)),
	m_top(lower.getVertex(1).m_col,
		lower.getVertex(0).m_row * 2.0 - lower.getVertex(1).m_row)
{
	if (!isValidDiamond())
		default();
}






void Diamond::draw(Board& board) const
{
	board.drawLine(m_left, m_right);
	board.drawLine(m_right, m_top);
	board.drawLine(m_top, m_left);
	board.drawLine(m_right, m_down);
	board.drawLine(m_left, m_down);
}

//-----------------------------------------------------
Rectangle Diamond::getBoundingRectangle() const
{
	Vertex bottomLeft(m_left.m_col, m_down.m_row);
	Vertex topRight(m_right.m_col, m_top.m_row);

	Rectangle r(bottomLeft, topRight);
	return r;
}

//-------------------------------------------------------
double Diamond::getArea() const
{
	return getHeight() * getWidth() / 2.0;
}

//----------------------------------------------------------
double Diamond::getPerimeter() const
{
	IsoscelesTriangle triangle(m_left, m_right, getHeight() / 2.0);

	return triangle.getPerimeter()*2 - getWidth()*2;
}

//----------------------------------------------------------
Vertex Diamond::getCenter() const
{
	Vertex center(m_top.m_col, m_left.m_row);
	return center;
}

//-----------------------------------------------------------
bool Diamond::scale(double factor)
{
	Vertex center(getCenter()),
		right(getVertex(2)),
		left(getVertex(0)),
		top(getVertex(1)),
		down(getVertex(3));

	right = right.setFactor(center, factor);
	left = left.setFactor(center, factor);
	top = top.setFactor(center, factor);
	down = down.setFactor(center, factor);

	if (factor <= 0 || !right.isValid() ||
		!left.isValid() || !top.isValid() || !down.isValid())
		return false;

	m_left = left;
	m_right = right;
	m_top = top;
	m_down = down;

	return true;
}

//-------------------------------------------------------------------------
Vertex Diamond::getVertex(int index) const
{
	switch (index)
	{
	case 0:
		return m_left;
	case 1:
		return m_top;
	case 2:
		return m_right;
	case 3:
		return m_down;
	}
}

//--------------------------------------------------------------------------
double Diamond::getWidth() const
{
	return m_right.m_col - m_left.m_col;
}

//--------------------------------------------------------------------------
double Diamond::getHeight() const
{
	return m_top.m_row - m_down.m_row;
}

//---------------------------------------------------------------------------
void Diamond::default()
{
		m_left = Vertex(25, 15);
		m_top = Vertex(30, 20);
		m_right = Vertex(25, 25);
		m_down = Vertex(20, 20);
}

//--------------------------------------------------------------------------
bool Diamond::isValidDiamond() const
{
	if (m_left.isValid() && m_right.isValid() &&
		m_top.isValid() && m_down.isValid() &&
		(m_top.m_col - m_down.m_col) < 0.5 &&
		(m_left.m_row - m_right.m_row) < 0.5 &&
		(sqrt(pow((m_left.m_col - m_top.m_col), 2) +
			pow((m_left.m_row - m_top.m_row), 2)) ==
			sqrt(pow((m_right.m_col - m_top.m_col), 2) +
				pow((m_right.m_row - m_top.m_row), 2)) ==
			sqrt(pow((m_left.m_col - m_down.m_col), 2) +
				pow((m_left.m_row - m_down.m_row), 2)) ==
			sqrt(pow((m_right.m_col - m_down.m_col), 2) +
				pow((m_right.m_row - m_down.m_row), 2))))
		return true;

	return false;
}