#include "pch.h"
#include "DoorManager.h"
#include "Door.h"

DoorManager::DoorManager()
{

}

DoorManager::~DoorManager()
{
	for (const Door* pDoor : m_pItems)
	{
		delete pDoor;
	}

}
void DoorManager::AddItem(Door* door)
{
	m_pItems.push_back(door);
}
void DoorManager::Draw() const
{
	for (const Door* pDoor : m_pItems)
	{
		pDoor->Draw();
	}
}

void DoorManager::Update(float elapsedSec, Avatar* pLevel)
{
	for (int i = 0; i < m_pItems.size(); i++)
	{
		m_pItems[i]->Update(elapsedSec, pLevel, i);
	}
}
