#include "IdManager.h"

IdManager::IdManager()
	: m_nextFreeId(0)
{

}

IdManager::~IdManager()
{

}

id IdManager::getNextId()
{
	return m_nextFreeId++;
}