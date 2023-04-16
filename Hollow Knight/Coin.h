#pragma once

class Texture;

class Coin
{
public:

    Coin();
    ~Coin();

    Rectf GetShape() const
    {
        return m_Shape;
    }

    void SetPosition(const Point2f& pos)
    {
        m_Shape.left = pos.x;
        m_Shape.bottom = pos.y;
    }

    bool GetIsPickedUp() const
    {
        return isPickedUp;
    }

    void setIsPickedUp(const bool newIsPickedUp) {
        isPickedUp = newIsPickedUp;
    }

    void Draw() const;

private:

    Rectf m_Shape;
    bool isPickedUp;

    Texture* m_pCoinTexture;

};
