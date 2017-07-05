#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include <map>
#include <typeindex>

class Engine;
class Entity;

class System
{
	protected:
		std::map<unsigned int, Entity*> m_EntityCache; //for processing, checking entity is present
		Engine* const m_Engine;
		
	public:
		const unsigned int m_id;
		std::set<std::type_index> m_RelevantComponents;

		virtual void processEntities() = 0; //do yo thang
		void addEntity(Entity* entity); //check if entity already in cache, check if it has relevant components, add to IDs and cache
		void removeEntity(Entity* entity); //check if entity exists, if so remove from IDs and cache
		bool hasEntity(unsigned int id);
		System(Engine* engine, unsigned int id);
		virtual ~System(){};
};
#endif