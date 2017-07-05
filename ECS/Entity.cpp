#include "Entity.h"

Entity::Entity(unsigned int idIn, std::string nameIn) : m_Id(idIn), m_name(nameIn)
{}

Entity::~Entity() //components should always be heap-allocated until component pool refactor.
{
}