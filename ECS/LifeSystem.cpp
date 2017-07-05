#include "LifeSystem.h"
#include "ComponentDerivative.h"
#include "Engine.h"


LifeSystem::LifeSystem(Engine* engine, unsigned int id): System(engine, id)
{
	m_RelevantComponents.insert(typeid(Life));
	m_RelevantComponents.insert(typeid(Velocity));
}

LifeSystem::~LifeSystem(void)
{
}

void LifeSystem::processEntities()
{
	m_Engine->removeComponent(0, typeid(Life));
	m_Engine->removeComponent(4, typeid(Height));
	Velocity* vel5 = new Velocity(5);
	m_Engine->addComponent(2, vel5);

	m_Engine->updateEntity(m_Engine->getEntity(0));
	m_Engine->updateEntity(m_Engine->getEntity(4));
	m_Engine->updateEntity(m_Engine->getEntity(2));
}
