#include "pch.h"
#include "BaseMovingObject.h"

#include <Texture.h>

BaseMovingObject::BaseMovingObject(const std::string& path):
	m_AnimTime(0),
	m_NrOfFrames(0),
	m_NrFramesPerSec(0),
	m_AnimFrame(0)
{
	m_pTexture = new Texture{ path };
}

BaseMovingObject::~BaseMovingObject()
{
	delete m_pTexture;
}

void BaseMovingObject::UpdateFrame(float elapsedSec,int numberFrames)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / numberFrames)
	{
		++m_AnimFrame %= numberFrames;

		m_AnimTime = 0.0f;
	}
}