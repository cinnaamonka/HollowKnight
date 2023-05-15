#include "pch.h"
#include "TextureManager.h"

#include <Texture.h>

TextureManager::TextureManager() :
	m_IsLoaded{ false }
{
	m_IsLoaded = false;
}
TextureManager::~TextureManager()
{

}

Texture* TextureManager::GetTexture(const std::string& filename)
{
	if (!m_IsLoaded)
	{
		Texture* newTexture = new Texture{ filename };
		texturesMap.emplace(filename, newTexture);
		m_IsLoaded = true;
		return (newTexture);
	}
	else
	{
		return texturesMap[filename];
	}
}