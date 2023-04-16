#include "pch.h"
#include "Spikes.h"

Spikes::Spikes(const Rectf& spikesRect):
	m_Shape{spikesRect}
{

}
Spikes::~Spikes()
{

}
void Spikes::Draw()
{
	utils::DrawRect(m_Shape);
}

