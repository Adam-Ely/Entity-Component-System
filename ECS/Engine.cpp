#include "Engine.h"
#include "Entity.h"
#include "System.h"
#include "Component.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::addEntity(Entity* entity)
//insert entity into collection and register it with other systems
{
	//lookup entity via id, if it exists throw exception
	//add to entity collection
	//register entity with systems
	auto entityIterator = m_Entities.find(entity->m_Id);
	if(entityIterator == m_Entities.end())
	{
		m_Entities.insert(std::pair<unsigned int, Entity*>(entity->m_Id, entity));
	}
	else
	{
		std::cout << "Error adding entity " << entity->m_Id << ". Entity with this ID already exists.\n";
		
	}

}

void Engine::removeEntity(unsigned int entityID)
//remove entity from collection
{
	//lookup entity via id, if doesnt exist throw exception
	//remove from map
	auto entityIterator = m_Entities.find(entityID);
	if(entityIterator == m_Entities.end())
	{
		std::cout << "Error removing entity " << entityID << ". Entity does not exist.\n";
	}
	else
	{
		m_Entities.erase(entityID);
	}

}

void Engine::addComponent(unsigned int entityID, Component* component)
//add component to entity specified
{
	//lookup entity via id, if doesnt exist throw exception
	//check if component of that type doesn't already exist, if so print error
	//insert component

	bool valid = true;
	
	auto entityIterator = m_Entities.find(entityID);
	if(entityIterator == m_Entities.end())
	{
		std::cout << "Error adding Component to Entity " << entityID << ". Entity does not exist.\n";
		valid = false;
	}
	//auto componentIterator = (entityIterator->second)->m_Components.find(typeid(*component));
	auto componentIterator = (entityIterator->second)->m_Components.find(typeid(*component));
	if(componentIterator != (entityIterator->second)->m_Components.end())
	{
		std::cout << "Error adding Component to Entity "<< entityID << ", it already has " << typeid(*component).name() << ".\n";
		valid = false;
	}
	if(valid)
	{
		(entityIterator->second)->m_Components.insert(std::pair<std::type_index, Component*>(typeid(*component), component));
	}

	return;
}

void Engine::removeComponent(unsigned int entityID, const std::type_index& componentType)
{
	bool valid = true;
	
	auto entityIterator = m_Entities.find(entityID);
	if(entityIterator == m_Entities.end())
	{
		std::cout << "Error removing Component from Entity " << entityID << ". Entity does not exist.\n";
		valid = false;
	}

	if (valid)
	{
		auto componentIterator = (entityIterator->second)->m_Components.find(componentType);
		if(componentIterator == (entityIterator->second)->m_Components.end())
		{
			std::cout << "Error removing Component " << componentType.name() << "from Entity. Component does not exist.\n";
			valid = false;	
		}
		if(valid)
		{
			(entityIterator->second)->m_Components.erase(componentIterator);
		}
	}
	return;
}

void Engine::addSystem(System* system)
//check it has a list of relevant components
{
	auto it = std::find< std::vector<System*>::iterator >( m_Systems.begin(), m_Systems.end(), system );
	
	bool valid = true;
	if(it != m_Systems.end())
	{
		std::cout << "Error adding System: " << typeid(*system).name() << ". System already exists.\n";
		valid = false;
	}
	if(system->m_RelevantComponents.empty())
	{
		std::cout << "Error adding System: " << typeid(*system).name() << ". Missing relevant components.\n";
		valid = false;
	}
	if(valid)
	{
		m_Systems.push_back(system);
		//need to refresh entity registers somehow
	}

	return;
}

void Engine::removeSystem(System* system)
{
	auto it = std::find< std::vector<System*>::iterator >( m_Systems.begin(), m_Systems.end(), system );
	
	if(it == m_Systems.end())
	{
		std::cout << "Error removing System: " << typeid(*system).name() << ". System not found.\n";
	}
	else
	{
		it = m_Systems.erase(it);
	}

	return;
}

void Engine::registerEntityToSystem(Entity* entity, System* system)
{
	bool valid = true;
	
	for(auto componentTypeIterator = system->m_RelevantComponents.begin(); componentTypeIterator != system->m_RelevantComponents.end(); componentTypeIterator++)
	{
		//see if current entity has a component of this type
		//if not, bail
		auto tempIt = entity->m_Components.find(*componentTypeIterator);
		if(tempIt == entity->m_Components.end())
		{
			valid = false;
		}
	}
	//if we're still going ahead, add the entity
	if(valid)
	{
		system->addEntity(entity);
	}
}

void Engine::registerAllEntitiesTo(System* system)
{
	bool valid = true;
	auto it = std::find< std::vector<System*>::iterator >( m_Systems.begin(), m_Systems.end(), system );
	
	if(it == m_Systems.end())
	{
		std::cout << "Error registering Entities to System: " << &system << ". System not found.\n";
	}
	else
	{
		for(auto entityIterator = m_Entities.begin(); entityIterator != m_Entities.end(); entityIterator++)
		{
			valid = true;
			for(auto componentTypeIterator = system->m_RelevantComponents.begin(); componentTypeIterator != system->m_RelevantComponents.end(); componentTypeIterator++)
			{
				//see if current entity has a component of this type
				//if not, bail
				auto tempIt = entityIterator->second->m_Components.find(*componentTypeIterator);
				if(tempIt == entityIterator->second->m_Components.end())
				{
					valid = false;
				}
			}
			//if we're still going ahead, add the entity
			if(valid)
			{
				system->addEntity(entityIterator->second);
			}
		}
	}

	return;
}

void Engine::registerToAllSystems(Entity* entity)
{
	bool valid = true;
	for(auto systemIterator = m_Systems.begin(); systemIterator != m_Systems.end(); systemIterator++)
	{
		valid = true;
		//for all that system's relevant components
		for(auto componentIterator = (*systemIterator)->m_RelevantComponents.begin(); componentIterator != (*systemIterator)->m_RelevantComponents.end(); componentIterator++)
		{
			//see if entity has these components
			auto tempIt = entity->m_Components.find(*componentIterator);
			if(tempIt == entity->m_Components.end())
			{
				valid = false;
			}
		}
		//if it has them all, add it to the system
		if(valid)
		{
			(*systemIterator)->addEntity(entity);
		}
	}
}

void Engine::registerAll()
{
	for(auto it = m_Systems.begin(); it != m_Systems.end(); it++)
	{
		registerAllEntitiesTo(*it);
	}
}

void Engine::updateEntity(Entity* entity)
{
	bool hasComponents;
	bool inCache;

	for(auto systemIterator = m_Systems.begin(); systemIterator != m_Systems.end(); systemIterator++)
	{
		hasComponents = true;
		inCache = (*systemIterator)->hasEntity(entity->m_Id);

		for(auto componentIterator = (*systemIterator)->m_RelevantComponents.begin(); componentIterator != (*systemIterator)->m_RelevantComponents.end(); componentIterator++)
		{
			//see if entity has these components
			auto tempIt = entity->m_Components.find(*componentIterator);
			if(tempIt == entity->m_Components.end())
			{
				hasComponents = false;
			}
		}

		if(hasComponents && !inCache)
		{
			(*systemIterator)->addEntity(entity);
		}
		else if( !hasComponents && inCache)
		{
			(*systemIterator)->removeEntity(entity);
		}
	}
}

Entity* Engine::getEntity(unsigned int id)
{
	return m_Entities[id];
}