#pragma once

class Texture;

class BaseEnemy
{
public:

	explicit BaseEnemy(const Point2f& position, const std::string &texture);
	virtual ~BaseEnemy();

	BaseEnemy(const BaseEnemy& other) = delete;
	BaseEnemy& operator=(const BaseEnemy& other) = delete;
	BaseEnemy(BaseEnemy&& other) = delete;
	BaseEnemy& operator=(BaseEnemy&& other) = delete;

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;

	bool IsOverlapping(const Rectf& rect) const;

protected:

	void UpdateFrame(float elapsedSec);
	void ChangeTexture();

	void SetBoundaries(float width, float height);

	Rectf GetBoundaries() const {
		return m_BoundariesBorder;
	}

	Rectf GetSourceRect() const {
		return m_SourceRect;
	}

	Rectf GetShape() const {
		return m_Shape;
	}

	void SetShape(const Rectf&shape) {
		m_Shape  = shape;
	}

	const Texture* GetTexture() const {
		return m_pEnemyTexture;
	}

private:

	Rectf m_SourceRect;
	Rectf m_Shape;
	Rectf m_BoundariesBorder;

	int   m_NrOfFrames;
	int   m_NrFramesPerSec;
	float m_AnimTime;
	int m_AnimFrame;

	Texture* m_pEnemyTexture;
};


