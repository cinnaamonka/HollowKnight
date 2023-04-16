#include "pch.h"
#include "Coin.h"

#include <Texture.h>

Coin::Coin():
	isPickedUp{ false }
{
	m_pCoinTexture = new Texture{ "Coin.png" };

}
Coin::~Coin()
{

}
void Coin::Draw() const
{
	m_pCoinTexture->Draw(m_Shape);
}