#include "pch.h"
#include "BaseMovingObject.h"

#include <Texture.h>

BaseMovingObject::BaseMovingObject(const std::string& path, int framesNumber) :
	m_AnimTime(0),
	m_NrOfFrames(framesNumber),
	m_NrFramesPerSec(10),
	m_AnimFrame(0),
	m_IsKilled(false),
	m_LifesAmount(2)

{
	m_pTexture = new Texture{ path };
}
BaseMovingObject::~BaseMovingObject()
{
	delete m_pTexture;
}

void BaseMovingObject::UpdateFrame(float elapsedSec, int numberFrames)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / m_NrFramesPerSec)
	{
		++m_AnimFrame %= numberFrames;

		m_AnimTime = 0.0f;
	}
}