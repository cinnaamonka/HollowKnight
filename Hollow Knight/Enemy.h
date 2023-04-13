#pragma once

class Texture;

class Enemy final
{
public:
	explicit Enemy(const Point2f& center);
	~Enemy();
	void Update( float elapsedSec );
	void Draw( ) const;
	bool IsOverlapping(const Rectf& rect ) const;
	
private:
	const Texture* m_pEnemyTexture;
	float m_Speed;
	Rectf m_SourceRect;
	Rectf m_Shape;
	Rectf m_BoundariesBorder;

	int   m_NrOfFrames;
	int   m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	//void MoveAvatar(float elapsedSec);
	void UpdateFrame(float elapsedSec);
	void ChangePosition();
};


