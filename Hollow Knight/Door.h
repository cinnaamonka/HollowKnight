#pragma once

class Texture;

#include "BaseMovingObject.h"


class Door: public  BaseMovingObject
{
public:

	Door(const Point2f& doorPos);
	Door(const Door& other) = delete;
	Door& operator=(const Door& other) = delete;
	Door(Door&& other) = delete;
	Door& operator=(Door&& other) = delete;
	~Door();

	bool isCollidingActor(const Rectf& actorShape, bool isAtacked);

	void Draw() const override;
	void Update(float elapsedSec);
	void ChangeTexture();
	void HandleCollision(Rectf& actor, bool isAtacking);
private:

	enum class State
	{
		breaking,
		broken,
		standing
	};
	State m_State;

	
};

