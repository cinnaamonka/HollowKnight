#pragma once

class Texture;

class Coin final
{
public:

    Coin();
    ~Coin();

    void Draw() const;

    Rectf GetShape() const
    {
        return m_Shape;
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

private:

    Rectf m_Shape;

    Texture* m_pCoinTexture;

    bool m_IsCollected;

};
