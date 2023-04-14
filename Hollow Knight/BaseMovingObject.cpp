#include "pch.h"
#include "BaseMovingObject.h"

#include <Texture.h>

BaseMovingObject::BaseMovingObject(const std::string& path) 
{
	m_pTexture = new Texture{ path };
}

BaseMovingObject::~BaseMovingObject()
{
	delete m_pTexture;
}