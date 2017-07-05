#ifndef ENGINE_H
#define ENGINE_H

#include<vector>
#include<map>
#include <iostream>
#include <typeindex>

class Entity;
class System;
struct Component;

class Engine
{
	private:
		std::map<unsigned int, Entity*> m_Entities;
		std::vector<System*> m_Systems;

	public:
		Engine();
		~Engine();

		void addEntity(Entity* entity); //insert entity into collection and register it with other systems
		void removeEntity(unsigned int entityID); //remove entity from collection
		void addComponent(unsigned int entityID, Component* component); //add component to entity specified
		void removeComponent(unsigned int entityID, const std::type_index& componentType); //remove component
		//TODO: removeComponent should take Component pointer which calls typeid on it inside the function. Prevent user confusion.
		void addSystem(System* system); //check it has a list of relevant components
		void removeSystem(System* system); //remove
		void registerEntityToSystem(Entity* entity, System* system);
		void registerAllEntitiesTo(System* system);
		void registerToAllSystems(Entity* entity);
		void registerAll();
		void updateEntity(Entity* entity);
		Entity* getEntity(unsigned int id);
};
#endif
