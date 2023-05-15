#include "pch.h"
#include "DoorManager.h"
#include "Door.h"

DoorManager::DoorManager()
{

}

DoorManager::~DoorManager()
{

}


void DoorManager::Update(float elapsedSec, Avatar* pAvatar)
{
	for (int i = 0; i < GetItems().size(); i++)
	{
		GetItems()[i]->Update(elapsedSec, pAvatar, i);
	}
}
