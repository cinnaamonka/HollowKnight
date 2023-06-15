#include "pch.h"
#include "Spikes.h"

Spikes::Spikes(const Rectf& spikesRect) :
	m_Shape(spikesRect)
{

}

Spikes::~Spikes()
{

}

bool Spikes::IsOverlapping(const Rectf& rect) const
{
	bool isColliding
	{
		rect.left < m_Shape.left + m_Shape.width &&
		(rect.left + rect.width > m_Shape.left) &&
		(rect.bottom < m_Shape.bottom + m_Shape.height) &&
		rect.bottom + rect.height > m_Shape.bottom
	};

	return isColliding;
}