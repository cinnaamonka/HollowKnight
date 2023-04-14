#pragma once

class Texture;

class BaseMovingObject
{
public:

	BaseMovingObject(const std::string &path);
	virtual ~BaseMovingObject();

	const Texture* GetTexture() const {
		return m_pTexture;
	}

	virtual void Draw() const = 0;

private:

	Texture* m_pTexture;
};