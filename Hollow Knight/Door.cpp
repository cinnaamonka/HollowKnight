#include "pch.h"
#include "Door.h"
#include "Avatar.h"

#include <Texture.h>
#include <SVGParser.h>

Door::Door(const Point2f& doorPos) :
	GroundObject{ "DoorNewTest.png"}, m_State{State::standing}, m_NrOfFrames(10), m_NrFramesPerSec(50)
{
	SVGParser::GetVerticesFromSvgFile("Doors.svg", m_Vertices);

	m_Shape.left = doorPos.x;
	m_Shape.bottom = doorPos.y;
	m_Shape.width = GetTexture()->GetWidth()/ m_NrOfFrames;
	m_Shape.height = GetTexture()->GetHeight();

	m_SourceRect.width = m_Shape.width;
	m_SourceRect.height = m_Shape.height;

}

Door::~Door()
{

}

void Door::Update(float elapsedSec, Avatar* actor)
{
	const int movingFrames = 8;
	Rectf rectActor = actor->GetShape();

	Vector2f vector = actor->GetVelocity();

	
	if ( m_State != State::broken)
	{
		HandleCollision(rectActor, vector, actor->IsAtacking());
		actor->SetShape(rectActor);
		UpdateFrame(elapsedSec, movingFrames);
		ChangeTexture();
	}
}
void Door::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, bool isAtacked)
{
	float borderDist{ 5.f };

	const Point2f ray1{ actorShape.left + borderDist, actorShape.bottom };
	const Point2f ray2{ actorShape.left + borderDist, actorShape.bottom + actorShape.height };

	const Point2f ray3{ actorShape.left + actorShape.width - borderDist, actorShape.bottom };
	const Point2f ray4{ actorShape.left + actorShape.width - borderDist, actorShape.bottom + actorShape.height };

	utils::HitInfo hitInfo{};

	
	for (std::vector<Point2f>& ver : m_Vertices)
	{
		if (isCollidingWalls(ver, actorShape, hitInfo) )
		{
			if (isAtacked)
			{
				m_State = State::breaking;
			}
			
			ResetHorizontalPosition(actorVelocity, actorShape, hitInfo);

			break;
		}
	}
}
void Door::ChangeTexture()
{

	if (m_State == State::broken)return;
	m_SourceRect.left = m_AnimFrame * m_SourceRect.width;

	const int breakingDoorTextureAmount = 8;
	const int brokenDoorTextureAmount = 1;

	if (m_State == State::breaking)
	{
		if (m_AnimFrame == breakingDoorTextureAmount - 1)
		{
			m_State = State::broken;
		}
		
	}
	if (m_State == State::broken)
	{
		m_SourceRect.left = 9 * m_SourceRect.width;
		m_AnimFrame = 1;

	}
	if(m_State == State::standing)
	{
		m_SourceRect.left = 0.0f;
		m_AnimFrame =1;
	}
}
void Door::Draw() const
{
	
	GetTexture()->Draw(m_Shape, m_SourceRect);
}
bool Door::isCollidingWalls(const std::vector<Point2f>& ver, Rectf& actorShape, utils::HitInfo& hitInfo)const
{
	float borderDist{ 5.f };

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
