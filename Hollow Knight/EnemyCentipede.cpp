#include "pch.h"
#include "EnemyCentipede.h"

#include <Texture.h>

// EnemyCentipede

EnemyCentipede::EnemyCentipede(const Point2f& position) :
	BaseEnemy(position, "EnemyCentipede.png",5), m_SpeedX(30.0f)
{

	SetBoundaries(600.0f, GetShape().height); // default
}
EnemyCentipede::~EnemyCentipede()
{

}
void EnemyCentipede::Update(float elapsedSec)
{
	UpdateFrame(elapsedSec,GetFramesNumber());

	ChangeTexture(1,4);

	Rectf myShape = GetShape();
	Rectf bounds = GetBoundaries();

	if (myShape.left + myShape.width >= bounds.left + bounds.width || myShape.left < bounds.left)
	{
		m_SpeedX *= -1;
	}
	if (!IsKilled())
	{
		myShape.left += m_SpeedX * elapsedSec;
	}
	

	SetShape(myShape);
}

void EnemyCentipede::Draw() const
{

	if (m_SpeedX < 0)
	{
		glPushMatrix();

		glTranslatef(GetShape().left, GetShape().bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-GetShape().width, 0, 0);

		GetTexture()->Draw(Point2f(0, 0), GetSourceRect());

		glPopMatrix();
	}
	else
	{
		GetTexture()->Draw(GetShape(), GetSourceRect());
	}
	
}
