#include "pch.h"
#include "DoorManager.h"
#include "Door.h"

DoorManager::DoorManager()
{

}

DoorManager::~DoorManager()
{

}


void DoorManager::Update(float elapsedSec, Avatar* pLevel)
{
	for (int i = 0; i < GetItems().size(); i++)
	{
		GetItems()[i]->Update(elapsedSec, pLevel, i);
	}
}
