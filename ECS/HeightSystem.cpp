#include "HeightSystem.h"
#include "ComponentDerivative.h"


HeightSystem::HeightSystem(Engine* engine, unsigned int id): System(engine, id) 
{
	m_RelevantComponents.insert(typeid(Velocity));
	m_RelevantComponents.insert(typeid(Width));
	m_RelevantComponents.insert(typeid(Height));
}


HeightSystem::~HeightSystem(void)
{
}

void HeightSystem::processEntities()
{

}