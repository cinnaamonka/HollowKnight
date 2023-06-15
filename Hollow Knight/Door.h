#pragma once

#include "GroundObject.h"

class Texture;
class Avatar;
class SoundEffect;



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
	void Update(float elapsedSec, Avatar* actor, const int index);
	void ChangeTexture();
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, bool isAtacked, const int index);
	bool isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) const;
	void SetSoundVolume(const int soundVolume) const;

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

	float m_AnimTime;

	int m_NrOfFrames;
	int m_NrFramesPerSec;
	int m_AnimFrame;

	Rectf m_Shape;
	Rectf m_SourceRect;

	std::vector<std::vector<Point2f>> m_Vertices;

	SoundEffect* m_pBreakingDoorSound;
};

