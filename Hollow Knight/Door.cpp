#include "pch.h"
#include "Door.h"
#include "Avatar.h"

#include <Texture.h>
#include <SVGParser.h>
#include <SoundEffect.h>

Door::Door(const Point2f& doorPos) :
	GroundObject("DoorNewTest.png"),
	m_State(State::standing),
	m_NrOfFrames(10),
	m_NrFramesPerSec(50),
	m_AnimTime(0.0f),
	m_AnimFrame(0)
{
	SVGParser::GetVerticesFromSvgFile("Doors.svg", m_Vertices);

	m_Shape.left = doorPos.x;
	m_Shape.bottom = doorPos.y;

	m_Shape.width = GetTexture()->GetWidth() / m_NrOfFrames;
	m_Shape.height = GetTexture()->GetHeight();

	m_SourceRect.width = m_Shape.width;
	m_SourceRect.height = m_Shape.height;

	m_pBreakingDoorSound = new SoundEffect("DoorBreaksSound.wav");
}

Door::~Door()
{
	delete m_pBreakingDoorSound;
}

void Door::Update(float elapsedSec, Avatar* actor, const int index)
{
	const int movingFrames = 8;

	Rectf rectActor = actor->GetShape();
	Vector2f vector = actor->GetVelocity();


	if (m_State != State::broken)
	{
		HandleCollision(rectActor, vector, actor->IsAtacking(), index);

		actor->SetShape(rectActor);

		UpdateFrame(elapsedSec, movingFrames);

		ChangeTexture();
	}
}

void Door::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, bool isAtacked, const int index)
{
	float borderDist = 5.f;

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	utils::HitInfo hitInfo{};

	if (isCollidingWalls(m_Vertices[index], actorShape, hitInfo))
	{
		if (isAtacked)
		{
			m_State = State::breaking;
		}

		ResetHorizontalPosition(actorVelocity, actorShape, hitInfo);
	}
}

void Door::ChangeTexture()
{
	if (m_State == State::broken) return;

	const int breakingDoorTextureAmount = 8;
	const int brokenDoorTexture = 9;
	const int brokenDoorTextureAmount = 1;

	m_SourceRect.left = m_AnimFrame * m_SourceRect.width;

	if (m_State == State::breaking)
	{
		if (m_AnimFrame == breakingDoorTextureAmount - 1)
		{
			m_State = State::broken;

		}

		m_pBreakingDoorSound->Play(0);
	}

	if (m_State == State::broken)
	{
		m_SourceRect.left = brokenDoorTexture * m_SourceRect.width;

		m_AnimFrame = 1;

	}

	if (m_State == State::standing)
	{
		m_SourceRect.left = 0.0f;

		m_AnimFrame = 1;
	}
}

void Door::Draw() const
{
	GetTexture()->Draw(m_Shape, m_SourceRect);
}

bool Door::isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo) const
{
	float borderDist = 5.f;

	const Point2f ray1{ actorShape.left, actorShape.bottom + borderDist };
	const Point2f ray2{ actorShape.left + actorShape.width, actorShape.bottom + borderDist };

	const Point2f ray3{ actorShape.left , actorShape.bottom + actorShape.height - borderDist };
	const Point2f ray4{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height - borderDist };

	const Point2f ray5{ actorShape.left , actorShape.bottom + actorShape.height / 2 };
	const Point2f ray6{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2 };

	return utils::Raycast(ver, ray1, ray2, hitInfo) || utils::Raycast(ver, ray3, ray4, hitInfo) || utils::Raycast(ver, ray5, ray6, hitInfo);
}

void Door::UpdateFrame(float elapsedSec, int numberFrames)
{
	m_AnimTime += elapsedSec;

	if (m_AnimTime >= 1.f / m_NrFramesPerSec)
	{
		++m_AnimFrame %= numberFrames;

		m_AnimTime = 0.0f;
	}
}

void Door::SetSoundVolume(const int soundVolume) const
{
	m_pBreakingDoorSound->SetVolume(soundVolume);

}
