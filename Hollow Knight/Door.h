#pragma once

class Texture;
class Avatar;
class SoundEffect;

#include "GroundObject.h"

class Door final : public GroundObject
{
public:

	Door(const Point2f& doorPos);
	Door(const Door& other) = delete;
	Door& operator=(const Door& other) = delete;
	Door(Door&& other) = delete;
	Door& operator=(Door&& other) = delete;
	~Door();

	void Draw() const;
	void Update(float elapsedSec, Avatar* actor,const int index);
	void ChangeTexture();
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, bool isAtacked,const int index);
	bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) const;

	void SetSoundVolume(const int soundVolume);

private:
	void UpdateFrame(float elapsedSec, int numberFrames);

private:

	enum class State
	{
		breaking,
		broken,
		standing
	};
	State m_State;

	float m_AnimTime = 0.0f;

	int m_NrOfFrames = 0;
	int m_NrFramesPerSec = 1;
	int m_AnimFrame = 0;

	Rectf m_Shape;
	Rectf m_SourceRect;

	std::vector<std::vector<Point2f>> m_Vertices;

	SoundEffect* m_pBreakingDoorSound;
};

