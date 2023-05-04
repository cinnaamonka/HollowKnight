#include "pch.h"
#include "Door.h"

#include <Texture.h>

Door::Door(const Point2f& doorPos) :
	BaseMovingObject{ "DoorNewTest.png",10}, m_State{State::standing}
{
	Rectf sourceRect{ 0,0,0,0 };
	Rectf shape{ 0.0f,0.0f,0.0f,0.0f };
	SetFramesPerSec(50);
	SetFramesNumber(10);

	shape.left = doorPos.x;
	shape.bottom = doorPos.y;
	shape.width = GetTexture()->GetWidth()/10;
	shape.height = GetTexture()->GetHeight();

	SetShape(shape);

	sourceRect.width = shape.width;
	sourceRect.height = shape.height;

	SetSourceRect(sourceRect);
}

Door::~Door()
{

}

bool Door::isCollidingActor(const Rectf& actorShape, bool isAtacked)
{
	const Rectf collideRect
	{
		 actorShape.left,
		 actorShape.bottom,
		 actorShape.width / 2,
		 actorShape.height
	};
	const Rectf objectCollisionShape
	{
		 GetShape().left + GetShape().width / 2,
		 GetShape().bottom,
		 GetShape().width / 2,
		 GetShape().height
	};
	if (m_State == State::broken)return false;
	if ((collideRect.left < objectCollisionShape.left &&
		collideRect.left + collideRect.width >= objectCollisionShape.left) && isAtacked)
	{
		m_State = State::breaking;
		return true;
	}

	return false;
}
void Door::Update(float elapsedSec)
{
	const int movingFrames = 8;
	
	
	if ( m_State != State::broken)
	{
		UpdateFrame(elapsedSec, movingFrames);
		//isCollidingActor(actor, isAtacking);
		ChangeTexture();
	}
	
}
void Door::HandleCollision(Rectf& actor, bool isAtacking)
{
	if (!isAtacking && isCollidingActor(actor, isAtacking) && m_State != State::broken)
	{
		actor.left = GetShape().left;
	}
}
void Door::ChangeTexture()
{

	Rectf srcRect{0.0f,GetSourceRect().height,GetSourceRect().width,GetSourceRect().height};

	if (m_State == State::broken)return;
	srcRect.left = GetAnimationFrame() * srcRect.width;

	const int breakingDoorTextureAmount = 8;
	const int brokenDoorTextureAmount = 1;

	if (m_State == State::breaking)
	{
		if (GetAnimationFrame() == breakingDoorTextureAmount - 1)
		{
			std::cout << "broken" << std::endl;
			m_State = State::broken;
		}
		
		SetSourceRect(srcRect);
	}
	if (m_State == State::broken)
	{
		srcRect.left = 9 * srcRect.width;
		SetAnimationFrame(1);
		SetSourceRect(srcRect);
	}
	if(m_State == State::standing)
	{
		srcRect.left = 0.0f;
		SetAnimationFrame(1);
		SetSourceRect(srcRect);
	}
	SetSourceRect(srcRect);
}
void Door::Draw() const
{
	Rectf rect1 = GetShape();
	Rectf rect2 = GetSourceRect();
	GetTexture()->Draw(GetShape(), GetSourceRect());
}