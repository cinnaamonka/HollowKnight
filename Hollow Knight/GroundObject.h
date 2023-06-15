#pragma once

class Texture;

class GroundObject
{
public:
	GroundObject(const std::string& texture);
	GroundObject(const GroundObject& other) = delete;
	GroundObject& operator=(const GroundObject& other) = delete;
	GroundObject(GroundObject&& other) = delete;
	GroundObject& operator=(GroundObject&& other) = delete;
	virtual ~GroundObject();

	void Draw(const Point2f& pos) const;

	const Rectf& GetShape() const
	{
		return m_Shape;
	}

protected:

	std::vector<std::vector<Point2f>> m_Vertices;

	bool isCollidingGround(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo);
	bool isCollidingTop(const std::vector<Point2f>& ver, const Rectf& actorShape, utils::HitInfo& hitInfo);


	void ResetVerticalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetTopPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);
	void ResetHorizontalPosition(Vector2f& actorVelocity, Rectf& actorShape, utils::HitInfo& hitInfo);

	void SetShape(const Rectf& rect);

	const Texture* GetTexture() const
	{
		return m_pTexture;
	}

private:

	Texture* m_pTexture;

	Rectf m_Shape;
	std::string texturefilename;
};

