#include "System.h"
#include "Entity.h"

System::System(Engine* engine, unsigned int id) : m_Engine(engine), m_id(id)
{
}

void System::addEntity(Entity* entity)
{
	//CHECK IF HAS IT ALREADY, IF SO DO NOTHING.
	m_EntityCache.insert(std::pair<unsigned int, Entity*>(entity->m_Id, entity));
}

void System::removeEntity(Entity* entity)
{
	m_EntityCache.erase(entity->m_Id);
}

bool System::hasEntity(unsigned int id)
{
	auto it = m_EntityCache.find(id);
	return it != m_EntityCache.end();
}