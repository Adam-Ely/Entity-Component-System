#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <unordered_map>
#include <typeindex>

struct Component;

class Entity
{
	protected:
		
		const std::string m_name;
	public:
		std::unordered_map<std::type_index, Component*> m_Components;
		const unsigned int m_Id;
		Entity(unsigned int idIn, std::string nameIn);
		~Entity();
		

};
#endif