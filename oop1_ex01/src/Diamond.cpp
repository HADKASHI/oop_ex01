#include "Diamond.h"



//*************************************************
//				c-tor functions
//*************************************************

Diamond::Diamond(const Vertex vertices[4])
	:m_left(vertices[0]),
	m_right(vertices[2]),
	m_top(vertices[1]),
	m_down(vertices[3])
{
	if (!isValidDiamond())
		defaultDiamond();

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
		defaultDiamond();
}


//*************************************************
//				draw functions
//*************************************************
void Diamond::draw(Board& board) const
{
	board.drawLine(m_left, m_right);
	board.drawLine(m_left, m_top);
	board.drawLine(m_top, m_right);
	board.drawLine(m_right, m_down);
	board.drawLine(m_down, m_left);
}


//*****************************************************
//					get functions
//*****************************************************
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


//*****************************************************
//					private functions
//*****************************************************
//---------------------------------------------------------------------------
void Diamond::defaultDiamond()
{
		m_left = Vertex(20, 20);
		m_top = Vertex(25, 25);
		m_right = Vertex(30, 20);
		m_down = Vertex(25, 15);
}

//--------------------------------------------------------------------------
bool Diamond::isValidDiamond() const
{
	if (m_left.isValid() && m_right.isValid() &&
		m_top.isValid() && m_down.isValid() &&
		(m_top.m_col - m_down.m_col) < 0.5 &&
		(m_left.m_row - m_right.m_row) < 0.5 &&
		(segmentLength(m_left, m_top) -
			segmentLength(m_right, m_top)) < 0.5 &&
		(segmentLength(m_left, m_down) -
			segmentLength(m_right, m_down)) < 0.5 &&
		(segmentLength(m_left, m_top) -
			segmentLength(m_right, m_down)) < 0.5 &&
		m_top.isHigherThan(m_down))
		return true;

	return false;
}

//-------------------------------------------------------------------------
double Diamond::segmentLength(Vertex v1, Vertex v2) const
{
	return sqrt(pow((v1.m_col - v2.m_col), 2) +
		pow((v1.m_row - v2.m_row), 2));
}