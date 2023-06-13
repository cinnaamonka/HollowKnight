#pragma once

class Texture;
class SoundEffect;

class Coin final
{
public:

    Coin();
    Coin(const Coin& other) = delete;
    Coin& operator=(const Coin& other) = delete;
    Coin(Coin&& other) = delete;
    Coin& operator=(Coin&& other) = delete;
    ~Coin();

    void Draw() const;

    Rectf GetShape() const
    {
        return m_Shape;
    }
    void SetShape(const Rectf& rect)
    {
        m_Shape = rect;
    }

    void SetPosition(const Point2f& pos)
    {
        m_Shape.left = pos.x;
        m_Shape.bottom = pos.y;
    }

    bool IsOverlapping(const Rectf& rect) const;

    bool IsCollected() const 
    {
        return m_IsCollected;
    }

    void SetIsCollected(const bool isCollected)
    {
        m_IsCollected = isCollected;
    }

    void Fall(float elapsedSec);

    void PlaySound()const;


private:

    Rectf m_Shape;

    Texture* m_pCoinTexture;

    bool m_IsCollected;
    
    SoundEffect* m_pCoinCollectedSound;
};
