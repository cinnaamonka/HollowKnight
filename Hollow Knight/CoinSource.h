#pragma once
class Texture;

class CoinSource final
{
public:

	CoinSource(const Point2f& position);
	CoinSource(const CoinSource& other) = delete;
	CoinSource& operator=(const CoinSource& other) = delete;
	CoinSource(CoinSource&& other) = delete;
	CoinSource& operator=(CoinSource&& other) = delete;
	~CoinSource();

	void Draw()const;
	void Update();
	void CheckIfDestroyed();
	bool IsOverlapping(const Rectf& rect) const;

	bool IsDestroyed()
	{
		return m_IsDestroyed;
	}
private:
	void Shake();
	void ChangeTexture();
private:

	Texture* m_pTexture;
	Point2f m_Position;
	Rectf m_SourceRect;
	float m_ClipWidth;
	float m_ClipHeight;

	bool m_IsDestroyed;
	bool m_IsAtacked;
	int m_Lifes;

	const int m_MaxLifes;

	int m_PassedFrames;
	const int m_MaxFramesAmount;
};

