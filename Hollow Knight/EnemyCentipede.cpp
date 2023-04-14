#include "pch.h"
#include "EnemyCentipede.h"

#include <Texture.h>

// EnemyCentipede

EnemyCentipede::EnemyCentipede(const Point2f& position) :
	BaseEnemy(position, "EnemyCentipede.png"), m_SpeedX(30.0f)
{
	SetBoundaries(300.0f, GetShape().height); // default
}

void EnemyCentipede::Update(float elapsedSec)
{
	UpdateFrame(elapsedSec);

	ChangeTexture();

	Rectf myShape = GetShape();
	Rectf bounds = GetBoundaries();

	if (myShape.left + myShape.width >= bounds.left + bounds.width || myShape.left < bounds.left)
	{
		m_SpeedX *= -1;
	}

	myShape.left += m_SpeedX * elapsedSec;

	SetShape(myShape);
}

void EnemyCentipede::Draw() const
{
	Rectf myShape = GetShape();
	Rectf sourceRect = GetSourceRect();

	if (m_SpeedX < 0)
	{
		glPushMatrix();

		glTranslatef(myShape.left, myShape.bottom, 0);
		glRotatef(0, 0, 0, 1);
		glScalef(-1, 1, 1);
		glTranslatef(-myShape.width, 0, 0);

		GetTexture()->Draw(Point2f(0, 0), sourceRect);

		glPopMatrix();
	}
	else
	{
		utils::DrawRect(myShape);

		GetTexture()->Draw(myShape, sourceRect);
	}

}