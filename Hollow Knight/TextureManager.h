#pragma once
#include <map>

class Texture;

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	Texture* GetTexture(const std::string& filename);

	bool IsLoaded()
	{
		return m_IsLoaded;
	}
	void SetIsLoaded(const bool isLoaded)
	{
		m_IsLoaded = isLoaded;
	}
private:
	bool m_IsLoaded;
	std::map<std::string, Texture*> texturesMap;
};

